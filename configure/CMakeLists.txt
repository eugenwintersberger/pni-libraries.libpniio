include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(FindBoost)
include(FindPkgConfig)

if(NOT PKG_CONFIG_FOUND)
    message("Could not find pkg-config ... try without it!")
endif()

if("${CMAKE_FAMILY_VERSION}" STREQUAL "2.6" OR "${CMAKE_VERSION}" STREQUAL "2.8.4")
    #first we have to find the c-library
    if(HDF5_C_LIBRARY_DIRS)
        #user provided HDF5_C_LIBRARY_DIRS
        find_library(HDF5_FOUND hdf5 "${HDF5_C_LIBRARY_DIRS}")
    else()
        #without use provided HDF5_C_LIBARY_DIRS
        find_library(HDF5_FOUND hdf5)
    endif()

    message(${HDF5_FOUND}) 
    get_filename_component(HDF5_C_LIBRARY_DIRS ${HDF5_FOUND} PATH)
    string(REGEX REPLACE "lib(64)*" "include" HDF5_INCLUDE_DIRS "${HDF5_C_LIBRARY_DIRS}")
    message(${HDF5_C_LIBRARY_DIRS})
    message(${HDF5_INCLUDE_DIRS})

    #now we have to look for the header file
    find_file(HEADER "hdf5.h" ${HDF5_INCLUDE_DIRS} "${HDF5_INCLUDE_DIRS}/hdf5")
    get_filename_component(HDF5_INCLUDE_DIRS ${HEADER} PATH)
    message(${HDF5_INCLUDE_DIRS})
    include_directories(${HDF5_INCLUDE_DIRS}) 
else()
    include(FindHDF5)
endif()

if(NOT HDF5_FOUND)
    #could not find HDF5 - stop configuration step
    message("HDF5 not found:")
    message(FATAL "Please set HDF5_C_INCLUDE_DIRS and HDF5_LIBRARY_DIRS manually!")
endif()

#=================================================================================
if(NOT CMAKE_BUILD_TYPE)
    message("No build type specified - default is RELEASE")
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

#setup for GNU CXX compiler
if(CMAKE_COMPILER_IS_GNUCXX)
    message("found GNU compiler ...")
    if(CMAKE_BUILD_TYPE MATCHES RELEASE)
        message("setup for release build ...")
        add_definitions(-O3)
    elseif(CMAKE_BUILD_TYPE MATCHES DEBUG)
        message("setup for debug build ...")
        add_definitions(-O0 -g)
    endif()
endif()

#=====================need to check compiler flags=============================
#check for supported c++11 flags

#store the original state of CMAKE_REQUIRED_FLAGS
set(CMAKE_REQUIRED_FLAGS_ORIG "${CMAKE_REQUIRED_FLAGS}")

set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS_ORIG} -std=c++11")
check_cxx_source_compiles("int main() { return 0; }" HAS_CXX11_FLAG)

set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS_ORIG} -std=c++0x")
check_cxx_source_compiles("int main() { return 0; }" HAS_CXX0X_FLAG)

if(HAS_CXX11_FLAG)
    add_definitions(-std=c++11)
    set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS_ORIG} -std=c++11")
else()
    if(HAS_CXX0X_FLAG)
        add_definitions(-std=c++0x)
        set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS_ORIG} -std=c++0x")
    else()
        message(FATAL_ERROR,"Compiler does not support C++11 compiler flag")
    endif()
endif()

#=================configure installation parameters============================
include(configure/InstallConfig.cmake)

#===================================check the size of data types===============
include(configure/CheckTypeSize.cmake)

#=================try to figure out some compiler capabilities=================
include(configure/CheckCompilerCaps.cmake)

#==========================check for libraries=====================================
#the only thing we have to do here is to check for pnicore
pkg_search_module(PNICORE_PKG REQUIRED pnicore)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.41 COMPONENTS program_options system regex)

if(PKG_CONFIG_FOUND)
    pkg_search_module(CPPUNIT REQUIRED cppunit)
endif()



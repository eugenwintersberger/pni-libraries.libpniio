include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(FindPkgConfig)

include("configure/ConfigureHDF5.cmake")
include("configure/BoostConfig.cmake")

#=================================================================================
if(NOT CMAKE_BUILD_TYPE)
    message("No build type specified - default is RELEASE")
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

#setup for GNU CXX compiler
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    message("found GNU compiler ...")
    add_definitions(-g -Wall -Wextra -pedantic)
    if(CMAKE_BUILD_TYPE MATCHES RELEASE)
        message("setup for release build ...")
        add_definitions(-O3)
    elseif(CMAKE_BUILD_TYPE MATCHES DEBUG)
        message("setup for debug build ...")
        add_definitions(-O0)
        add_definitions(-DDEBUG)
    endif()

    add_definitions(-std=c++11)
    add_definitions(-DGNU_CXX)
    add_definitions(-DGNU)

elseif(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    message(STATUS "Found Clang C++ compiler ...")

    add_definitions(-Wextra -pedantic -Wall)
    if(CMAKE_BUILD_TYPE MATCHES RELEASE)
        message("setup for release build ...")
        add_definitions(-O3 -g)
    elseif(CMAKE_BUILD_TYPE MATCHES DEBUG)
        message("setup for debug build ...")
        add_definitions(-O0 -g -fno-inline -DDEBUG)
    endif()

    #for this version the compiler has to support c++11 flag
    add_definitions(-std=c++11)
    add_definitions(-DCLANG_CXX)
    add_definitions(-DCLANG)
elseif(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    message(STATUS "Found Microsoft C++ compiler ...")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(/wd4251)
endif()

#===================================check the size of data types===============
include(configure/CheckTypeSize.cmake)

find_package(h5cpp REQUIRED)

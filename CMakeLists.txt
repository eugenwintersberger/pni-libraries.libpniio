cmake_minimum_required(VERSION 2.6)
project(libpniio)
include(CTest)

set(CMAKE_FAMILY_VERSION "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}")

if(NOT CMAKE_BUILD_TYPE)
    message("No build type specified - default is RELEASE")
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

set(BOOST_INCLUDEDIR CACHE PATH "Path to the boost header files")
set(BOOST_LIBRARYDIR CACHE PATH "Path to the boost library files")
set(HDF5_C_LIBRARY_DIRS CACHE PATH "Path to the HDF5 library files")
set(HDF5_INCLUDE_DIRS CACHE PATH "Path to the HDF5 header files")
set(PNICORE_INCLUDEDIR CACHE PATH "Path to the pnicore header files")
set(PNICORE_LIBRARYDIR CACHE PATH "Path to the pnicore library files")
set(ZLIB_LIBRARYDIR CACHE PATH "Path to the ZLib library files")
set(ZLIB_INCLUDEDIR CACHE PATH "Path to the ZLib header files")
set(SZLIB_LIBRARYDIR CACHE PATH "Path to the SZLib library files")
set(SZLIB_INCLUDEDIR CACHE PATH "Path to the SZLib header files")

#===========================provide some user options==========================
option(BOOST_PREFIX "installation prefix of the local BOOST installation" "/usr")

#======================do here some setup work=================================
include(configure/CMakeLists.txt)

#need to define the version of the library
set(MAJOR_VERSION "1")
set(MINOR_VERSION "0")
set(PATCH_VERSION "1")
set(LIBRARY_VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")
set(SO_VERSION ${LIBRARY_VERSION})

include_directories("./include")

#need this to get the generated header files into the build.
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")
add_subdirectory("include")
add_subdirectory("src")
add_subdirectory("doc")
add_subdirectory("test")


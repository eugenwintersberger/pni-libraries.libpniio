cmake_minimum_required(VERSION 3.0.0)
project(pniio
        LANGUAGES CXX C
        VERSION 1.1.0)
include(CTest)

set(CMAKE_FAMILY_VERSION "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}")

if(NOT CMAKE_BUILD_TYPE)
    message("No build type specified - default is RELEASE")
    set(CMAKE_BUILD_TYPE Release)
endif()

# on Windows we first try to fetch Boost from conan - on all other systems
# try to get the system installation
if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
  set(PNIIO_CONAN_BOOST ON CACHE BOOL "User the Boost libraries from Conan")
else()
  set(PNIIO_CONAN_BOOST OFF CACHE BOOL "User the Boost libraries from Conan")
endif()

# on Windows we first try to fetch Boost from conan - on all other systems
# try to get the system installation
if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
  set(PNIIO_CONAN_HDF5 ON CACHE BOOL "User the Boost libraries from Conan")
else()
  set(PNIIO_CONAN_HDF5 OFF CACHE BOOL "User the Boost libraries from Conan")
endif()

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
  set(PNIIO_CONAN_PNICORE ON CACHE BOOL "Using conan pnicore installation")
else()
  set(PNIIO_CONAN_PNICORE OFF CACHE BOOL "Using conan pnicore installation")
endif()

#===========================provide some user options==========================
option(BOOST_PREFIX "installation prefix of the local BOOST installation" "/usr")

#======================do here some setup work=================================
include(configure/CMakeLists.txt)

#need to define the version of the library
set(LIBRARY_VERSION ${PROJECT_VERSION})
set(SO_VERSION ${PROJECT_VERSION})

include_directories("./include")

#need this to get the generated header files into the build.
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")
add_subdirectory("include")
add_subdirectory("src")
#add_subdirectory("doc")
add_subdirectory("test")

cmake_minimum_required(VERSION 3.0.0)
project(pniio
        LANGUAGES CXX C
        VERSION 1.1.0)
include(CTest)

# =============================================================================
# set library package and SOName. As this is partly a header only library the
# package version and the SOName coincide as header libraries can be considered
# as static libraries. We follow here somehow the strategy of the Boost
# libraries.
# =============================================================================
#need to define the version of the library
set(LIBRARY_VERSION ${PROJECT_VERSION})
set(SO_VERSION ${PROJECT_VERSION})


if(NOT CMAKE_BUILD_TYPE)
    message(FATAL_ERROR "No CMAKE_BUILD_TYPE set - you have to provide one!")
endif()

# =============================================================================
# determine from which source to get dependencies
# =============================================================================

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
  #on windows we use conan by default
  set(PNIIO_CONAN_BOOST ON CACHE BOOL "User the Boost libraries from Conan")
else()
  set(PNIIO_CONAN_BOOST OFF CACHE BOOL "User the Boost libraries from Conan")
endif()

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    #on Windows we use conan by default
  set(PNIIO_CONAN_HDF5 ON CACHE BOOL "User the Boost libraries from Conan")
else()
  set(PNIIO_CONAN_HDF5 OFF CACHE BOOL "User the Boost libraries from Conan")
endif()

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    #on Windows we use conan by default
  set(PNIIO_CONAN_PNICORE ON CACHE BOOL "Using conan pnicore installation")
else()
  set(PNIIO_CONAN_PNICORE OFF CACHE BOOL "Using conan pnicore installation")
endif()

# =============================================================================
# import configuration
# =============================================================================
include(configure/CMakeLists.txt)



include_directories("./include")

#need this to get the generated header files into the build.
include_directories("${PROJECT_BINARY_DIR}/include")
add_subdirectory("include")
add_subdirectory("src")
#add_subdirectory("doc")
add_subdirectory("test")

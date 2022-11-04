cmake_minimum_required(VERSION 3.10)
project(pninexus
        LANGUAGES CXX C
        VERSION 3.0.1
        # VERSION 3.0
	)
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



#---------------------------------------------------------------------------------
# Augment CMake with our custom scripts
#---------------------------------------------------------------------------------
set(EXTRA_MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${EXTRA_MODULES_DIR})


if (NOT DEFINED BUILD_SHARED_LIBS)
  set(BUILD_SHARED_LIBS ON)
endif()
option(PNINEXUS_BUILD_SHARED "Build pninexus as a shared library" ${BUILD_SHARED_LIBS})
if (NOT PNINEXUS_BUILD_SHARED)
  set(BUILD_SHARED_LIBS OFF)
endif()
option(PNINEXUS_LOCAL_MODULES "Build pninexus using cmake local modules first")
option(PNINEXUS_BUILD_EXAMPLES "Include the examples in the project" OFF)
option(PNINEXUS_BUILD_DOC "build document" ON)


set(PNINEXUS_CONAN "AUTO" CACHE STRING "conan options AUTO (conan must be in path), MANUAL (expects conanbuildinfo.cmake in build directory) or DISABLE")
set(PNINEXUS_CONAN_PROFILE "default" CACHE STRING "Name of conan profile to use, uses default by default")
set(PNINEXUS_CONAN_FILE "conanfile.txt" CACHE STRING "The conanfile to use for the build")

if(${PNINEXUS_CONAN} MATCHES "AUTO")
  include(${EXTRA_MODULES_DIR}/ConanSetup.cmake)
  conan_cmake_run(CONANFILE ${PNINEXUS_CONAN_FILE}
      PROFILE ${PNINEXUS_CONAN_PROFILE}
      BASIC_SETUP NO_OUTPUT_DIRS KEEP_RPATHS
      BUILD_TYPE "None"
      BUILD outdated)
  if(PNINEXUS_LOCAL_MODULES)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
  else()
    list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_BINARY_DIR})
  endif()
elseif(${PNINEXUS_CONAN} MATCHES "MANUAL")
  if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    conan_basic_setup(NO_OUTPUT_DIRS KEEP_RPATHS)
    if(PNINEXUS_LOCAL_MODULES)
      list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
    else()
      list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_BINARY_DIR})
    endif()
  else()
    message(FATAL_ERROR "PNINEXUS_CONAN set to MANUAL but no file named conanbuildinfo.cmake found in build directory")
  endif()
elseif(NOT ${PNINEXUS_CONAN} MATCHES "DISABLE")
  message(FATAL_ERROR "Unrecognised option for PNINEXUS_CONAN (${PNINEXUS_CONAN}), use AUTO, MANUAL or DISABLE")
endif()


#---------------------------------------------------------------------------------
# General configuration
#---------------------------------------------------------------------------------

include(${EXTRA_MODULES_DIR}/EnsureBuildType.cmake)
include(${EXTRA_MODULES_DIR}/CoverageReports.cmake)
include(${EXTRA_MODULES_DIR}/InstallConfig.cmake)
include(${EXTRA_MODULES_DIR}/OutputDirConfig.cmake)
include(${EXTRA_MODULES_DIR}/WindowsUtils.cmake)
include(${EXTRA_MODULES_DIR}/PackageConfig.cmake)
include(${EXTRA_MODULES_DIR}/BuildInfo.cmake)

if(PNINEXUS_BUILD_DOC)
  include(${EXTRA_MODULES_DIR}/DoxygenUtilities.cmake)
  include(Sphinx)
endif()

include(utilities)
# include(DoxygenUtilities)


#---------------------------------------------------------------------------------
# compiler and library configuration
#---------------------------------------------------------------------------------
find_package(Boost 1.40 COMPONENTS system
                                   regex
                                   date_time
                                   unit_test_framework
                                   filesystem REQUIRED)
include(${EXTRA_MODULES_DIR}/CompilerConfig.cmake)
include(${EXTRA_MODULES_DIR}/MPIConfig.cmake)
include(${EXTRA_MODULES_DIR}/HDF5LibraryConfig.cmake)
include(${EXTRA_MODULES_DIR}/H5CPPLibraryConfig.cmake)

if(PNINEXUS_BUILD_SHARED)
  pninexus_message(STATUS "Building shared library")
else()
  pninexus_message(STATUS "Building static library")
endif()
if (PNINEXUS_WITH_MPI)
  pninexus_message(STATUS "Building with MPI support")
endif()

find_package(Threads REQUIRED)
find_package(SZIP)
find_package(ZLIB REQUIRED)
find_package(h5cpp REQUIRED)


#
# add check target to build and run the tests
#
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -C ${CMAKE_BUILD_TYPE})

#
# add a custom target to build the HTML documentation
#
add_custom_target(html)


#---------------------------------------------------------------------------------
# create and install the package version file
#---------------------------------------------------------------------------------
write_basic_package_version_file(
     ${PROJECT_BINARY_DIR}/${PACKAGE_VERSION_FILE_NAME}
     VERSION ${PROJECT_VERSION}
     COMPATIBILITY AnyNewerVersion)

install(FILES ${PROJECT_BINARY_DIR}/${PACKAGE_VERSION_FILE_NAME}
        DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
        COMPONENT development)

#----------------------------------------------------------------------------------
# create and install the package config file
#----------------------------------------------------------------------------------
configure_file(${PACKAGE_CONFIG_FILE_NAME} ${PACKAGE_CONFIG_FILE_NAME} @ONLY)
install(FILES ${PROJECT_BINARY_DIR}/${PACKAGE_CONFIG_FILE_NAME}
        DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
        COMPONENT development)



#need this to get the generated header files into the build.
add_subdirectory("src")
if(PNINEXUS_BUILD_DOC)
  add_subdirectory("doc")
endif()
add_subdirectory("test")

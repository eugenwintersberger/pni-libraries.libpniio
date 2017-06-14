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


#
# defining some default parameters
#
include(cmake/common/EnsureBuildType.cmake)
include(cmake/common/InstallConfig.cmake)
include(cmake/common/ConanSetup.cmake)
include(cmake/common/OutputDirConfig.cmake)
include(cmake/common/PackageConfig.cmake)
include(cmake/common/WindowsUtils.cmake)

# =============================================================================
# determine from which source to get dependencies
# =============================================================================

if(NOT CONAN_BOOST)
    if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
      #on windows we use conan by default
      set(CONAN_BOOST ON CACHE BOOL "User the Boost libraries from Conan")
    else()
      set(CONAN_BOOST OFF CACHE BOOL "User the Boost libraries from Conan")
    endif()
endif()

if(NOT CONAN_HDF5)
    if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
        #on Windows we use conan by default
      set(CONAN_HDF5 ON CACHE BOOL "User the Boost libraries from Conan")
    else()
      set(CONAN_HDF5 OFF CACHE BOOL "User the Boost libraries from Conan")
    endif()
endif()

if(NOT CONAN_PNICORE)
    if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
        #on Windows we use conan by default
      set(CONAN_PNICORE ON CACHE BOOL "Using conan pnicore installation")
    else()
      set(CONAN_PNICORE OFF CACHE BOOL "Using conan pnicore installation")
    endif()
endif()

# =============================================================================
# import configuration
# =============================================================================
include(configure/CMakeLists.txt)


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
configure_file(${PACKAGE_CONFIG_FILE_NAME} ${PACKAGE_CONFIG_FILE_NAME} COPYONLY)
install(FILES ${PROJECT_BINARY_DIR}/${PACKAGE_CONFIG_FILE_NAME}
        DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
        COMPONENT development)



include_directories("./include")

#need this to get the generated header files into the build.
include_directories("${PROJECT_BINARY_DIR}/include")
add_subdirectory("include")
add_subdirectory("src")
#add_subdirectory("doc")
add_subdirectory("test")

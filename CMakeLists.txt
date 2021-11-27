cmake_minimum_required(VERSION 3.0.0)
project(pninexus
        LANGUAGES CXX C
        VERSION 2.0.0
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


#
# defining some default parameters
#
include(cmake/common/EnsureBuildType.cmake)
include(cmake/common/InstallConfig.cmake)
include(cmake/common/OutputDirConfig.cmake)
include(cmake/common/PackageConfig.cmake)
include(cmake/common/WindowsUtils.cmake)
include(cmake/common/DoxygenUtils.cmake)
include(cmake/common/SphinxUtils.cmake)


#
# add check target to build and run the tests
#
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -C ${CMAKE_BUILD_TYPE})

#
# add a custom target to build the HTML documentation
#
add_custom_target(html)

# =============================================================================
# determine from which source to get dependencies
# =============================================================================
set(WITH_CONAN OFF CACHE BOOL "Satisfy dependencies with conan")

if(WITH_CONAN)
	include(cmake/common/ConanSetup.cmake)
	include(${CMAKE_CURRENT_SOURCE_DIR}/conan.cmake)
	
	conan_cmake_run(CONANFILE conanfile.txt
		            BASIC_SETUP
		            BUILD missing)	
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
configure_file(${PACKAGE_CONFIG_FILE_NAME} ${PACKAGE_CONFIG_FILE_NAME} @ONLY)
install(FILES ${PROJECT_BINARY_DIR}/${PACKAGE_CONFIG_FILE_NAME}
        DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
        COMPONENT development)



#need this to get the generated header files into the build.
add_subdirectory("src")
add_subdirectory("doc")
add_subdirectory("test")

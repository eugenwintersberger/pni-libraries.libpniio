#
# Configure the Boost libraries
#

include(${PROJECT_SOURCE_DIR}/cmake/common/BoostLibrarySetup.cmake)

if(CONAN_BOOST)

    conan_cmake_run(REQUIRES "Boost/1.62.0@lasote/stable"
                    BASIC_SETUP
                    OPTIONS "Boost:shared=True"
                    IMPORTS "bin, *.dll -> bin"
                    BUILD missing)

endif()


find_package(Boost 1.40 COMPONENTS system
                                   regex
                                   date_time
                                   unit_test_framework
                                   filesystem)


if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find Boost libraries!")
else()
    message(STATUS "Found Boost version: ${Boost_VERSION}")
    message(STATUS "Boost library dir: ${Boost_LIBRARY_DIRS}")
    message(STATUS "Boost headers in: ${Boost_INCLUDE_DIRS}")
    add_definitions(-DBOOST_VERSION=${Boost_VERSION})
endif()

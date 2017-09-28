#
# Configure the Boost libraries
#

include(${PROJECT_SOURCE_DIR}/cmake/common/BoostLibrarySetup.cmake)


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

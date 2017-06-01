#
# Configure the Boost libraries
#


if(PNIIO_CONAN_BOOST)

    find_program(CONAN conan)
    if(CONAN MATCHES "CONAN-NONFOUND")
        message(FATAL_ERROR "Could not find conan executable to install dependencies")
    endif()

    if(NOT EXISTS ${PROJECT_BINARY_DIR}/conan.cmake)
        message(STATUS "Downloading conan.cmake file from github")
        file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
             ${PROJECT_BINARY_DIR}/conan.cmake)
    endif()

    include(${PROJECT_BINARY_DIR}/conan.cmake)

    conan_cmake_run(REQUIRES "Boost/1.62.0@lasote/stable"
                    BASIC_SETUP
                    OPTIONS "Boost:shared=True"
                    BUILD missing)

endif()

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 0.40 COMPONENTS system
                                   regex
                                   date_time
                                   unit_test_framework
                                   filesystem)


if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find Boost libraries!")
else()
    message(STATUS "Found Boost version: ${Boost_VERSION}")
    add_definitions(-DBOOST_VERSION=${Boost_VERSION})
endif()

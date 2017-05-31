
if(PNIIO_CONAN_PNICORE)

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

    set(BUILD_OPTS)
    if(PNIIO_CONAN_BOOST)
      list(APPEND BUILD_OPTS "pnicore:with_conan_boost=True")
    endif()

    conan_cmake_run(REQUIRES "pnicore/1.1.0@wintersb/devel"
                    BASIC_SETUP
                    OPTIONS ${BUILD_OPTS}
                    BUILD missing)

endif()

message(STATUS "Looking for a user defined pnicore cmake package")
#we are definitely looking for a config file package here
find_package(pnicore CONFIG REQUIRED)

set(pnicore_LIBRARIES pnicore_shared)
get_target_property(pnicore_INCLUDE_DIRS pnicore_shared INTERFACE_INCLUDE_DIRECTORIES)

message(STATUS "Found pnicore headers in: ${pnicore_INCLUDE_DIRS}")
message(STATUS "pnicore libraries: ${pnicore_LIBRARIES}")


if(CONAN_PNICORE)


    set(BUILD_OPTS)
    if(NOT CONAN_BOOST)
      list(APPEND BUILD_OPTS "pnicore:with_system_boost=True")
    endif()

    conan_cmake_run(REQUIRES "pnicore/1.1.0@wintersb/devel"
                    BASIC_SETUP
                    OPTIONS ${BUILD_OPTS}
                    IMPORTS "bin, *.dll -> bin"
                    BUILD missing)

endif()

message(STATUS "Looking for a user defined pnicore cmake package")
#we are definitely looking for a config file package here
find_package(pnicore CONFIG REQUIRED)

set(pnicore_LIBRARIES pnicore_shared)
get_target_property(pnicore_INCLUDE_DIRS pnicore_shared INTERFACE_INCLUDE_DIRECTORIES)

message(STATUS "Found pnicore headers in: ${pnicore_INCLUDE_DIRS}")
message(STATUS "pnicore libraries: ${pnicore_LIBRARIES}")

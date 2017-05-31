set(SOURCES close_test.cpp
            get_filename_test.cpp
            get_name_test.cpp
            get_parent_test.cpp
            get_path_test.cpp
            get_root_test.cpp
            get_size_test.cpp
            is_valid_test.cpp
           )


set_source_files_properties(close_test.cpp PROPERTIES
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=testing common algorithms")
add_executable(common_test ${SOURCES}
               $<TARGET_OBJECTS:test_common>
               $<TARGET_OBJECTS:algorithm_common>
               )
target_link_libraries(common_test pniio Boost::unit_test_framework)
add_test(NAME "algorithms:common"
COMMAND common_test
WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/algorithm_test/common_test)

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set_property(TEST "algorithms:common" APPEND PROPERTY
        ENVIRONMENT "PATH=${PATH_STRING}")
endif()

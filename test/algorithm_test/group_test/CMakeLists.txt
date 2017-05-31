set(SOURCES create_field_test.cpp
            create_group_test.cpp
            get_child_test.cpp
            get_class_test.cpp
            get_object_test.cpp
            is_class_test.cpp
            set_class_test.cpp
           )


set_source_files_properties(create_field_test.cpp PROPERTIES
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=testing group algorithms")
add_executable(algo_group_test ${SOURCES}
               $<TARGET_OBJECTS:test_common>
               $<TARGET_OBJECTS:algorithm_common>)
target_link_libraries(algo_group_test pniio Boost::unit_test_framework)
add_test(NAME "algorithms:group_tests"
COMMAND algo_group_test
WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/algorithm_test/group_test)

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set_property(TEST "algorithms:group_tests" APPEND PROPERTY
        ENVIRONMENT "PATH=${PATH_STRING}")
endif()

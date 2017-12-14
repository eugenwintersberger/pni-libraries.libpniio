set(SOURCES create_field_test.cpp
            create_group_test.cpp
            get_child_test.cpp
            get_class_test.cpp
            get_object_test.cpp
            is_class_test.cpp
            set_class_test.cpp
           )


set_boost_test_definitions(SOURCES "testing group algorithms")
add_executable(algo_group_test ${SOURCES}
               $<TARGET_OBJECTS:test_common>
               $<TARGET_OBJECTS:algorithm_common>)
target_link_libraries(algo_group_test pniio Boost::unit_test_framework)
add_boost_logging_test("algorithms:group_tests"
                       algo_group_test
                       ${PROJECT_BINARY_DIR}/test/algorithm_test/group_test)

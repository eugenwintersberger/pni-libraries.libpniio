set(SOURCES get_unit_test.cpp
            set_unit_test.cpp
           )


set_boost_test_definitions(SOURCES "testing field algorithms")
add_executable(algo_field_test ${SOURCES}
               $<TARGET_OBJECTS:test_common>
               $<TARGET_OBJECTS:algorithm_common>)
target_link_libraries(algo_field_test pniio Boost::unit_test_framework)

add_boost_logging_test("algorithms:field_tests"
                       algo_field_test
                   ${PROJECT_BINARY_DIR}/test/algorithm_test/field_test)

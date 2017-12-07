set(SOURCES as_attribute_test.cpp
            as_field_test.cpp
            as_group_test.cpp
            is_field_test.cpp
            is_attribute_test.cpp
            is_group_test.cpp
            )


set_boost_test_definitions(SOURCES "testing inquiry attributes")
add_executable(inquiry_conversion_test EXCLUDE_FROM_ALL ${SOURCES}
               $<TARGET_OBJECTS:test_common>
               $<TARGET_OBJECTS:algorithm_common>)
target_link_libraries(inquiry_conversion_test pniio Boost::unit_test_framework)
add_boost_logging_test("algorithms:inquiry_conversion"
                       inquiry_conversion_test
                       ${PROJECT_BINARY_DIR}/test/algorithm_test/inquiry_conversion_test)

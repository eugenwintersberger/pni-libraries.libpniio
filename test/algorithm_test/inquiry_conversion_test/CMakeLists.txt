set(SOURCES as_attribute_test.cpp
            inquiry_test_fixture.cpp
            as_field_test.cpp
            as_group_test.cpp
            is_field_test.cpp
            is_attribute_test.cpp
            is_group_test.cpp
            )


set_source_files_properties(as_attribute_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; \
                            BOOST_TEST_MODULE=testing inquiry attributes")
add_executable(inquiry_conversion_test EXCLUDE_FROM_ALL ${SOURCES}
               $<TARGET_OBJECTS:test_common>)
target_link_libraries(inquiry_conversion_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("algorithms:inquiry_conversion" inquiry_conversion_test)
add_dependencies(check inquiry_conversion_test)


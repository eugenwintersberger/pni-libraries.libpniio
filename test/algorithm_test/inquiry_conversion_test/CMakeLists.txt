set(SOURCES inquiry_conversion_test.cpp
            as_attribute_test.cpp
            as_field_test.cpp
            as_group_test.cpp
            is_field_test.cpp
            is_attribute_test.cpp
            is_group_test.cpp
            )


add_executable(inquiry_conversion_test ${SOURCES}
               $<TARGET_OBJECTS:test_common>)
target_link_libraries(inquiry_conversion_test pniio ${CPPUNIT_LIBRARIES})
add_test("algorithms:inquiry_conversion" inquiry_conversion_test)


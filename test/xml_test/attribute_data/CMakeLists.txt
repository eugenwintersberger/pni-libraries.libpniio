set(SOURCES attribute_data.cpp
            scalar_attribute_fixture.cpp 
            scalar_bool_attribute_fixture.cpp
            scalar_string_attribute_fixture.cpp
    )


add_executable(attribute_data ${SOURCES})
target_link_libraries(attribute_data pniio ${CPPUNIT_LIBRARIES})

add_test("XML::attribute_data" attribute_data)

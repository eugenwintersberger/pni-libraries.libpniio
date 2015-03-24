set(SOURCES attribute_test.cpp
            create_attribute_test.cpp
            get_attribute_test.cpp
)


add_executable(attribute_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(attribute_test pniio ${CPPUNIT_LIBRARIES})
add_test("algorithms:attribute_test" attribute_test)


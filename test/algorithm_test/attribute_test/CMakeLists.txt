set(SOURCES attribute_test.cpp
            create_attribute_test.cpp
            get_attribute_test.cpp
)


add_executable(algo_attribute_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(algo_attribute_test pniio ${CPPUNIT_LIBRARIES})
add_test("algorithms:attribute_test" algo_attribute_test)


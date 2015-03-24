set(SOURCES field_test.cpp
            get_unit_test.cpp
            set_unit_test.cpp
           )


add_executable(field_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(field_test pniio ${CPPUNIT_LIBRARIES})
add_test("algorithms:field_tests" field_test)


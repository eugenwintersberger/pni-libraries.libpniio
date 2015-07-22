set(SOURCES field_test.cpp
            get_unit_test.cpp
            set_unit_test.cpp
           )


add_executable(algo_field_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(algo_field_test pniio ${CPPUNIT_LIBRARIES})
add_test("algorithms:field_tests" algo_field_test)


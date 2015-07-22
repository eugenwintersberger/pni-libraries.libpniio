set(SOURCES create_field_test.cpp
            create_group_test.cpp
            get_child_test.cpp
            get_class_test.cpp
            get_object_test.cpp
            group_test.cpp
            is_class_test.cpp
            set_class_test.cpp
           )


add_executable(algo_group_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(algo_group_test pniio ${CPPUNIT_LIBRARIES})
add_test("algorithms:group_tests" algo_group_test)


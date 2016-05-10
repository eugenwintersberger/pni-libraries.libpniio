set(SOURCES create_field_test.cpp
            create_group_test.cpp
            get_child_test.cpp
            get_class_test.cpp
            get_object_test.cpp
            is_class_test.cpp
            set_class_test.cpp
           )


set_source_files_properties(create_field_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; 
                            BOOST_TEST_MODULE=testing group algorithms")
add_executable(algo_group_test EXCLUDE_FROM_ALL ${SOURCES} 
               $<TARGET_OBJECTS:test_common>
               $<TARGET_OBJECTS:algorithm_common>)
target_link_libraries(algo_group_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("algorithms:group_tests" algo_group_test)
add_dependencies(check algo_group_test)


set(SOURCES get_unit_test.cpp
            set_unit_test.cpp
           )


set_source_files_properties(get_unit_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; 
                            BOOST_TEST_MODULE=testing field algorithms")
add_executable(algo_field_test EXCLUDE_FROM_ALL ${SOURCES} 
               $<TARGET_OBJECTS:test_common>
               $<TARGET_OBJECTS:algorithm_common>)
target_link_libraries(algo_field_test pniio
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("algorithms:field_tests" algo_field_test)
add_dependencies(check algo_field_test)


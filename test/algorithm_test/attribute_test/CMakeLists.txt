set(SOURCES create_attribute_test.cpp
            get_attribute_test.cpp
            get_attributes_test.cpp
)


set_source_files_properties(create_attribute_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; 
                            BOOST_TEST_MODULE=testing attribute algorithms")
add_executable(algo_attribute_test EXCLUDE_FROM_ALL ${SOURCES} 
               $<TARGET_OBJECTS:test_common>
               $<TARGET_OBJECTS:algorithm_common>)
target_link_libraries(algo_attribute_test pniio 
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("algorithms:attribute_test" algo_attribute_test)
add_dependencies(check algo_attribute_test)


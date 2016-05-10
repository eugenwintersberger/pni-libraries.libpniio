set(SOURCES io_test_fixture.cpp 
            get_rank_test.cpp
            get_shape_test.cpp
            get_type_test.cpp
            grow_test.cpp
            read_write_test.cpp
           )


set_source_files_properties(get_rank_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; 
                            BOOST_TEST_MODULE=testing group algorithms")
add_executable(algo_io_tests EXCLUDE_FROM_ALL ${SOURCES} 
               $<TARGET_OBJECTS:test_common>
               $<TARGET_OBJECTS:algorithm_common>)
target_link_libraries(algo_io_tests pniio 
                                    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("algorithms:io_tests" algo_io_tests)
add_dependencies(check algo_io_tests)


set(SOURCES close_test.cpp
            get_filename_test.cpp
            get_name_test.cpp
            get_parent_test.cpp
            get_path_test.cpp
            get_root_test.cpp
            get_size_test.cpp
            is_valid_test.cpp
           )


set_source_files_properties(close_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; 
                            BOOST_TEST_MODULE=testing common algorithms")
add_executable(common_test EXCLUDE_FROM_ALL ${SOURCES} 
               $<TARGET_OBJECTS:test_common>
               $<TARGET_OBJECTS:algorithm_common>
               )
target_link_libraries(common_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("algorithms:common" common_test)
add_dependencies(check common_test)


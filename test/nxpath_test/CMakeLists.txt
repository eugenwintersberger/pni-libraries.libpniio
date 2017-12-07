set(SOURCES
            nxpath_test.cpp
            nxpath_create_test.cpp
            nxpath_push_test.cpp
            nxpath_pop_test.cpp
            test_element_equality.cpp
            nxpath_equality_test.cpp
           )

set_boost_test_definitions(SOURCES "Testing general nxpath functions")
add_executable(nxpath_tests EXCLUDE_FROM_ALL ${SOURCES})
add_dependencies(check nxpath_tests)
target_link_libraries(nxpath_tests pniio Boost::unit_test_framework)
add_boost_logging_test("nxpath:general_tests" nxpath_tests
                       ${PROJECT_BINARY_DIR}/test/nxpath_test)



set(PARSERSRC  nxpath_parser_test.cpp )

set_boost_test_definitions(PARSERSRC "Testing the path parser")
add_executable(nxpath_parser_tests EXCLUDE_FROM_ALL ${PARSERSRC})
add_dependencies(check nxpath_parser_tests)
target_link_libraries(nxpath_parser_tests pniio Boost::unit_test_framework)
add_boost_logging_test("nxpath:parser_tests" nxpath_parser_tests
                       ${PROJECT_BINARY_DIR}/test/nxpath_test)


set(UTILSRC test_object_element.cpp
            test_is_root_element.cpp
            test_is_complete.cpp
            test_has_name.cpp
            test_has_class.cpp
            test_is_absolute.cpp
            test_has_file_section.cpp
            test_has_attribute_section.cpp
            test_split_path.cpp
            test_is_empty.cpp
            test_join.cpp
            nxpath_match_test.cpp
            test_element_match.cpp
            test_make_relative.cpp
           )

set_boost_test_definitions(UTILSRC "Testing nxpath utilities")
add_executable(nxpath_utils_test EXCLUDE_FROM_ALL ${UTILSRC})
add_dependencies(check nxpath_utils_test)
target_link_libraries(nxpath_utils_test pniio Boost::unit_test_framework)
add_boost_logging_test("nxpath:utilities" nxpath_utils_test
                       ${PROJECT_BINARY_DIR}/test/nxpath_test)

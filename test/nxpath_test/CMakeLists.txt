set(SOURCES 
            nxpath_test.cpp
            nxpath_create_test.cpp
            nxpath_push_test.cpp
            nxpath_pop_test.cpp
            test_element_equality.cpp 
            nxpath_equality_test.cpp                   
           )

set_source_files_properties(nxpath_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; \
                            BOOST_TEST_MODULE=Testing general nxpath functions")
add_executable(nxpath_tests EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(nxpath_tests pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("nxpath:general_tests" nxpath_tests)
add_dependencies(check nxpath_tests)

set(PARSERSRC  nxpath_parser_test.cpp
               element_parser_test.cpp
               elements_parser_test.cpp
               dot_parser_test.cpp
           )

set_source_files_properties(nxpath_parser_test.cpp PROPERTIES
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; \
                            BOOST_TEST_MODULE=Testing the path parser")
add_executable(nxpath_parser_tests EXCLUDE_FROM_ALL ${PARSERSRC})
target_link_libraries(nxpath_parser_tests pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("nxpath:parser_tests" nxpath_parser_tests)
add_dependencies(check nxpath_parser_tests)

#
#set(UTILSRC nxpath_utils_tests.cpp
#            test_object_element.cpp
#            test_is_root_element.cpp
#            test_is_complete.cpp
#            test_has_name.cpp
#            test_has_class.cpp
#            test_is_absolute.cpp
#            test_has_file_section.cpp
#            test_has_attribute_section.cpp
#            test_split_path.cpp
#            test_is_empty.cpp
#            test_join.cpp
#            nxpath_match_test.cpp
#            test_element_match.cpp
#            test_make_relative.cpp
#           )
#add_executable(nxpath_utils_test EXCLUDE_FROM_ALL  ${UTILSRC})
#target_link_libraries(nxpath_utils_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
#add_test("nxpath:utilities" nxpath_utils_test)


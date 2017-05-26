set(SOURCES
            nxpath_test.cpp
            nxpath_create_test.cpp
            nxpath_push_test.cpp
            nxpath_pop_test.cpp
            test_element_equality.cpp
            nxpath_equality_test.cpp
           )

set_source_files_properties(nxpath_test.cpp PROPERTIES
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=Testing general nxpath functions")
add_executable(nxpath_tests ${SOURCES})
target_link_libraries(nxpath_tests pniio Boost::unit_test_framework)
add_test(NAME "nxpath:general_tests"
COMMAND nxpath_tests
WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/nxpath_test)

if(CMAKE_SYSTEM_NAME MATCHES Windows)
  set_property(TEST "nxpath:general_tests" APPEND PROPERTY
  ENVIRONMENT "PATH=${PATH_STRING}")
endif()

set(PARSERSRC  nxpath_parser_test.cpp
               element_parser_test.cpp
               elements_parser_test.cpp
               dot_parser_test.cpp
           )

set_source_files_properties(nxpath_parser_test.cpp PROPERTIES
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=Testing the path parser")
add_executable(nxpath_parser_tests ${PARSERSRC})
target_link_libraries(nxpath_parser_tests pniio Boost::unit_test_framework)
add_test(NAME "nxpath:parser_tests"
COMMAND nxpath_parser_tests
WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/nxpath_test)

if(CMAKE_SYSTEM_NAME MATCHES Windows)
  set_property(TEST "nxpath:parser_tests" APPEND PROPERTY
ENVIRONMENT "PATH=${PATH_STRING}")
endif()


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

set_source_files_properties(test_object_element.cpp PROPERTIES
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=Testing nxpath utilities")
add_executable(nxpath_utils_test ${UTILSRC})
target_link_libraries(nxpath_utils_test pniio Boost::unit_test_framework)
add_test(NAME "nxpath:utilities"
COMMAND nxpath_utils_test
WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/nxpath_test)

if(CMAKE_SYSTEM_NAME MATCHES Windows)
  set_property(TEST "nxpath:utilities" APPEND PROPERTY
  ENVIRONMENT "PATH=${PATH_STRING}")
endif()

add_subdirectory(primitive_parsers)
add_subdirectory(object_parsers)
set(TESTS_WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/parser_test)

add_executable(is_integer_test is_integer_test.cpp)
target_link_libraries(is_integer_test pniio Boost::unit_test_framework)
target_compile_definitions(is_integer_test PRIVATE
"BOOST_TEST_DYN_LINK;BOOST_TEST_MODULE=Testing is_integer utility function")

add_test(NAME "parsers:utilities:is_integer"
COMMAND is_integer_test
WORKING_DIRECTORY ${TESTS_WORKING_DIRECTORY})

add_executable(is_float_test is_float_test.cpp)
target_link_libraries(is_float_test pniio Boost::unit_test_framework)
target_compile_definitions(is_float_test PRIVATE
"BOOST_TEST_DYN_LINK;BOOST_TEST_MODULE=Testing is_float utility function")

add_test(NAME "parsers:utilities:is_float"
COMMAND is_float_test
WORKING_DIRECTORY ${TESTS_WORKING_DIRECTORY})

add_executable(is_slice_test is_slice_test.cpp)
target_link_libraries(is_slice_test pniio Boost::unit_test_framework)
target_compile_definitions(is_slice_test PRIVATE
"BOOST_TEST_DYN_LINK;BOOST_TEST_MODULE=Testing is_slice utiltiy function")

add_test(NAME "parsers:utilities:is_slice"
COMMAND is_slice_test
WORKING_DIRECTORY ${TESTS_WORKING_DIRECTORY})

add_executable(is_bool_test is_bool_test.cpp)
target_link_libraries(is_bool_test pniio Boost::unit_test_framework)
target_compile_definitions(is_bool_test PRIVATE
"BOOST_TEST_DYN_LINK;BOOST_TEST_MODULE=Testing is_bool utility function")

add_test(NAME "parsers:utilities:is_boolean"
COMMAND is_bool_test
WORKING_DIRECTORY ${TESTS_WORKING_DIRECTORY})

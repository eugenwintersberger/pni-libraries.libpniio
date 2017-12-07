add_subdirectory(primitive_parsers)
add_subdirectory(object_parsers)
set(TESTS_WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/parser_test)

add_executable(default_int_regexp_test EXCLUDE_FROM_ALL default_int_regexp_test.cpp)
target_link_libraries(default_int_regexp_test pniio Boost::unit_test_framework)
target_compile_definitions(default_int_regexp_test PRIVATE
"BOOST_TEST_DYN_LINK;BOOST_TEST_MODULE=Testing the default regular expression for integers")

add_test(NAME "parsers:utilities:default_int_regexp"
COMMAND default_int_regexp_test
WORKING_DIRECTORY ${TESTS_WORKING_DIRECTORY})

add_executable(default_float_regexp_test EXCLUDE_FROM_ALL default_float_regexp_test.cpp)
target_link_libraries(default_float_regexp_test pniio Boost::unit_test_framework)
target_compile_definitions(default_float_regexp_test PRIVATE
"BOOST_TEST_DYN_LINK;BOOST_TEST_MODULE=Testing the default regular expression for floats")

add_test(NAME "parsers:utilities:default_float_regexp"
COMMAND default_float_regexp_test
WORKING_DIRECTORY ${TESTS_WORKING_DIRECTORY})

add_dependencies(check default_int_regexp_test 
	                   default_float_regexp_test)

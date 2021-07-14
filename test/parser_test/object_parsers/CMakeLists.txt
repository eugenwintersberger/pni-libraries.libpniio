set(SOURCES slice_parser_test.cpp
            vector_parser_test.cpp
            int8_vector_parser_test.cpp
            uint8_vector_parser_test.cpp
            float32_vector_parser_test.cpp
            bool_vector_parser_test.cpp
            string_vector_parser_test.cpp
           )

set_boost_test_definitions(SOURCES "testing object parsers")
add_executable(object_parsers_test EXCLUDE_FROM_ALL ${SOURCES} )
target_link_libraries(object_parsers_test pninexus Boost::unit_test_framework)
add_boost_logging_test("parsers:object_parsers" object_parsers_test
                       ${PROJECT_BINARY_DIR}/test/parser_test/object_parsers)
                      
add_dependencies(check object_parsers_test)

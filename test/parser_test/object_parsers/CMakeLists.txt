set(SOURCES slice_parser_test.cpp
            vector_parser_test.cpp
            int8_vector_parser_test.cpp
            uint8_vector_parser_test.cpp
            float32_vector_parser_test.cpp
            bool_vector_parser_test.cpp
            string_vector_parser_test.cpp
           )

set_source_files_properties(slice_parser_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; 
                            BOOST_TEST_MODULE=testing object parsers")
add_executable(object_parsers_test EXCLUDE_FROM_ALL ${SOURCES} )
target_link_libraries(object_parsers_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("parsers:object_parsers" object_parsers_test)
add_dependencies(check object_parsers_test)


set(SOURCES uint8_parser_test.cpp
            uint16_parser_test.cpp
            uint32_parser_test.cpp
            uint64_parser_test.cpp
            int8_parser_test.cpp
            int16_parser_test.cpp
            int32_parser_test.cpp
            int64_parser_test.cpp
            float32_parser_test.cpp
            float64_parser_test.cpp
            float128_parser_test.cpp
            complex32_parser_test.cpp
            complex64_parser_test.cpp
            complex128_parser_test.cpp
            string_parser_test.cpp
            bool_parser_test.cpp
            value_parser_test.cpp
           )


set_source_files_properties(uint8_parser_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; \
                            BOOST_TEST_MODULE=testing primitive parsers")
add_executable(primitive_parsers_test EXCLUDE_FROM_ALL ${SOURCES} )
target_link_libraries(primitive_parsers_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("parsers:primitive_parsers" primitive_parsers_test)
add_dependencies(check primitive_parsers_test)


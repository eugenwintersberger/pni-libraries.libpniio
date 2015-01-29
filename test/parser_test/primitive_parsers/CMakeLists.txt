set(SOURCES primitive_parsers_test.cpp
            uint8_parser_test.cpp
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

add_executable(primitive_parsers_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(primitive_parsers_test pniio ${CPPUNIT_LIBRARIES})
add_test("parsers:primitive_parsers" primitive_parsers_test)


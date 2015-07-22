set(SOURCES object_parsers_test.cpp
            slice_parser_test.cpp
            vector_parser_test.cpp
            int8_vector_parser_test.cpp
            uint8_vector_parser_test.cpp
            float32_vector_parser_test.cpp
            bool_vector_parser_test.cpp
            string_vector_parser_test.cpp
           )

add_executable(object_parsers_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(object_parsers_test pniio ${CPPUNIT_LIBRARIES})
add_test("parsers:object_parsers" object_parsers_test)


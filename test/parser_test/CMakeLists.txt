set(SOURCES array_parser_test.cpp
            record_parser_test.cpp
            slice_parser_test.cpp
            value_parser_test.cpp
            parser_test.cpp
           )

add_executable(parser_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(parser_test pniio ${CPPUNIT_LIBRARIES})
add_test(parser_test parser_test)


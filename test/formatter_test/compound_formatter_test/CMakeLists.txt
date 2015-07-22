set(SOURCES compound_formatters_test.cpp
            int8_vector_formatter_test.cpp
            bool_vector_formatter_test.cpp
            mdarray_formatter_test.cpp
            array_formatter_test.cpp
           )

add_executable(compound_formatter_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(compound_formatter_test pniio ${CPPUNIT_LIBRARIES})
add_test("formatters:compound_formatters" compound_formatter_test)


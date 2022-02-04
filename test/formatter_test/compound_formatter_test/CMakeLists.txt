set(SOURCES
            int8_vector_formatter_test.cpp
            bool_vector_formatter_test.cpp
            mdarray_formatter_test.cpp
            array_formatter_test.cpp
           )

set_boost_test_definitions(SOURCES "Testing compound formatters")
add_executable(compound_formatter_test EXCLUDE_FROM_ALL ${SOURCES} )
add_dependencies(check compound_formatter_test)
target_link_libraries(compound_formatter_test pninexus h5cpp::h5cpp Boost::unit_test_framework)
add_boost_logging_test("formatters:compound_formatters"
                       compound_formatter_test
                       ${PROJECT_BINARY_DIR}/test/formatter_test/compound_formatter_test)

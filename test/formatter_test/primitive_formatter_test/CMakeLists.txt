set(SOURCES
            uint8_formatter_test.cpp
            uint16_formatter_test.cpp
            uint32_formatter_test.cpp
            uint64_formatter_test.cpp
            int8_formatter_test.cpp
            int16_formatter_test.cpp
            int32_formatter_test.cpp
            int64_formatter_test.cpp
            float32_formatter_test.cpp
            float64_formatter_test.cpp

            complex32_formatter_test.cpp

            bool_formatter_test.cpp
            value_formatter_test.cpp
           )

set_boost_test_definitions(SOURCES "Testing primitive formatters")
add_executable(primitive_formatter_test EXCLUDE_FROM_ALL ${SOURCES})
add_dependencies(check primitive_formatter_test)
target_link_libraries(primitive_formatter_test pninexus Boost::unit_test_framework)
add_boost_logging_test("formatters:primitive_formatters"
                       primitive_formatter_test
                       ${PROJECT_BINARY_DIR}/test/formatter_test/primitive_formatter_test)

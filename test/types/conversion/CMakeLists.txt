#need to define the version of the library
set(SOURCES unchecked_convertible_test.cpp
            is_unchecked_convertible_test.cpp
            is_checked_convertible_test.cpp
            is_convertible_test.cpp
            checked_convertible_test.cpp
            convert_uint8_test.cpp
            convert_uint16_test.cpp
            convert_uint32_test.cpp
            convert_uint64_test.cpp
            convert_int8_test.cpp
            convert_int16_test.cpp
            convert_int32_test.cpp
            convert_int64_test.cpp
            convert_float32_test.cpp
            convert_float64_test.cpp
            convert_float128_test.cpp
            convert_complex32_test.cpp
            convert_complex64_test.cpp
            convert_complex128_test.cpp
    )


set_boost_test_definitions(SOURCES "Testing type conversions")
add_executable(conversion_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(conversion_test pninexus h5cpp::h5cpp Boost::unit_test_framework)
add_dependencies(check conversion_test)

add_boost_logging_test("types:conversion_test" conversion_test
                       ${PROJECT_BINARY_DIR}/test/types/conversion)

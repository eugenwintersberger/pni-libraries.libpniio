#need to define the version of the library
set(SOURCES value_construction_test.cpp
            value_assignment_test.cpp
            uint8_value_as_test.cpp
            uint16_value_as_test.cpp
            uint32_value_as_test.cpp
            uint64_value_as_test.cpp
            int8_value_as_test.cpp
            int16_value_as_test.cpp
            int32_value_as_test.cpp
            int64_value_as_test.cpp
            float32_value_as_test.cpp
            float64_value_as_test.cpp
            float128_value_as_test.cpp
            complex32_value_as_test.cpp
            complex64_value_as_test.cpp
            complex128_value_as_test.cpp
            string_value_as_test.cpp
            binary_value_as_test.cpp
            bool_value_as_test.cpp
            ebool_value_as_test.cpp
    )

# set_boost_test_definitions(SOURCES "testing the value type erasure")

add_executable(value_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)

target_link_libraries(value_test pninexus h5cpp::h5cpp Boost::unit_test_framework Boost::filesystem)
target_compile_definitions(value_test PRIVATE
    BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing the value type erasure")
add_dependencies(check value_test)


add_boost_logging_test("type_erasure_test:value" value_test
                       ${PROJECT_BINARY_DIR}/test/type_erasures/value)

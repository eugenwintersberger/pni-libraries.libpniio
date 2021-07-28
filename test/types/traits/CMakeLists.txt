#need to define the version of the library
set(SOURCES is_integer_type_test.cpp
            is_integer_test.cpp

            is_complex_test.cpp
            is_complex_type_test.cpp

            is_float_type_test.cpp
            is_float_test.cpp

            is_numeric_type_test.cpp
            is_numeric_test.cpp

            is_non_numeric_type_test.cpp
    )

set_boost_test_definitions(SOURCES "testing type traits")

add_executable(traits_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(traits_test pninexus Boost::unit_test_framework)
add_dependencies(check traits_test)

add_boost_logging_test("types:traits_test" traits_test
                       ${PROJECT_BINARY_DIR}/test/types/traits)

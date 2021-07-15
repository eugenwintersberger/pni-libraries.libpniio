#need to define the version of the library
set(SOURCES add_operator_test.cpp
            div_operator_test.cpp
            inplace_arithmetics_test.cpp
            mult_operator_test.cpp
            sub_operator_test.cpp
    )

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif()

set_boost_test_definitions(SOURCES "testing array arithmetics")

add_executable(math_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
add_executable(random_ranges EXCLUDE_FROM_ALL random_ranges.cpp)
add_dependencies(check math_test random_ranges)

target_link_libraries(math_test pninexus Boost::unit_test_framework)

target_link_libraries(random_ranges pninexus)

add_boost_logging_test("math_test" math_test ${PROJECT_BINARY_DIR}/test/math)

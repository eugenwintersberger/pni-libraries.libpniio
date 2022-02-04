#need to define the version of the library
set(SOURCES scalar_test.cpp
            array_selection_test.cpp
            array_view_test.cpp
            array_view_unary_arithmetic_test.cpp
            dynamic_mdarray_test.cpp
            fix_mdarray_test.cpp
            static_mdarray_test.cpp
            mdarray_test.cpp
            array_view_utils_test.cpp
    )

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif()

set_boost_test_definitions(SOURCES "Testing array functions")

add_executable(arrays_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(arrays_test pninexus h5cpp::h5cpp Boost::unit_test_framework)
add_dependencies(check arrays_test)

add_boost_logging_test("arrays_test"
                       arrays_test
                       ${PROJECT_BINARY_DIR}/test/arrays)

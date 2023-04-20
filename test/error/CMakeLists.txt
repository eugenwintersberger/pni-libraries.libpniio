#need to define the version of the library
set(SOURCES check_equal_size_test.cpp
            check_index_in_dim_test.cpp
            check_indexes_test.cpp
            check_equal_rank_test.cpp
            check_equal_shape_test.cpp
            )

set_boost_test_definitions(SOURCES "testing error functions")

add_executable(error_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(error_test pninexus h5cpp::h5cpp Boost::unit_test_framework)
add_dependencies(check error_test)

add_boost_logging_test("error_test" error_test ${PROJECT_BINARY_DIR}/test/error)

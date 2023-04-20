#need to define the version of the library
set(SOURCES container_utils_array_test.cpp
            container_utils_std_test.cpp
            index_iterator_test.cpp
            iterator_test.cpp
            slice_test.cpp
    )

set_boost_test_definitions(SOURCES "testing utilty code")

add_executable(utils_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(utils_test pninexus h5cpp::h5cpp Boost::unit_test_framework Boost::filesystem)
add_dependencies(check utils_test)


add_boost_logging_test("utils_test" utils_test
                       ${PROJECT_BINARY_DIR}/test/utils_test)

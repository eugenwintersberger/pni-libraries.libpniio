set(SOURCES get_rank_test.cpp
            io_test_fixture.cpp
            get_shape_test.cpp
            get_type_test.cpp
            grow_test.cpp
            read_write_test.cpp
           )

set_boost_test_definitions(SOURCES "testing group algorithms")
add_executable(algo_io_tests EXCLUDE_FROM_ALL ${SOURCES}
               $<TARGET_OBJECTS:test_common>
               $<TARGET_OBJECTS:algorithm_common>)
target_link_libraries(algo_io_tests pniio Boost::unit_test_framework)
add_boost_logging_test("algorithms:io_tests"
                       algo_io_tests
                       ${PROJECT_BINARY_DIR}/test/algorithm_test/io_test)

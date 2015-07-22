set(SOURCES get_rank_test.cpp
            get_shape_test.cpp
            get_type_test.cpp
            grow_test.cpp
            io_test.cpp
            read_write_test.cpp
           )


add_executable(algo_io_tests EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(algo_io_tests pniio ${CPPUNIT_LIBRARIES})
add_test("algorithms:io_tests" algo_io_tests)


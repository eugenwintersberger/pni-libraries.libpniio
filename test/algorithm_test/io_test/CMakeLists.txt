set(SOURCES get_rank_test.cpp
            get_shape_test.cpp
            get_type_test.cpp
            grow_test.cpp
            io_test.cpp
            read_write_test.cpp
           )


add_executable(io_tests ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(io_tests pniio ${CPPUNIT_LIBRARIES})
add_test("algorithms:io_tests" io_tests)


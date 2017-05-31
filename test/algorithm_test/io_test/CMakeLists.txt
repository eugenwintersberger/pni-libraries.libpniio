set(SOURCES io_test_fixture.cpp
            get_rank_test.cpp
            get_shape_test.cpp
            get_type_test.cpp
            grow_test.cpp
            read_write_test.cpp
           )


set_source_files_properties(get_rank_test.cpp PROPERTIES
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=testing group algorithms")
add_executable(algo_io_tests ${SOURCES}
               $<TARGET_OBJECTS:test_common>
               $<TARGET_OBJECTS:algorithm_common>)
target_link_libraries(algo_io_tests pniio Boost::unit_test_framework)
add_test(NAME "algorithms:io_tests"
COMMAND algo_io_tests
WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/algorithm_test/io_test)

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set_property(TEST "algorithms:io_tests" APPEND PROPERTY
        ENVIRONMENT "PATH=${PATH_STRING}")
endif()

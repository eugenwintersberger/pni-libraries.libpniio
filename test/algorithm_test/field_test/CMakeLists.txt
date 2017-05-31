set(SOURCES get_unit_test.cpp
            set_unit_test.cpp
           )


set_source_files_properties(get_unit_test.cpp PROPERTIES
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=testing field algorithms")
add_executable(algo_field_test ${SOURCES}
               $<TARGET_OBJECTS:test_common>
               $<TARGET_OBJECTS:algorithm_common>)
target_link_libraries(algo_field_test pniio Boost::unit_test_framework)
add_test(NAME "algorithms:field_tests"
COMMAND algo_field_test
WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/algorithm_test/field_test)

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set_property(TEST "algorithms:field_tests" APPEND PROPERTY
        ENVIRONMENT "PATH=${PATH_STRING}")
endif()

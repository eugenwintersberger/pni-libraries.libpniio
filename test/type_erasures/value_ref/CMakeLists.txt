#need to define the version of the library
set(SOURCES value_ref_construction_test.cpp
            value_ref_assignment_test.cpp
    )

set_boost_test_definitions(SOURCES "testing the value_ref type erasure")
add_executable(value_ref_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(value_ref_test pninexus Boost::unit_test_framework)
add_dependencies(check value_ref_test)


add_boost_logging_test("type_erasure_test:value_ref" value_ref_test 
                 ${PROJECT_BINARY_DIR}/test/type_erasures/value_ref)

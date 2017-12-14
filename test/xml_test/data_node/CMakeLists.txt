set(SOURCES child_node_io_test.cpp
            data_node_fixture.cpp
            attribute_node_io_test.cpp
    )

set_boost_test_definitions(SOURCES "testing data_node operations")
add_executable(data_node_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(data_node_test pniio Boost::unit_test_framework)

#add_boost_logging_test("XML::data_node_tests" data_node_test
#                       ${PROJECT_BINARY_DIR}/test/xml_test/data_node)

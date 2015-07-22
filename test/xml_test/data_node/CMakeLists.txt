set(SOURCES data_node_test.cpp
            child_node_io_fixture.cpp
            attribute_node_io_fixture.cpp
    )


add_executable(data_node_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(data_node_test pniio ${CPPUNIT_LIBRARIES})

add_test("XML::data_node_tests" data_node_test)

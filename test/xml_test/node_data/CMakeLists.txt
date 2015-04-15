set(SOURCES node_data.cpp
            child_node_io_fixture.cpp
            attribute_node_io_fixture.cpp
    )


add_executable(node_data ${SOURCES})
target_link_libraries(node_data pniio ${CPPUNIT_LIBRARIES})

add_test("XML::node_data" node_data)

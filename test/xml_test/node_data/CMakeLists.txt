set(SOURCES node_data.cpp
            node_scalar_data_fixture.cpp
            node_array_data_fixture.cpp
            node_inquery_data_fixture.cpp
    )


add_executable(node_data ${SOURCES})
target_link_libraries(node_data pniio ${CPPUNIT_LIBRARIES})

add_test("XML::node_data" node_data)

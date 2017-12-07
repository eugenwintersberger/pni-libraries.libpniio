set(SOURCES inquery_test.cpp
            data_from_xml_test.cpp
            )

set(XMLFILES object1.xml object2.xml object3.xml)

foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_executable(io_node_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(io_node_test pniio Boost::unit_test_framework)
add_boost_logging_test("XML::io_node" io_node_test
${PROJECT_BINARY_DIR}/test/xml_test/io_node)

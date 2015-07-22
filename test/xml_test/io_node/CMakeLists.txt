set(SOURCES io_node_tests.cpp
            inquery_fixture.cpp
            data_from_xml_fixture.cpp
            )

set(XMLFILES object1.xml object2.xml object3.xml)

foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPY_ONLY)
endforeach()

add_executable(io_node_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(io_node_test pniio ${CPPUNIT_LIBRARIES})
add_test(NAME "XML::io_node"
         COMMAND io_node_test)

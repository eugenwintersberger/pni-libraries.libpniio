set(SOURCES run_test.cpp attribute_data_fixture.cpp node_data_fixture.cpp)

set(XMLFILES attribute.xml node.xml)


foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_executable(object_data_test ${SOURCES})
target_link_libraries(object_data_test pniio ${CPPUNIT_LIBRARIES})
add_test(NAME "XML::object_data"
         COMMAND object_data_test)

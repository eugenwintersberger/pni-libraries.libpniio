set(SOURCES field_inquery_fixture.cpp
            field_to_xml_fixture.cpp
            )

set(XMLFILES field1.xml
             field2.xml
             field3.xml
             field4.xml
             field5.xml
             field_test_data_array.xml
             field_test_data_scalar.xml
             )


foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_executable(field_test ${SOURCES})
target_link_libraries(field_test pniio ${CPPUNIT_LIBRARIES})
add_test(NAME "XML::field"
         COMMAND field_test)

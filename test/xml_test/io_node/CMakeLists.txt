set(SOURCES run_test.cpp
            inquery_fixture.cpp
            data_from_xml_fixture.cpp
            )

set(XMLFILES object1.xml object2.xml object3.xml)

foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPY_ONLY)
endforeach()

add_executable(run_test ${SOURCES})
target_link_libraries(run_test pniio ${CPPUNIT_LIBRARIES})
add_test(NAME "XML::io_node"
         COMMAND run_test)

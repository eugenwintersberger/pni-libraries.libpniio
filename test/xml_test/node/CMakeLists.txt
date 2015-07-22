set(SOURCES run_test.cpp
            creation_fixture.cpp
            inquery_fixture.cpp
     )

set(XMLFILES  node_from_bad_file.xml node_from_str.xml
              inquery.xml 
    )


foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_executable(node_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(node_test pniio ${CPPUNIT_LIBRARIES})
add_test(NAME "XML::node"
         COMMAND node_test)

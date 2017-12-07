set(SOURCES creation_fixture.cpp
            inquery_fixture.cpp
     )

set(XMLFILES  node_from_bad_file.xml
              node_from_str.xml
              inquery.xml
    )


foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_executable(node_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(node_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_boost_logging_test("XML::node" node_test
         ${PROJECT_BINARY_DIR}/test/xml_test/node)

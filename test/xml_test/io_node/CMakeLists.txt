set(SOURCES inquery_test.cpp
            data_from_xml_test.cpp
            )

set(XMLFILES object1.xml object2.xml object3.xml)

foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_executable(io_node_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(io_node_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME "XML::io_node"
         COMMAND io_node_test)
add_dependencies(check io_node_test)

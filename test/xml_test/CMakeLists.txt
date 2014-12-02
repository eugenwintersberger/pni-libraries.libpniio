set(SOURCES xml_test.cpp
            xml_attribute_test.cpp
            xml_to_nexus_test.cpp
            node_data_test.cpp
            node_test.cpp
            field_test.cpp
            group_test.cpp
            )

set(XMLFILES group1.xml
             group2.xml
             group3.xml
             field1.xml
             field2.xml
             field3.xml
             field4.xml
             field5.xml
             igor.xml
             field_test_data_scalar.xml
             field_test_data_array.xml
             node_from_bad_file.xml
             node_from_str.xml
             object_tree1.xml)


foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_subdirectory(dimensions)
add_subdirectory(attribute_data)
add_executable(xml_test ${SOURCES})
target_link_libraries(xml_test pniio ${CPPUNIT_LIBRARIES})
add_test(xml_test xml_test)

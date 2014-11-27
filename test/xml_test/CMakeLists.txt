set(SOURCES xml_test.cpp
            xml_attribute_test.cpp
            xml_lowlevel_test.cpp
            xml_node_data_test.cpp
            xml_node_test.cpp
            xml_field_test.cpp
            xml_group_test.cpp
            dimensions_test.cpp
            )

set(XMLFILES dim1.xml
             dim2.xml
             dim3.xml
             dim4.xml
             dim5.xml
             dim6.xml
             group1.xml
             group2.xml
             group3.xml
             field1.xml
             field2.xml
             field3.xml
             field4.xml
             field5.xml
             node_from_bad_file.xml
             node_from_str.xml
             object_tree1.xml)


foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_executable(xml_test ${SOURCES})
target_link_libraries(xml_test pniio ${CPPUNIT_LIBRARIES})
add_test(xml_test xml_test)

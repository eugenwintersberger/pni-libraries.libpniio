set(SOURCES #xml_test.cpp
    #xml_attribute_test.cpp
    #        xml_to_nexus_test.cpp
    #        node_test.cpp
    #        group_test.cpp
            )

set(XMLFILES group1.xml
             group2.xml
             group3.xml
             igor.xml
             object_tree1.xml)


foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_subdirectory(node)
add_subdirectory(object_data)
#add_subdirectory(dimensions)
#add_subdirectory(attribute_data)
#add_subdirectory(node_data)
#add_subdirectory(field)
#add_subdirectory(io_object)
#add_executable(xml_test ${SOURCES})
#target_link_libraries(xml_test pniio ${CPPUNIT_LIBRARIES})
#add_test(xml_test xml_test)

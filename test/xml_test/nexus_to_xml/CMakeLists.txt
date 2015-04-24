set(SOURCES nexus_to_xml_tests.cpp
            simple_structure_test.cpp   
            simple_structure_with_data_test.cpp  
            detector_with_transformation_test.cpp       
    )
    
set(XMLFILES simple_structure.nxs      
             simple_structure_with_data.nxs
             detector_with_transformation.nxs
   )

foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()


add_executable(nexus_to_xml_tests ${SOURCES})
target_link_libraries(nexus_to_xml_tests pniio ${CPPUNIT_LIBRARIES})

add_test("XML::nexus_to_xml_tests" nexus_to_xml_tests)

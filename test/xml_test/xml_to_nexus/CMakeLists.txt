set(SOURCES simple_structure_test.cpp
            simple_structure_with_data_test.cpp
            detector_with_transformation_test.cpp
            detector_master_file_test.cpp
    )
    
set(XMLFILES simple_structure.xml
             simple_structure_with_data.xml
             detector_with_transformation.xml
             detector_master_file.xml
             detector_data_file.xml
   )

foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()


add_executable(xml_to_nexus_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(xml_to_nexus_test pniio
                                        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test("XML::xml_to_nexus_tests" xml_to_nexus_test)
add_dependencies(check xml_to_nexus_test)

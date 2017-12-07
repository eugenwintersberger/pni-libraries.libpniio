set(SOURCES simple_structure_test.cpp
            simple_structure_with_data_test.cpp
            detector_with_transformation_test.cpp
    )

set(XMLFILES simple_structure.nxs
             simple_structure.xml
             simple_structure_with_data.nxs
             simple_structure_with_data.xml
             detector_with_transformation.nxs
             detector_with_transformation.xml
   )

foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()


add_executable(nexus_to_xml_test EXCLUDE_FROM_ALL ${SOURCES}
               $<TARGET_OBJECTS:xml_test_common>)
target_link_libraries(nexus_to_xml_test pniio Boost::unit_test_framework)

add_boost_logging_test("XML::nexus_to_xml_test" nexus_to_xml_test
                        ${PROJECT_BINARY_DIR}/test/xml_test/nexus_to_xml)

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


add_executable(xml_to_nexus_test ${SOURCES})
target_link_libraries(xml_to_nexus_test pniio Boost::unit_test_framework)

add_test(NAME "XML::xml_to_nexus_tests"
COMMAND xml_to_nexus_test
WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/xml_test/xml_to_nexus)

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set_property(TEST "XML::xml_to_nexus_tests" APPEND PROPERTY
        ENVIRONMENT "PATH=${PATH_STRING}")
endif()

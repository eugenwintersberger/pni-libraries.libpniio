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

add_executable(node_test ${SOURCES})
target_link_libraries(node_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME "XML::node" 
         COMMAND node_test 
         WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/test/xml_test/node")

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set_property(TEST "XML::node" APPEND PROPERTY
        ENVIRONMENT "PATH=${PATH_STRING}")
endif()

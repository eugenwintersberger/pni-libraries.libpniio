set(SOURCES inquery_test.cpp
            data_from_xml_test.cpp
            )

set(XMLFILES object1.xml object2.xml object3.xml)

foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_executable(io_node_test ${SOURCES})
target_link_libraries(io_node_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME "XML::io_node"
         COMMAND io_node_test)

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set_property(TEST "XML::io_node" APPEND PROPERTY
        ENVIRONMENT "PATH=${PATH_STRING}")
endif()

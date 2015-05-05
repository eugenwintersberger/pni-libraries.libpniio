set(XMLFILES igor.xml)


foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_subdirectory(node)
add_subdirectory(dimensions)
add_subdirectory(io_node)
add_subdirectory(data_node)
add_subdirectory(attribute)
add_subdirectory(field)
add_subdirectory(group)
add_subdirectory(link)
add_subdirectory(xml_to_nexus)
add_subdirectory(nexus_to_xml)


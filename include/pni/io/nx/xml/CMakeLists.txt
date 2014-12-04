set(HEADER_FILES attribute_data.hpp 
                 nexus_to_xml.hpp 
                 node_data.hpp 
                 xml_to_nexus.hpp 
                 node.hpp
                 io_object.hpp
                 field.hpp
                 group.hpp
                 attribute.hpp
                 dimensions.hpp
                 default.hpp
                 object_data.hpp
                 )

install(FILES ${HEADER_FILES} 
    DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io/nx/xml)

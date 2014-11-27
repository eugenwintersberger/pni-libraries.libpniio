set(HEADER_FILES attribute_data.hpp 
                 create_field_visitor.hpp 
                 create_group_visitor.hpp 
                 field2xml_visitor.hpp 
                 nexus2xml.hpp 
                 node_data.hpp 
                 xml_lowlevel.hpp 
                 xml_node.hpp
                 field.hpp
                 group.hpp
                 shape.hpp
                 attribute.hpp
                 )

install(FILES ${HEADER_FILES} 
    DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io/nx/xml)

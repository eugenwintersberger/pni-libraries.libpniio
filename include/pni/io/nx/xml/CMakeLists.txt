set(HEADER_FILES attribute_data.hpp 
                 create_field_visitor.hpp 
                 create_group_visitor.hpp 
                 dim2shape.hpp 
                 field2xml_visitor.hpp 
                 nexus2xml.hpp 
                 node_data.hpp 
                 shape2dim.hpp 
                 xml_lowlevel.hpp 
                 xml_node.hpp
                 shape.hpp)

install(FILES ${HEADER_FILES} 
    DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io/nx/xml)

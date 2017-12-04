set(HEADER_FILES nexus_to_xml.hpp 
                 data_node.hpp 
                 xml_to_nexus.hpp 
                 node.hpp
                 io_node.hpp
                 field.hpp
                 group.hpp
                 attribute.hpp
                 dimensions.hpp
                 default.hpp
                 array_utils.hpp
                 link.hpp)
                
set(SOURCE_FILES data_node.cpp 
                 node.cpp
                 io_node.cpp
                 dimensions.cpp
                 array_utils.cpp
                 field.cpp
                 link.cpp)

install(FILES ${HEADER_FILES} 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/io/nx/xml)

set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)
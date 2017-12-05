set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/nexus_to_xml.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/data_node.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/xml_to_nexus.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/node.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/io_node.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/field.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/group.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/attribute.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/dimensions.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/default.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array_utils.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/link.hpp)
                
set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/data_node.cpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/node.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/io_node.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/dimensions.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array_utils.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/field.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/link.cpp)

install(FILES ${HEADER_FILES} 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/io/nx/xml)

set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)
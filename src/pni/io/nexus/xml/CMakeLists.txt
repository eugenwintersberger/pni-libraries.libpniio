set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/object_builder.hpp 
	             ${CMAKE_CURRENT_SOURCE_DIR}/group_builder.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/builder_factory.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/datatype_builder.hpp
                )
                
set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/object_builder.cpp 
	             ${CMAKE_CURRENT_SOURCE_DIR}/group_builder.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/builder_factory.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/node.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/io_node.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/data_node.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/dimensions.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/field_builder.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/field_node.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/datatype_builder.cpp
       )

install(FILES ${HEADER_FILES} 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/io/nexus/xml)

set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)
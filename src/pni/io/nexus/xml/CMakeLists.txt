set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/object_builder.hpp 
	             ${CMAKE_CURRENT_SOURCE_DIR}/group_builder.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/builder_factory.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/datatype_builder.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/dataspace_builder.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/dimension_node_handler.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/dataset_creation_list_builder.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/data_writer.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/attribute_builder.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/link_builder.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/create.hpp
                )
                
set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/object_builder.cpp 
	             ${CMAKE_CURRENT_SOURCE_DIR}/group_builder.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/builder_factory.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/node.cpp	             	             	           
	             ${CMAKE_CURRENT_SOURCE_DIR}/field_builder.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/datatype_builder.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/dataspace_builder.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/dimension_node_handler.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/dataset_creation_list_builder.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/data_writer.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/attribute_builder.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/link_builder.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/create.cpp
       )

install(FILES ${HEADER_FILES} 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/io/nexus/xml)

set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)
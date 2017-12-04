set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/as_attribute.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/as_field.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/as_group.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/as_link.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/close.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/create_attribute.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/create_field.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/create_group.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_attribute.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_child.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_class.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_name.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_filename.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_object.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_parent.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_path.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_rank.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_shape.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_size.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_type.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_unit.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_root.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/grow.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/is_attribute.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/object_predicates.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/iterators.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/is_class.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/is_field.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/is_group.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/is_valid.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/is_link.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/read.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/set_class.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/set_unit.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/write.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/utils.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_children.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_attributes.hpp
                 )
set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp)

install(FILES ${HEADER_FILES} 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/io/nx/algorithms)
   
set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)

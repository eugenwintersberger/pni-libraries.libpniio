set(HEADER_FILES as_attribute.hpp 
                 as_field.hpp 
                 as_group.hpp 
                 close.hpp 
                 create_attribute.hpp 
                 create_field.hpp 
                 create_group.hpp 
                 get_attribute.hpp 
                 get_child.hpp 
                 get_class.hpp 
                 get_name.hpp 
                 get_filename.hpp
                 get_object.hpp 
                 get_parent.hpp 
                 get_path.hpp 
                 get_rank.hpp 
                 get_shape.hpp 
                 get_size.hpp 
                 get_type.hpp 
                 get_unit.hpp 
                 get_root.hpp
                 grow.hpp 
                 is_attribute.hpp 
                 object_predicates.hpp
                 iterators.hpp
                 is_class.hpp 
                 is_field.hpp 
                 is_group.hpp 
                 is_valid.hpp 
                 read.hpp 
                 set_class.hpp 
                 set_unit.hpp 
                 write.hpp
                 utils.hpp
                 get_children.hpp
                 get_attributes.hpp
                 )

install(FILES ${HEADER_FILES} 
    DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io/nx/algorithms)

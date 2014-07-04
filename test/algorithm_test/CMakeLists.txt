set(SOURCES as_attribute_test.cpp
            as_field_test.cpp
            as_group_test.cpp
            create_attribute_test.cpp
            create_field_test.cpp
            create_group_test.cpp
            close_test.cpp
            get_attribute_test.cpp
            get_child_test.cpp
            get_child_by_index_test.cpp
            get_children_test.cpp
            get_class_test.cpp
            get_object_test.cpp
            get_parent_test.cpp
            get_root_test.cpp
            get_rank_test.cpp
            get_shape_test.cpp
            get_size_test.cpp
            get_type_test.cpp
            get_unit_test.cpp
            grow_test.cpp
            is_attribute_test.cpp
            is_class_test.cpp
            is_field_test.cpp
            is_group_test.cpp
            is_valid_test.cpp
            read_test.cpp
            set_class_test.cpp
            set_unit_test.cpp
            write_test.cpp
            algorithm_test.cpp
            get_name_test.cpp
            #get_path_test.cpp
           )

add_executable(algorithm_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(algorithm_test pniio ${CPPUNIT_LIBRARIES})
add_test(algorithm_test algorithm_test)


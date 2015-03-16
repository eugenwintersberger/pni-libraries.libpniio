set(SOURCES 
algorithm_test.cpp
create_attribute_test.cpp
create_field_test.cpp
create_group_test.cpp
get_attribute_test.cpp
get_child_test.cpp
get_class_test.cpp
get_object_test.cpp
get_rank_test.cpp
get_shape_test.cpp
get_type_test.cpp
get_unit_test.cpp
grow_test.cpp
is_class_test.cpp
read_write_test.cpp
set_class_test.cpp
set_unit_test.cpp
           )


add_subdirectory(inquiry_conversion_test)
add_subdirectory(common_test)
add_executable(algorithm_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(algorithm_test pniio ${CPPUNIT_LIBRARIES})
add_test(algorithm_test algorithm_test)


set(SOURCES close_test.cpp
            common_test.cpp
            get_filename_test.cpp
            get_name_test.cpp
            get_parent_test.cpp
            get_path_test.cpp
            get_root_test.cpp
            get_size_test.cpp
            is_valid_test.cpp
           )


add_executable(common_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(common_test pniio ${CPPUNIT_LIBRARIES})
add_test("algorithms:common" common_test)


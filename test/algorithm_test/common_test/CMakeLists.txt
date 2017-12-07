set(SOURCES close_test.cpp
            get_filename_test.cpp
            get_name_test.cpp
            get_parent_test.cpp
            get_path_test.cpp
            get_root_test.cpp
            get_size_test.cpp
            is_valid_test.cpp
           )


set_boost_test_definitions(SOURCES "testing common algorithms")

add_executable(common_test EXCLUDE_FROM_ALL ${SOURCES}
               $<TARGET_OBJECTS:test_common>
               $<TARGET_OBJECTS:algorithm_common>
               )
target_link_libraries(common_test pniio Boost::unit_test_framework)

#add_boost_logging_test("algorithms:common"
#                       common_test
#                       ${PROJECT_BINARY_DIR}/test/algorithm_test/common_test)

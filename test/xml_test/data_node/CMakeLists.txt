set(SOURCES child_node_io_test.cpp
            attribute_node_io_test.cpp
    )

add_executable(data_node_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(data_node_test pniio 
                                     ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test("XML::data_node_tests" data_node_test)
add_dependencies(check data_node_test)

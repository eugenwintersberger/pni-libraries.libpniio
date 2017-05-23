set(SOURCES child_node_io_test.cpp
            data_node_fixture.cpp
            attribute_node_io_test.cpp
    )

set_source_files_properties(child_node_io_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=testing data_node operations")
add_executable(data_node_test ${SOURCES})
target_link_libraries(data_node_test pniio 
                                     ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test("XML::data_node_tests" data_node_test)

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set_property(TEST "XML::data_node_tests" APPEND PROPERTY
        ENVIRONMENT "PATH=${PATH_STRING}")
endif()

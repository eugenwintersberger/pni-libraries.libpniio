set(SOURCES xml_test.cpp
	        group_builder_test.cpp
	        xml_base_fixture.cpp
	        xml_test_common.cpp
	        node_test.cpp
	        field_builder_test.cpp
	        datatype_builder_test.cpp
	        dataspace_builder_test.cpp
	        scalar_attribute_builder_test.cpp
	        array_attribute_builder_test.cpp
	        builder_fixture.cpp
	        )
	      
	      
set(DATAFILES group_builder.xml
              scalar_attribute_test.xml
              array_attribute_test.xml)

foreach(F ${DATAFILES})
	configure_file(${F} ${F} COPYONLY)
endforeach()
	       
set_boost_test_definitions(SOURCES "Testing Nexus xml stack")
add_executable(nexus_xml_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(nexus_xml_test pniio Boost::unit_test_framework)
add_dependencies(check nexus_xml_test)
add_boost_logging_test("nexus::xml" nexus_xml_test
	                   ${CMAKE_CURRENT_BINARY_DIR})
	                  
add_subdirectory(dimensions)
add_subdirectory(node)
add_subdirectory(io_node)
add_subdirectory(field)
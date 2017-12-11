set(SOURCES xml_test.cpp
	        group_builder_test.cpp
	        )
	      
	      
set(DATAFILES group_builder.xml)

foreach(F ${DATAFILES})
	configure_file(${F} ${F} COPYONLY)
endforeach()
	       
set_boost_test_definitions(SOURCES "Testing Nexus xml stack")
add_executable(nexus_xml_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(nexus_xml_test pniio Boost::unit_test_framework)
add_dependencies(check nexus_xml_test)
add_boost_logging_test("nexus::xml" nexus_xml_test
	                   ${CMAKE_CURRENT_BINARY_DIR})
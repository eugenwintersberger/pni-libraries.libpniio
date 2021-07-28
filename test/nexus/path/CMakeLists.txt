set(SOURCES path_test.cpp
	        creation_test.cpp
	        equality_test.cpp
	        match_test.cpp
	        pop_test.cpp
	        push_test.cpp
	        element_equality_test.cpp
	        element_match_test.cpp
	        has_attribute_test.cpp
	        has_class_test.cpp
	        has_file_test.cpp
	        has_name_test.cpp
	        is_absolute_test.cpp
	        is_complete_test.cpp
	        is_empty_test.cpp
	        is_root_element_test.cpp
	        join_test.cpp
	        make_relative_test.cpp
	        split_path_test.cpp
	        object_element_test.cpp
	        parser_test.cpp
	        path_object_test.cpp
	        is_unique_test.cpp
	        conversion_test.cpp
	        get_path_test.cpp
	        get_objects.cpp
           )
          
set(XML_FILES detector_with_transformation.xml
	          simple_structure.xml
	          multi_entry.xml
	          multi_detector.xml
	         )
	        
foreach(XML_FILE ${XML_FILES})
	configure_file(${XML_FILE} ${XML_FILE} COPYONLY)
endforeach()

set_boost_test_definitions(SOURCES "Testing nexus::Path")
add_executable(nexus_path_tests EXCLUDE_FROM_ALL ${SOURCES})
add_dependencies(check nexus_path_tests)
target_link_libraries(nexus_path_tests pninexus Boost::unit_test_framework)
add_boost_logging_test("nexus::path" nexus_path_tests
                       ${PROJECT_BINARY_DIR}/test/nexus/path)


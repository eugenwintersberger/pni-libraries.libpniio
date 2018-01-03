add_subdirectory(version)
add_subdirectory(file)
add_subdirectory(algorithms)
add_subdirectory(xml)
add_subdirectory(path)

set(SOURCES base_class_factory_test.cpp)

set_boost_test_definitions(SOURCES "Testing BaseClassFactory functionality")
add_executable(nexus_base_class_factory_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(nexus_base_class_factory_test pniio Boost::unit_test_framework)
add_dependencies(check nexus_base_class_factory_test)

add_boost_logging_test("nexus::base_class_factory" nexus_base_class_factory_test
	                   ${CMAKE_CURRENT_BINARY_DIR})
	               
set(SOURCES field_test.cpp)

set_boost_test_definitions(SOURCES "Testing fields")
add_executable(nexus_field_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(nexus_field_test pniio Boost::unit_test_framework)
add_dependencies(check nexus_field_test)

add_boost_logging_test("nexus::field" nexus_field_test
                       ${CMAKE_CURRENT_BINARY_DIR})
	                  
	                  
set(PREDICATE_SOURCES predicate_test.cpp)
set_boost_test_definitions(PREDICATE_SOURCES "Testing nexus predicates")
add_executable(nexus_predicate_test EXCLUDE_FROM_ALL ${PREDICATE_SOURCES})
target_link_libraries(nexus_predicate_test pniio Boost::unit_test_framework)
add_dependencies(check nexus_predicate_test)
add_boost_logging_test("nexus::predicates" nexus_predicate_test
	                   ${CMAKE_CURRENT_BINARY_DIR})	   
	                 
	                 
set(HDF5TEST_SOURCES hdf5_array_test.cpp                     
                    hdf5_support_fixture.cpp)
set_boost_test_definitions(HDF5TEST_SOURCES "Testing HDF5 support")
add_executable(nexus_hdf5_support_test EXCLUDE_FROM_ALL ${HDF5TEST_SOURCES})
target_link_libraries(nexus_hdf5_support_test pniio Boost::unit_test_framework)
add_dependencies(check nexus_hdf5_support_test)
add_boost_logging_test("nexus::hdf5_support" nexus_hdf5_support_test
	                   ${CMAKE_CURRENT_BINARY_DIR})	 
	                  
set(CONTAINER_TEST_SOURCES node_list_test.cpp
                           dataset_list_test.cpp
                           group_list_test.cpp
                           attribute_list_test.cpp
                           container_test_fixture.cpp)
configure_file(container_test.xml container_test.xml COPYONLY)
set_boost_test_definitions(CONTAINER_TEST_SOURCES "Testing NeXus containers")
add_executable(nexus_container_test EXCLUDE_FROM_ALL ${CONTAINER_TEST_SOURCES})
target_link_libraries(nexus_container_test pniio Boost::unit_test_framework)
add_dependencies(check nexus_container_test)
add_boost_logging_test("nexus::containers" nexus_container_test
	                   ${CMAKE_CURRENT_BINARY_DIR}) 
             
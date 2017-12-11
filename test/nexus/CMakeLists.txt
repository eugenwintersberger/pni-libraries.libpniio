add_subdirectory(version)
add_subdirectory(file)
add_subdirectory(algorithms)
add_subdirectory(xml)

set(SOURCES base_class_test.cpp)

set_boost_test_definitions(SOURCES "Testing BaseClass functionality")
add_executable(nexus_base_class_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(nexus_base_class_test pniio Boost::unit_test_framework)
add_dependencies(check nexus_base_class_test)

add_boost_logging_test("nexus::base_class" nexus_base_class_test
	                   ${CMAKE_CURRENT_BINARY_DIR})
	                  
	                  
set(PREDICATE_SOURCES predicate_test.cpp)
set_boost_test_definitions(PREDICATE_SOURCES "Testing nexus predicates")
add_executable(nexus_predicate_test EXCLUDE_FROM_ALL ${PREDICATE_SOURCES})
target_link_libraries(nexus_predicate_test pniio Boost::unit_test_framework)
add_dependencies(check nexus_predicate_test)
add_boost_logging_test("nexus::predicates" nexus_predicate_test
	                   ${CMAKE_CURRENT_BINARY_DIR})	                 
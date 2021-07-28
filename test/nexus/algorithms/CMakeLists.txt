set(SOURCES search_test.cpp
            get_type_id_test.cpp)

set_boost_test_definitions(SOURCES "Testing NeXus algorithms")
add_executable(nexus_algorithm_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(nexus_algorithm_test pninexus Boost::unit_test_framework)
add_dependencies(check nexus_algorithm_test)
add_boost_logging_test("nexus::algorithms" nexus_algorithm_test
	                   ${CMAKE_CURRENT_BINARY_DIR})
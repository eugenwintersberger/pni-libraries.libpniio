add_subdirectory(version)
add_subdirectory(file)

set(SOURCES base_class_test.cpp)

set_boost_test_definitions(SOURCES "Testing BaseClass functionality")
add_executable(nexus_base_class_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(nexus_base_class_test pniio Boost::unit_test_framework)
add_dependencies(check nexus_base_class_test)

add_boost_logging_test("nexus::base_class" nexus_base_class_test
	                   ${CMAKE_CURRENT_BINARY_DIR})
set(SOURCES nexus_file_test.cpp
	        nexus_file_creation_test.cpp
	        nexus_file_open_test.cpp
	        nexus_file_check_test.cpp
	        )
	       
set_boost_test_definitions(SOURCES "Testing Nexus file creation and opening")

add_executable(nexus_file_test EXCLUDE_FROM_ALL ${SOURCES})
add_dependencies(check nexus_file_test)
target_link_libraries(nexus_file_test pniio Boost::unit_test_framework)

add_boost_logging_test("nexus::files_test" nexus_file_test
	                   ${PROJECT_BINARY_DIR}/test/nexus/file)
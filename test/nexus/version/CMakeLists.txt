set(SOURCES version_test.cpp
            string_conversion_test.cpp
            version_comparison_test.cpp)


set_boost_test_definitions(SOURCES "testing Version class")

add_executable(nexus_version_test EXCLUDE_FROM_ALL ${SOURCES})
add_dependencies(check nexus_version_test)
target_link_libraries(nexus_version_test pninexus Boost::unit_test_framework)

add_boost_logging_test("nexus::version_test" nexus_version_test
	                   ${PROJECT_BINARY_DIR}/test/nexus)
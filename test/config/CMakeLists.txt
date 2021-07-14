#need to define the version of the library
set(SOURCES  configuration_test.cpp)

set_boost_test_definitions(SOURCES "testing the configuration facilities")
add_executable(config_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(config_test pninexus Boost::unit_test_framework)
add_dependencies(check config_test)

configure_file(pni.cfg.cmake pni.cfg)

add_boost_logging_test("config_test" config_test ${PROJECT_BINARY_DIR}/test/config)

set(SOURCES create_attribute_test.cpp
            get_attribute_test.cpp
            get_attributes_test.cpp
)


set_boost_test_definitions(SOURCES "testing attribute algorithms")

add_executable(algo_attribute_test EXCLUDE_FROM_ALL ${SOURCES}
               $<TARGET_OBJECTS:test_common>
               $<TARGET_OBJECTS:algorithm_common>)

target_link_libraries(algo_attribute_test pniio Boost::unit_test_framework)

#add_boost_logging_test("algorithms:attribute_test"
#                       algo_attribute_test
#                       ${PROJECT_BINARY_DIR}/test/algorithm_test/attribute_test)

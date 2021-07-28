#need to define the version of the library
set(SOURCES index_map_tests.cpp
            dynamic_cindex_map_test.cpp
            fixed_dim_cindex_map_test.cpp
            static_cindex_map_test.cpp
            cindex_implementation_test.cpp
            )

# compiler definitions are set in index_map_test.cpp. This is an exception
# and only necessary as we have to implement the main function here
# by ourselves. 

add_executable(index_maps_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(index_maps_test pninexus Boost::unit_test_framework)
add_dependencies(check index_maps_test)

add_boost_logging_test("index_maps_test"
                       index_maps_test
                       ${PROJECT_BINARY_DIR}/test/index_maps)

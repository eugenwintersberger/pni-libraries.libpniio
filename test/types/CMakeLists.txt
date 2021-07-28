#need to define the version of the library
set(SOURCES binary_test.cpp
            bool_test.cpp
            type_class_map_test.cpp
            type_id_map_test.cpp
            id_type_map_test.cpp
            container_trait_test.cpp
            type_id_test.cpp
            type_info_test.cpp
            type_id_from_str_test.cpp
            str_from_type_id_test.cpp
    )

set_boost_test_definitions(SOURCES "testing type features")

add_executable(type_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(type_test pninexus Boost::unit_test_framework)

add_executable(show_type_info EXCLUDE_FROM_ALL show_type_info.cpp)
target_link_libraries(show_type_info pninexus)
add_dependencies(check type_test show_type_info)


add_subdirectory(conversion)
add_subdirectory(traits)

add_boost_logging_test("type_test" type_test ${PROJECT_BINARY_DIR}/test/types)


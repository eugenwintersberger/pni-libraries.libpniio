set(SOURCES as_attribute_test.cpp
            as_field_test.cpp
            as_group_test.cpp
            is_field_test.cpp
            is_attribute_test.cpp
            is_group_test.cpp
            )


set_source_files_properties(as_attribute_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=testing inquiry attributes")
add_executable(inquiry_conversion_test ${SOURCES}
               $<TARGET_OBJECTS:test_common>
               $<TARGET_OBJECTS:algorithm_common>)
target_link_libraries(inquiry_conversion_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("algorithms:inquiry_conversion" inquiry_conversion_test)


if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set_property(TEST "algorithms:inquiry_conversion" APPEND PROPERTY
            ENVIRONMENT "PATH=${PATH_STRING}")
endif()

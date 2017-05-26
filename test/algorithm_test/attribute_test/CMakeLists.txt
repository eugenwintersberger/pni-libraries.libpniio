set(SOURCES create_attribute_test.cpp
            get_attribute_test.cpp
            get_attributes_test.cpp
)


set_source_files_properties(create_attribute_test.cpp PROPERTIES
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=testing attribute algorithms")
add_executable(algo_attribute_test ${SOURCES}
               $<TARGET_OBJECTS:test_common>
               $<TARGET_OBJECTS:algorithm_common>)

target_link_libraries(algo_attribute_test pniio Boost::unit_test_framework)


add_test(NAME "algorithms:attribute_test"
         COMMAND algo_attribute_test)

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set_property(TEST "algorithms:attribute_test" APPEND PROPERTY
        ENVIRONMENT "PATH=${PATH_STRING}")
endif()

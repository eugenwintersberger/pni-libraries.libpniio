set(SOURCES slice_parser_test.cpp
            vector_parser_test.cpp
            int8_vector_parser_test.cpp
            uint8_vector_parser_test.cpp
            float32_vector_parser_test.cpp
            bool_vector_parser_test.cpp
            string_vector_parser_test.cpp
           )

set_source_files_properties(slice_parser_test.cpp PROPERTIES
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=testing object parsers")
add_executable(object_parsers_test ${SOURCES} )
target_link_libraries(object_parsers_test pniio Boost::unit_test_framework)
add_test(NAME "parsers:object_parsers"
COMMAND object_parsers_test
WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/parser_test/object_parsers)

if(CMAKE_SYSTEM_NAME MATCHES Windows)
  set_property(TEST "parsers:object_parsers" APPEND PROPERTY
  ENVIRONMENT "PATH=${PATH_STRING}")
endif()

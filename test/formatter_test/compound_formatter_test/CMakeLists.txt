set(SOURCES
            int8_vector_formatter_test.cpp
            bool_vector_formatter_test.cpp
            mdarray_formatter_test.cpp
            array_formatter_test.cpp
           )

set_source_files_properties(int8_vector_formatter_test.cpp PROPERTIES
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=Testing compound formatters")
add_executable(compound_formatter_test ${SOURCES} )
target_link_libraries(compound_formatter_test pniio Boost::unit_test_framework)
add_test(NAME "formatters:compound_formatters"
COMMAND compound_formatter_test
WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/formatter_test/compound_formatter_test)

if(CMAKE_SYSTEM_NAME MATCHES Windows)
  set_property(TEST "formatters:compound_formatters" APPEND PROPERTY
  ENVIRONMENT "PATH=${PATH_STRING}")
endif()

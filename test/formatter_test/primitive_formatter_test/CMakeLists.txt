set(SOURCES
            uint8_formatter_test.cpp
            uint16_formatter_test.cpp
            uint32_formatter_test.cpp
            uint64_formatter_test.cpp
            int8_formatter_test.cpp
            int16_formatter_test.cpp
            int32_formatter_test.cpp
            int64_formatter_test.cpp
            float32_formatter_test.cpp
            float64_formatter_test.cpp

            complex32_formatter_test.cpp

            bool_formatter_test.cpp
            value_formatter_test.cpp
           )

set_source_files_properties(bool_formatter_test.cpp PROPERTIES
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=Testing primitive formatters")
add_executable(primitive_formatter_test ${SOURCES})
target_link_libraries(primitive_formatter_test pniio Boost::unit_test_framework)
add_test(NAME "formatters:primitive_formatters"
COMMAND primitive_formatter_test
WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/formatter_test/primitive_formatter_test)

if(CMAKE_SYSTEM_NAME MATCHES Windows)
  set_property(TEST "formatters:primitive_formatters" APPEND PROPERTY
  ENVIRONMENT "PATH=${PATH_STRING}")
endif()

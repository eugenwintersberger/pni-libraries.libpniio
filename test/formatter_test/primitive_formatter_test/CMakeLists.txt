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
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; \
                                                 BOOST_TEST_MODULE=Testing primitive formatters")
add_executable(primitive_formatter_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(primitive_formatter_test pniio 
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("formatters:primitive_formatters" primitive_formatter_test)

add_dependencies(check primitive_formatter_test)


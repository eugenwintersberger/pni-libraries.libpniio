set(SOURCES 
            int8_vector_formatter_test.cpp
            bool_vector_formatter_test.cpp
            mdarray_formatter_test.cpp
            array_formatter_test.cpp
           )

set_source_files_properties(int8_vector_formatter_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; 
                            BOOST_TEST_MODULE=Testing compound formatters")
add_executable(compound_formatter_test EXCLUDE_FROM_ALL ${SOURCES} )
target_link_libraries(compound_formatter_test pniio
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("formatters:compound_formatters" compound_formatter_test)

add_dependencies(check compound_formatter_test)


set(SOURCES primitive_formatters_test.cpp
            float32_formatter_test.cpp
            float64_formatter_test.cpp

            complex32_formatter_test.cpp
           )

add_executable(primitive_formatter_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(primitive_formatter_test pniio ${CPPUNIT_LIBRARIES})
add_test("formatters:primitive_formatters" primitive_formatter_test)


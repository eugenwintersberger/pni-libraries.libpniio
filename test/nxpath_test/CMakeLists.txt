set(SOURCES nxpath_tests.cpp
            filepath_parser_test.cpp
            nxpath_parser_test.cpp
            element_parser_test.cpp
            elements_parser_test.cpp
           )

add_executable(nxpath_tests ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(nxpath_tests pniio ${CPPUNIT_LIBRARIES})
add_test(nxpath_tests nxpath_tests)


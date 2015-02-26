set(SOURCES nxpath_tests.cpp
            nxpath_test.cpp
            nxpath_create_test.cpp
           )

set(PARSERSRC nxpath_parser_tests.cpp 
              nxpath_parser_test.cpp
              element_parser_test.cpp
              elements_parser_test.cpp
           )
set(UTILSRC nxpath_utils_tests.cpp
            test_object_element.cpp
           )
add_executable(nxpath_parser_tests ${PARSERSRC} $<TARGET_OBJECTS:test_common>)
add_executable(nxpath_tests ${SOURCES} $<TARGET_OBJECTS:test_common>)
add_executable(nxpath_utils_test ${UTILSRC} $<TARGET_OBJECTS:test_common>)
target_link_libraries(nxpath_tests pniio ${CPPUNIT_LIBRARIES})
target_link_libraries(nxpath_parser_tests pniio ${CPPUNIT_LIBRARIES})
target_link_libraries(nxpath_utils_test pniio ${CPPUNIT_LIBRARIES})
add_test(nxpath_tests nxpath_tests)
add_test("nxpath:parser_tests" nxpath_parser_tests)
add_test("nxpath:utilities" nxpath_utils_test)


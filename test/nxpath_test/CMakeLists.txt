set(SOURCES nxpath_test.cpp
            filepath_parser_test.cpp
           )

add_executable(nxpath_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(nxpath_test pniio ${CPPUNIT_LIBRARIES})
add_test(nxpath_test nxpath_test)


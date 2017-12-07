set(SOURCES group_test.cpp )

set(XMLFILES  group1.xml group2.xml group3.xml)

foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_executable(group_test EXCLUDE_FROM_ALL ${SOURCES}
               $<TARGET_OBJECTS:test_common>)
target_link_libraries(group_test pniio Boost::unit_test_framework)
add_boost_logging_test("XML::group_tests" group_test
${PROJECT_BINARY_DIR}/test/xml_test/group)

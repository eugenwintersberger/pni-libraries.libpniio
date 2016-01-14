set(SOURCES group_test.cpp )

set(XMLFILES  group1.xml group2.xml group3.xml)

foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_executable(group_test EXCLUDE_FROM_ALL ${SOURCES}
               $<TARGET_OBJECTS:test_common>)
target_link_libraries(group_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME "XML::group_tests"
         COMMAND group_test)
add_dependencies(check group_test)

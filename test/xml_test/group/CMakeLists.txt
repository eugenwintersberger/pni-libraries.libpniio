set(SOURCES group_tests.cpp
            group_test.cpp            
     )

set(XMLFILES  group1.xml group2.xml group3.xml)


foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_executable(group_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(group_test pniio ${CPPUNIT_LIBRARIES})
add_test(NAME "XML::group_tests"
         COMMAND group_test)

set(SOURCES read_fixture.cpp
            write_fixture.cpp
            inquery_fixture.cpp
            dimensions_test.cpp
            )

set(XMLFILES dim1.xml
             dim2.xml
             dim3.xml
             dim4.xml
             dim5.xml
             dim6.xml)


foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_executable(dimensions_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(dimensions_test pniio ${CPPUNIT_LIBRARIES})
add_test(NAME "XML::dimensions"
         COMMAND dimensions_test)

set(SOURCES read_test.cpp
            write_test.cpp
            inquery_test.cpp
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
target_link_libraries(dimensions_test pniio 
                                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME "XML::dimensions"
         COMMAND dimensions_test)
add_dependencies(check dimensions_test)

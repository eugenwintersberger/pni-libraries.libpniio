set(SOURCES read_test.cpp
            write_test.cpp
            inquery_test.cpp
            dimensions_fixture.cpp
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

set_source_files_properties(read_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; \
                            BOOST_TEST_MODULE=testing xml dimensions operations")
add_executable(dimensions_test EXCLUDE_FROM_ALL ${SOURCES}
    $<TARGET_OBJECTS:xml_test_common>)
target_link_libraries(dimensions_test pniio 
                                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME "XML::dimensions"
         COMMAND dimensions_test)
add_dependencies(check dimensions_test)

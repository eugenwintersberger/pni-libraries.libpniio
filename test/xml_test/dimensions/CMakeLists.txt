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

set_boost_test_definitions(SOURCES "testing xml dimensions operations")
add_executable(dimensions_test ${SOURCES} $<TARGET_OBJECTS:xml_test_common>)
target_link_libraries(dimensions_test pniio Boost::unit_test_framework)
add_boost_logging_test("XML::dimensions" dimensions_test
${PROJECT_BINARY_DIR}/test/xml_test/dimensions)

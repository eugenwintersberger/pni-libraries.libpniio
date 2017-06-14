set(SOURCES internal_link_test.cpp
            external_link_test.cpp
            )

set(XMLFILES internal_link_test.xml external_link_test.xml)

foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_executable(link_test ${SOURCES})
target_link_libraries(link_test pniio Boost::unit_test_framework)
add_boost_logging_test("XML::link_tests" link_test
${PROJECT_BINARY_DIR}/test/xml_test/link)

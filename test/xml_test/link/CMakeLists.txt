set(SOURCES internal_link_test.cpp
            external_link_test.cpp
            )

set(XMLFILES internal_link_test.xml external_link_test.xml)

foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPY_ONLY)
endforeach()

add_executable(link_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(link_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME "XML::link_tests"
         COMMAND link_test)
add_dependencies(check link_test)

set(SOURCES internal_link_test.cpp
            external_link_test.cpp
            )

set(XMLFILES internal_link_test.xml external_link_test.xml)

foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_executable(link_test ${SOURCES})
target_link_libraries(link_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME "XML::link_tests"
         COMMAND link_test)

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set_property(TEST "XML::link_tests" APPEND PROPERTY
        ENVIRONMENT "PATH=${PATH_NAME}")
endif()

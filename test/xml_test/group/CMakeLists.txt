set(SOURCES group_test.cpp )

set(XMLFILES  group1.xml group2.xml group3.xml)

foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_executable(group_test ${SOURCES}
               $<TARGET_OBJECTS:test_common>)
target_link_libraries(group_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME "XML::group_tests"
         COMMAND group_test)

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)     
    set_property(TEST "XML::group_tests" APPEND PROPERTY
        ENVIRONMENT "PATH=${PATH_STRING}")
endif()

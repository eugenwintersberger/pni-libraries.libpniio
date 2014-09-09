set(SOURCES nexus_lowlevel_test.cpp
            NXAttributeTest.cpp
            NXFieldTest.cpp
            NXFileTest.cpp
            NXGroupTest.cpp
            nxlink_test.cpp
            NXSelectionTest.cpp
            recursive_iterator_test.cpp
           )

add_executable(nexus_lowlevel_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(nexus_lowlevel_test pniio ${CPPUNIT_LIBRARIES})
add_test(nexus_lowlevel_test nexus_lowlevel_test)


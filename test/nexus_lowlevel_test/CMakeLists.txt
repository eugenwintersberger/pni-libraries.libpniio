set(SOURCES nexus_lowlevel_test.cpp
            NXAttributeTest.cpp
            NXFieldTest.cpp
            NXFileTest.cpp
            NXGroupTest.cpp
            nxlink_test.cpp
            NXSelectionTest.cpp
            flat_group_test.cpp
           )

set(NXFILESRC nxfile_tests.cpp
              nxfile_creation_test.cpp 
              nxfile_open_single_file_test.cpp
              nxfile_open_family_file_test.cpp
    )

add_executable(nxfile_tests ${NXFILESRC} $<TARGET_OBJECTS:test_common>)
add_executable(nexus_lowlevel_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(nexus_lowlevel_test pniio ${CPPUNIT_LIBRARIES})
target_link_libraries(nxfile_tests pniio ${CPPUNIT_LIBRARIES})
add_test(nexus_lowlevel_test nexus_lowlevel_test)
add_test("Nexus_Layer_1:nxfile" nxfile_tests)

add_custom_target(cleanup COMMAND rm -rf *.nxs *.h5)

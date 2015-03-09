set(SOURCES nexus_lowlevel_test.cpp
            NXAttributeTest.cpp
            NXFieldTest.cpp
            NXGroupTest.cpp
            nxlink_test.cpp
            NXSelectionTest.cpp
            flat_group_test.cpp
           )

set(NXFILESRC nxfile_tests.cpp
              nxfile_creation_test.cpp 
              nxfile_open_single_file_test.cpp
              nxfile_open_family_file_test.cpp
              nxfile_misc_test.cpp
    )

set(NXGROUPSRC nxgroup_tests.cpp
               nxgroup_creation_test.cpp
               nxgroup_access_test.cpp
               nxgroup_misc_test.cpp
              )

set(NXFIELDSRC nxfield_tests.cpp
               nxfield_creation_test.cpp
               nxfield_io_test.cpp
               nxfield_grow_test.cpp
               nxfield_partial_io_test.cpp
    )

add_executable(nxfile_tests ${NXFILESRC} $<TARGET_OBJECTS:test_common>)
add_executable(nexus_lowlevel_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
add_executable(nxgroup_tests ${NXGROUPSRC} $<TARGET_OBJECTS:test_common>)
add_executable(nxfield_tests ${NXFIELDSRC} $<TARGET_OBJECTS:test_common>)

target_link_libraries(nexus_lowlevel_test pniio ${CPPUNIT_LIBRARIES})
target_link_libraries(nxfile_tests pniio ${CPPUNIT_LIBRARIES})
target_link_libraries(nxgroup_tests pniio ${CPPUNIT_LIBRARIES})
target_link_libraries(nxfield_tests pniio ${CPPUNIT_LIBRARIES})

add_test(nexus_lowlevel_test nexus_lowlevel_test)
add_test("Nexus_Layer_1:nxfile" nxfile_tests)
add_test("Nexus_Layer_1:nxgroup" nxgroup_tests)
add_test("Nexus_Layer_1:nxfield" nxfield_tests)

add_custom_target(cleanup COMMAND rm -rf *.nxs *.h5)

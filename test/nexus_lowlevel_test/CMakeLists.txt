set(SOURCES nexus_lowlevel_test.cpp
            nxlink_test.cpp
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
               nxfield_inquiry_test.cpp
    )

set(NXATTRSRC nxattribute_tests.cpp
              nxattribute_creation_test.cpp
              nxattribute_access_test.cpp
              nxattribute_io_test.cpp
              nxattribute_view_io_test.cpp
              nxattribute_partial_io_test.cpp
              nxattribute_manage_test.cpp
   )

set(NXLINKSRC nxlink_tests.cpp
              nxlink_internal_test.cpp
              nxlink_external_test.cpp
   )

add_executable(nxfile_tests EXCLUDE_FROM_ALL ${NXFILESRC} $<TARGET_OBJECTS:test_common>)
add_executable(nexus_lowlevel_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
add_executable(nxgroup_tests EXCLUDE_FROM_ALL ${NXGROUPSRC} $<TARGET_OBJECTS:test_common>)
add_executable(nxfield_tests EXCLUDE_FROM_ALL ${NXFIELDSRC} $<TARGET_OBJECTS:test_common>)
add_executable(nxattribute_tests EXCLUDE_FROM_ALL ${NXATTRSRC} $<TARGET_OBJECTS:test_common>)
add_executable(nxlink_tests EXCLUDE_FROM_ALL ${NXLINKSRC} $<TARGET_OBJECTS:test_common>)

target_link_libraries(nexus_lowlevel_test pniio ${CPPUNIT_LIBRARIES})
target_link_libraries(nxfile_tests pniio ${CPPUNIT_LIBRARIES})
target_link_libraries(nxgroup_tests pniio ${CPPUNIT_LIBRARIES})
target_link_libraries(nxfield_tests pniio ${CPPUNIT_LIBRARIES})
target_link_libraries(nxattribute_tests pniio ${CPPUNIT_LIBRARIES})
target_link_libraries(nxlink_tests pniio ${CPPUNIT_LIBRARIES})

add_test("Nexus_Layer_1:low-level-test" nexus_lowlevel_test)
add_test("Nexus_Layer_1:nxfile" nxfile_tests)
add_test("Nexus_Layer_1:nxgroup" nxgroup_tests)
add_test("Nexus_Layer_1:nxfield" nxfield_tests)
add_test("Nexus_Layer_1:nxattribute" nxattribute_tests)
add_test("Nexus_Layer_1:nxlink" nxlink_tests)

add_custom_target(cleanup COMMAND rm -rf *.nxs *.h5)

set(COMMON_SRC nxfield_test_fixture.cpp
               nxattribute_test_fixture.cpp
               value_ref_test_tools.cpp)
add_library(level_1_common EXCLUDE_FROM_ALL OBJECT ${COMMON_SRC})
target_compile_definitions(level_1_common PUBLIC BOOST_ALL_DYN_LINK)

#------------------------------------------------------------------------------
# test nxfile related operations
#------------------------------------------------------------------------------
set(NXFILESRC nxfile_creation_test.cpp
              nxfile_open_single_file_test.cpp
              nxfile_open_family_file_test.cpp
              nxfile_misc_test.cpp
    )


set_boost_test_definitions(NXFILESRC "testing nxfile operations")
add_executable(nxfile_tests EXCLUDE_FROM_ALL ${NXFILESRC})
target_link_libraries(nxfile_tests pniio Boost::unit_test_framework)
add_boost_logging_test("Nexus_Layer_1:nxfile"
                       nxfile_tests
                       ${PROJECT_BINARY_DIR}/test/nexus_lowlevel_test)

add_custom_target(cleanup_artifacts
COMMAND ${CMAKE_COMMAND} -E remove *.nxs
WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/nexus_lowlevel_test)

set_tests_properties("Nexus_Layer_1:nxfile" PROPERTIES DEPENDS cleanup_artifacts)


#------------------------------------------------------------------------------
# test nxgroup related operations
#------------------------------------------------------------------------------
set(NXGROUPSRC  nxgroup_creation_test.cpp
                nxgroup_access_test.cpp
                nxgroup_misc_test.cpp
                nxgroup_recursive_test.cpp
              )

set_boost_test_definitions(NXGROUPSRC "testing nxgroup operations")
add_executable(nxgroup_tests EXCLUDE_FROM_ALL ${NXGROUPSRC}
               $<TARGET_OBJECTS:level_1_common>
               $<TARGET_OBJECTS:test_common>)
target_link_libraries(nxgroup_tests pniio Boost::unit_test_framework)
add_boost_logging_test("Nexus_Layer_1:nxgroup"
                        nxgroup_tests
                        ${PROJECT_BINARY_DIR}/test/nexus_lowlevel_test)


#------------------------------------------------------------------------------
# test nxfield related operations
#------------------------------------------------------------------------------
set(NXFIELDSRC  nxfield_creation_test.cpp
                nxfield_io_test.cpp
                nxfield_grow_test.cpp
                nxfield_partial_io_test.cpp
                nxfield_inquiry_test.cpp
    )

set_boost_test_definitions(NXFIELDSRC "testing nxfield operations")
add_executable(nxfield_tests EXCLUDE_FROM_ALL ${NXFIELDSRC}
               $<TARGET_OBJECTS:level_1_common>
               $<TARGET_OBJECTS:test_common>)
target_link_libraries(nxfield_tests pniio Boost::unit_test_framework)
add_boost_logging_test("Nexus_Layer_1:nxfield"
                       nxfield_tests
                       ${PROJECT_BINARY_DIR}/test/nexus_lowlevel_test)

#------------------------------------------------------------------------------
# test nxattribute related operations
#------------------------------------------------------------------------------
set(NXATTRSRC  nxattribute_creation_test.cpp
               nxattribute_access_test.cpp
               nxattribute_io_test.cpp
               nxattribute_view_io_test.cpp
               nxattribute_partial_io_test.cpp
               nxattribute_manage_test.cpp
   )

set_boost_test_definitions(NXATTRSRC "testing nxattribute operations")
add_executable(nxattribute_tests EXCLUDE_FROM_ALL ${NXATTRSRC}
                $<TARGET_OBJECTS:level_1_common>
                $<TARGET_OBJECTS:test_common>)
target_link_libraries(nxattribute_tests pniio Boost::unit_test_framework)
add_boost_logging_test("Nexus_Layer_1:nxattribute" nxattribute_tests
                       ${PROJECT_BINARY_DIR}/test/nexus_lowlevel_test)

#------------------------------------------------------------------------------
# test link related operations
#------------------------------------------------------------------------------
set(NXLINKSRC  nxlink_internal_test.cpp
               nxlink_external_test.cpp
               get_links_test.cpp
               get_links_recursive_test.cpp
               link_test.cpp
   )

set_boost_test_definitions(NXLINKSRC "testing nxattribute operations")
add_executable(nxlink_tests EXCLUDE_FROM_ALL ${NXLINKSRC}
               $<TARGET_OBJECTS:level_1_common>
               $<TARGET_OBJECTS:test_common>)
target_link_libraries(nxlink_tests pniio Boost::unit_test_framework)
add_boost_logging_test("Nexus_Layer_1:nxlink" nxlink_tests
                        ${PROJECT_BINARY_DIR}/test/nexus_lowlevel_test)

#-------------------------------------------------------------------------------
# we have to add the list of produced files to the cleanup target
#-------------------------------------------------------------------------------
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
  get_links_recursive_test.nxs
  nxfield_grow_test.nxs
  nxfile_create_test_test_with_split.00002.nxs
  nxgroup_access_test.nxs
  get_links_test.nxs
  nxfield_inquiry_test.nxs
  nxfile_create_test_test_with_split.00003.nxs
  nxgroup_creation_test.nxs
  link_test.nxs
  nxfield_io_test.nxs
  nxfile_creation_test_test_simple.nxs
  nxgroupmisctest.nxs
  nxattribute_access_test.nxs
  nxfield_partial_io_test.nxs
  nxfile_creation_test_test_with_overwrite.nxs  nxgroup_recursive_test.nxs
  nxattribute_creation_test.nxs
  nxfile_create_test_test_with_overwrite_with_split.00000.nxs
  nxfile_misc_test.nxs
  nxlink_external_test.link.nxs
  nxattribute_io_test.nxs
  nxfile_create_test_test_with_overwrite_with_split.00001.nxs
  nxfile_open_test.0000.nxs
  nxlink_external_test.target.nxs
  nxattribute_manage_test.nxs
  nxfile_create_test_test_with_overwrite_with_split.00002.nxs
  nxfile_open_test.0001.nxs
  nxlink_internal_test.nxs
  nxattribute_partial_io_test.nxs
  nxfile_create_test_test_with_overwrite_with_split.00003.nxs
  nxfile_open_test.0002.nxs
  nxattribute_view_io_test.nxs
  nxfile_create_test_test_with_split.00000.nxs
  nxfile_open_test.0003.nxs
  nxfield_creation_test.nxs
  nxfile_create_test_test_with_split.00001.nxs
  nxfile_open_test.nxs
)

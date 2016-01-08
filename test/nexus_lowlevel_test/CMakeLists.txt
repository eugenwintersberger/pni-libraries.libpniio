set(COMMON_SRC nxfield_test_fixture.cpp
               nxattribute_test_fixture.cpp
               value_ref_test_tools.cpp)
add_library(level_1_common OBJECT ${COMMON_SRC})

#------------------------------------------------------------------------------
# test nxfile related operations
#------------------------------------------------------------------------------
set(NXFILESRC nxfile_creation_test.cpp 
              nxfile_open_single_file_test.cpp
              nxfile_open_family_file_test.cpp
              nxfile_misc_test.cpp
    )


set_source_files_properties(nxfile_creation_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; \
                            BOOST_TEST_MODULE=testing nxfile operations")
add_executable(nxfile_tests EXCLUDE_FROM_ALL ${NXFILESRC})
target_link_libraries(nxfile_tests pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("Nexus_Layer_1:nxfile" nxfile_tests)
add_dependencies(check nxfile_tests)


#------------------------------------------------------------------------------
# test nxgroup related operations
#------------------------------------------------------------------------------
set(NXGROUPSRC  nxgroup_creation_test.cpp
                nxgroup_access_test.cpp
                nxgroup_misc_test.cpp
                nxgroup_recursive_test.cpp
              )

set_source_files_properties(nxgroup_creation_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; \
                            BOOST_TEST_MODULE=testing nxgroup operations")
add_executable(nxgroup_tests EXCLUDE_FROM_ALL ${NXGROUPSRC} 
               $<TARGET_OBJECTS:level_1_common>
               $<TARGET_OBJECTS:test_common>)
target_link_libraries(nxgroup_tests pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("Nexus_Layer_1:nxgroup" nxgroup_tests)
add_dependencies(check nxgroup_tests)

#------------------------------------------------------------------------------
# test nxfield related operations
#------------------------------------------------------------------------------
set(NXFIELDSRC  nxfield_creation_test.cpp
                nxfield_io_test.cpp
                nxfield_grow_test.cpp
                nxfield_partial_io_test.cpp
                nxfield_inquiry_test.cpp
    )

set_source_files_properties(nxfield_creation_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; \
                            BOOST_TEST_MODULE=testing nxfield operations")
add_executable(nxfield_tests EXCLUDE_FROM_ALL ${NXFIELDSRC} 
               $<TARGET_OBJECTS:level_1_common>
               $<TARGET_OBJECTS:test_common>)
target_link_libraries(nxfield_tests pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("Nexus_Layer_1:nxfield" nxfield_tests)
add_dependencies(check nxfield_tests)

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

set_source_files_properties(nxattribute_creation_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; \
                            BOOST_TEST_MODULE=testing nxattribute operations")
add_executable(nxattribute_tests EXCLUDE_FROM_ALL ${NXATTRSRC} 
                $<TARGET_OBJECTS:level_1_common>
                $<TARGET_OBJECTS:test_common>)
target_link_libraries(nxattribute_tests pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("Nexus_Layer_1:nxattribute" nxattribute_tests)
add_dependencies(check nxattribute_tests)

#------------------------------------------------------------------------------
# test nxattribute related operations
#------------------------------------------------------------------------------
set(NXLINKSRC  nxlink_internal_test.cpp
               nxlink_external_test.cpp
   )

set_source_files_properties(nxlink_internal_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; \
                            BOOST_TEST_MODULE=testing nxattribute operations")
add_executable(nxlink_tests EXCLUDE_FROM_ALL ${NXLINKSRC}
               $<TARGET_OBJECTS:level_1_common>
               $<TARGET_OBJECTS:test_common>)
target_link_libraries(nxlink_tests pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test("Nexus_Layer_1:nxlink" nxlink_tests)
add_dependencies(check nxlink_tests)

add_custom_target(cleanup COMMAND rm -rf *.nxs *.h5)

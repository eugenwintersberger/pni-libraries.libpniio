
#need to define the version of the library
set(COMMON_SRC EqualityCheck.cpp data.cpp TestHelpers.cpp)
add_library(test_common OBJECT ${COMMON_SRC})

link_directories(${PNICORE_PKG_LIBRARY_DIRS} ${HDF5_LIBRARY_DIRS})
include_directories(${PNICORE_PKG_INCLUDE_DIRS} ${HDF5_INCLUDE_DIRS})
link_directories("${CMAKE_CURRENT_BINARY_DIR}/../src")
include_directories(${PNICORE_PKG_INCLUDE_DIRS})

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

endif()

add_subdirectory(xml_test)
add_subdirectory(hdf5_imp_test)
add_subdirectory(nexus_lowlevel_test)
add_subdirectory(parser_test)
add_subdirectory(algorithm_test)
add_subdirectory(reader_test)
add_subdirectory(nxpath_test)
add_subdirectory(formatter_test)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
add_dependencies(check node_test dimensions_test io_node_test
                       data_node_test attribute_tests field_test
                       group_test link_test xml_to_nexus_test
                       nexus_to_xml_test
                       hdf5_imp_test 
                       nexus_lowlevel_test
                       nxfile_tests
                       nxgroup_tests
                       nxfield_tests
                       nxattribute_tests
                       nxlink_tests
                       primitive_parsers_test
                       object_parsers_test
                       inquiry_conversion_test
                       common_test
                       algo_group_test
                       algo_field_test
                       algo_attribute_test
                       algo_io_tests
                       reader_test
                       nxpath_tests
                       nxpath_parser_tests
                       nxpath_utils_test
                       primitive_formatter_test
                       compound_formatter_test
                       )


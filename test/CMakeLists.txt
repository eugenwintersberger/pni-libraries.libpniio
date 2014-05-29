
#need to define the version of the library
set(TEST_SOURCES 
    ./nxvariant_tests/is_valid_test.cpp
    ./nxvariant_tests/get_attribute_test.cpp
    ./nxvariant_tests/get_class_test.cpp
    ./nxvariant_tests/get_size_test.cpp
    ./nxvariant_tests/get_type_test.cpp
    ./nxvariant_tests/read_test.cpp
    ./nxvariant_tests/get_unit_test.cpp
    ./nxvariant_tests/grow_test.cpp
    ./nxvariant_tests/get_object_test.cpp
    ./nxvariant_tests/is_class_test.cpp
    ./nxvariant_tests/is_group_test.cpp
    ./nxvariant_tests/get_shape_test.cpp
    ./nxvariant_tests/as_field_test.cpp
    ./nxvariant_tests/write_test.cpp
    ./nxvariant_tests/create_group_test.cpp
    ./nxvariant_tests/as_group_test.cpp
    ./nxvariant_tests/set_class_test.cpp
    ./nxvariant_tests/get_rank_test.cpp
    ./nxvariant_tests/is_field_test.cpp
    ./nxvariant_tests/set_unit_test.cpp
    ./nxvariant_tests/as_attribute_test.cpp
    ./nxvariant_tests/create_field_test.cpp
    ./nxvariant_tests/create_attribute_test.cpp
    ./nxvariant_tests/get_child_test.cpp
    ./nxvariant_tests/is_attribute_test.cpp
    ./nxvariant_tests/get_parent_test.cpp
    ./data.cpp
    ./TestHelpers.cpp
    ./parser_tests/value_parser_test.cpp
    ./parser_tests/slice_parser_test.cpp
    ./parser_tests/array_parser_test.cpp
    ./parser_tests/record_parser_test.cpp
    ./pniiotest.cpp
    ./EqualityCheck.cpp
)

set(COMMON_SRC EqualityCheck.cpp data.cpp TestHelpers.cpp)
add_library(test_common OBJECT ${COMMON_SRC})

link_directories(${PNICORE_PKG_LIBRARY_DIRS} ${HDF5_LIBRARY_DIRS})
include_directories(${PNICORE_PKG_INCLUDE_DIRS} ${HDF5_INCLUDE_DIRS})
link_directories("${CMAKE_CURRENT_BINARY_DIR}/../src")
include_directories(${PNICORE_PKG_INCLUDE_DIRS})
add_executable(pniiotest ${TEST_SOURCES})

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

    #add libraries
    target_link_libraries(pniiotest ${CPPUNIT_LIBRARIES})

endif()

target_link_libraries(pniiotest pniio dl)

add_subdirectory(xml_test)
add_subdirectory(utils_test)
add_subdirectory(hdf5_imp_test)
add_subdirectory(nexus_lowlevel_test)


add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/reader_tests/iui8.tiff ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/reader_tests/ii8.tiff ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/reader_tests/ii32.tiff ${CMAKE_CURRENT_BINARY_DIR})



#need to define the version of the library
file(GLOB_RECURSE TEST_SOURCES *.cpp)

link_directories(${PNICORE_PKG_LIBRARY_DIRS} ${HDF5_LIBRARY_DIRS})
include_directories(${PNICORE_PKG_INCLUDE_DIRS} ${HDF5_INCLUDE_DIRS})
link_directories("${CMAKE_CURRENT_BINARY_DIR}/../src")
include_directories(${PNICORE_PKG_INCLUDE_DIRS})
add_executable(pniiotest ${TEST_SOURCES})
target_link_libraries(pniiotest pniio ${CPPUNIT_PKG_LIBRARIES})

add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/xml_test/dim1.xml $<TARGET_FILE_DIR:pniiotest>)
add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/xml_test/dim2.xml $<TARGET_FILE_DIR:pniiotest>)
add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/xml_test/dim3.xml $<TARGET_FILE_DIR:pniiotest>)
add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/xml_test/dim4.xml $<TARGET_FILE_DIR:pniiotest>)
add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/xml_test/dim5.xml $<TARGET_FILE_DIR:pniiotest>)

add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/xml_test/field1.xml $<TARGET_FILE_DIR:pniiotest>)
add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/xml_test/field2.xml $<TARGET_FILE_DIR:pniiotest>)
add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/xml_test/field3.xml $<TARGET_FILE_DIR:pniiotest>)
add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/xml_test/field4.xml $<TARGET_FILE_DIR:pniiotest>)
add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/xml_test/field5.xml $<TARGET_FILE_DIR:pniiotest>)

add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/xml_test/node_from_bad_file.xml $<TARGET_FILE_DIR:pniiotest>)
add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/xml_test/node_from_str.xml $<TARGET_FILE_DIR:pniiotest>)
add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/xml_test/object_tree1.xml $<TARGET_FILE_DIR:pniiotest>)


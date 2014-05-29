set(SOURCES tiff_reader_test.cpp
            reader_test.cpp
           )

add_executable(reader_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(reader_test pniio ${CPPUNIT_LIBRARIES})

add_custom_command(TARGET reader_test PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/iui8.tiff ${CMAKE_CURRENT_BINARY_DIR}/iui8.tiff)
add_custom_command(TARGET reader_test PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/ii8.tiff ${CMAKE_CURRENT_BINARY_DIR}/ii8.tiff)
add_custom_command(TARGET reader_test PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/ii32.tiff ${CMAKE_CURRENT_BINARY_DIR}/ii32.tiff)

add_test(reader_test reader_test)

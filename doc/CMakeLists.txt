#build documentation
include(FindDoxygen)

#generate the mainpage input file
configure_file(mainpage.cmake mainpage @ONLY)
configure_file(Doxyfile.cmake Doxyfile @ONLY)

#run doxygen
add_custom_command(OUTPUT html COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile)
add_custom_target(documentation ALL SOURCES "html")
install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html" 
    DESTINATION "${CMAKE_INSTALL_DOCDIR}/libpniio-doc")

#need to copy some files in order to get documentation right

add_custom_command(TARGET documentation PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/ascii_io ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET documentation PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/general_io ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET documentation PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/h5_implementation_classes ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET documentation PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/image_io ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET documentation PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/images)
add_custom_command(TARGET documentation PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/implementation_interface ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET documentation PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/installation ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET documentation PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/nexus_io ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET documentation PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/nexus_utilities ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET documentation PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/nxpath_code ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET documentation PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/usage ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET documentation PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/variant_code ${CMAKE_CURRENT_BINARY_DIR})


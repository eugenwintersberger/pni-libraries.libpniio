#build documentation
include(FindDoxygen)

#generate the mainpage input file
if("${CMAKE_FAMILY_VERSION}" EQUAL "2.6")
    configure_file(mainpage.cmake ./doc/mainpage @ONLY)
else()
    configure_file(mainpage.cmake mainpage @ONLY)
endif()

if("${CMAKE_FAMILY_VERSION}" EQUAL "2.6")
    configure_file(Doxyfile.cmake ./doc/Doxyfile @ONLY)
else()
    configure_file(Doxyfile.cmake Doxyfile @ONLY)
endif()

#run doxygen
add_custom_command(OUTPUT html COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile)
add_custom_target(documentation ALL SOURCES "html")
install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html" 
    DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}")


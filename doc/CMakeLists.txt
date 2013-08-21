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


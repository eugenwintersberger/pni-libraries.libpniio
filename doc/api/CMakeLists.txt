#generate additional doxygen files
configure_file(mainpage.cmake mainpage.dox @ONLY)
configure_file(Doxyfile.cmake Doxyfile @ONLY)
set_source_files_properties(Doxyfile mainpage.dox
                      PROPERTIES GENERATED TRUE)

#run doxygen
add_custom_command(OUTPUT doxygen.stamp
                   COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile > doxygen.log
                   COMMAND echo "timestamp" > doxygen.stamp
                   DEPENDS Doxyfile mainpage.dox ${CMAKE_DOXYGEN_BUILD_DEPENDENCIES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_custom_target(api_doc DEPENDS doxygen.stamp )


install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html"
    DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}${LIBRARY_VERSION}-doc"
    OPTIONAL
    COMPONENT doc_html
    )

set(RST_FILES index.rst
              exceptions.rst
              nexus.rst
              nexus_file.rst
              nexus_xml.rst
              nexus_algorithm.rst
              nexus_path.rst
              nexus_utils.rst
              nexus_factories.rst
              ascii.rst
              ascii_parsers.rst
              ascii_spreadsheet.rst)

foreach(RST_FILE ${RST_FILES})
    configure_file(${RST_FILE} ${RST_FILE} COPYONLY)
endforeach()

add_sphinx_source(${RST_FILES})
#generate additional doxygen files
configure_file(mainpage.cmake mainpage.dox @ONLY)
configure_file(Doxyfile.cmake Doxyfile @ONLY)
set_source_files_properties(Doxyfile mainpage.dox
                      PROPERTIES GENERATED TRUE)

#run doxygen
add_custom_command(OUTPUT doxygen.stamp
                   COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
                   COMMAND echo "timestamp" > doxygen.stamp
                   SOURCE ${CMAKE_DOXYGEN_BUILD_DEPENDENCIES}
                   DEPENDS Doxyfile mainpage.dox)
add_custom_target(api_doc SOURCES doxygen.stamp )


install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html"
    DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}${LIBRARY_VERSION}-doc"
    OPTIONAL
    COMPONENT doc_html
    )

set(RST_FILES index.rst
              exceptions.rst)

foreach(RST_FILE ${RST_FILES})
    configure_file(${RST_FILE} ${RST_FILE} COPYONLY)
endforeach()

add_sphinx_source(${RST_FILES})
#build documentation
include(FindDoxygen)

set(HEADER_DIR ../include/pni/io)

if(DOXYGEN_FOUND)
    #generate additional doxygen files
    configure_file(mainpage.cmake mainpage @ONLY)
    configure_file(algorithm_code.cmake algorithm_code  @ONLY)
    configure_file(ascii_io.cmake ascii_io @ONLY)
    configure_file(general_io.cmake general_io @ONLY)
    configure_file(h5_implementation_classes.cmake
                   h5_implementation_classes @ONLY)
    configure_file(nexus_io.cmake nexus_io @ONLY)
    configure_file(image_io.cmake image_io @ONLY)
    configure_file(xml_code.cmake xml_code @ONLY)
    configure_file(nxpath_code.cmake nxpath_code @ONLY)
    configure_file(nexus_utilities.cmake nexus_utilities @ONLY)

    configure_file(Doxyfile.cmake Doxyfile @ONLY)

    #run doxygen
    add_custom_command(OUTPUT html COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile)
    add_custom_target(api_doc SOURCES "html")
    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html"
        DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}"
        OPTIONAL
        COMPONENT doc_html
        )
endif()

add_subdirectory(ug)
add_subdirectory(examples)

add_custom_target(html DEPENDS api_doc)
add_custom_target(pdf DEPENDS ug_doc)

add_custom_target(install-html
    DEPENDS html
    COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=doc_html
    -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake)

add_custom_target(install-pdf
    DEPENDS pdf
    COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=doc_pdf
    -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake)

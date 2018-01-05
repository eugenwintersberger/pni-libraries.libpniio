

configure_file(conf.py.in conf.py @ONLY)
configure_file(index.rst index.rst COPYONLY)

if(DOXYGEN_FOUND)
    #generate additional doxygen files
    configure_file(mainpage.cmake mainpage.dox @ONLY)
    configure_file(algorithm_code.cmake algorithm_code.dox  @ONLY)
    configure_file(ascii_io.cmake ascii_io.dox @ONLY)
    configure_file(general_io.cmake general_io.dox @ONLY)
    configure_file(h5_implementation_classes.cmake
                   h5_implementation_classes.dox @ONLY)
    configure_file(nexus_io.cmake nexus_io.dox @ONLY)
    configure_file(image_io.cmake image_io.dox @ONLY)
    configure_file(xml_code.cmake xml_code.dox @ONLY)
    configure_file(nxpath_code.cmake nxpath_code.dox @ONLY)
    configure_file(nexus_utilities.cmake nexus_utilities.dox @ONLY)

    configure_file(Doxyfile.cmake Doxyfile @ONLY)

    #run doxygen
    add_custom_command(OUTPUT html COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile)
    add_custom_target(api_doc SOURCES "html" )
    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html"
        DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}${LIBRARY_VERSION}-doc"
        OPTIONAL
        COMPONENT doc_html
        )
endif()

add_subdirectory(_static)
add_subdirectory(_templates)
add_subdirectory(users_guide)
add_subdirectory(examples)

add_custom_target(sphinx_build
                  COMMAND sphinx-build -bhtml . build/html
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}                  
                  SOURCES ${CMAKE_SPHINX_SOURCES} conf.py index.rst)
add_dependencies(html sphinx_build)


#
# install the documentation
#
add_custom_target(install-html
    DEPENDS html
    COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=doc_html
    -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake)


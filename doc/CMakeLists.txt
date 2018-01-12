

configure_file(conf.py.in conf.py @ONLY)
configure_file(index.rst index.rst COPYONLY)



add_subdirectory(_static)
add_subdirectory(_templates)
add_subdirectory(users_guide)
add_subdirectory(api)
add_subdirectory(examples)
add_subdirectory(images)

add_custom_target(sphinx_build
                  COMMAND sphinx-build -bhtml . build/html
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} 
                  DEPENDS api_doc                 
                  SOURCES ${CMAKE_SPHINX_SOURCES} conf.py index.rst)
add_dependencies(html sphinx_build)


#
# install the documentation
#
add_custom_target(install-html
    DEPENDS html
    COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=doc_html
    -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake)


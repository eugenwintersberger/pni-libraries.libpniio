#build users guide with sphinx

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(HTML_DIR "${CMAKE_CURRENT_BINARY_DIR}/build/html")
set(EPUB_DIR "${CMAKE_CURRENT_BINARY_DIR}/build/epub")
set(PDF_DIR  "${CMAKE_CURRENT_BINARY_DIR}/build/latex")


#we can do this since sphinx looks by itself for new files.
add_custom_target(ug_html COMMAND sphinx-build -b html ${SRC_DIR} ${HTML_DIR})
add_custom_target(ug_epub COMMAND sphinx-build -b epub ${SRC_DIR} ${EPUB_DIR})
add_custom_target(ug_pdf  COMMAND sphinx-build -b latex ${SRC_DIR} ${EPUB_DIR})


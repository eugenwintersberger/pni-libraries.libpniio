set(STATIC_FILES layers.svg)

foreach(STATIC_FILE ${STATIC_FILES})
    configure_file(${STATIC_FILE} ${STATIC_FILE} COPYONLY)
endforeach()

add_sphinx_source(${STATIC_FILES})
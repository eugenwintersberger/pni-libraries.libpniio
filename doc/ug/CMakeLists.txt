#build documentation

#get all the sources for the documentation
set(PDFLATEX_COMPILER pdflatex)
set(BIBTEX_COMMAND bibtex)
set(MASTER libpniio_ug.tex)
set(SOURCES tex/installation.tex
            tex/introduction.tex
            tex/nexus_introduction.tex
            tex/nexus_path.tex
            tex/usage.tex
            tex/basic_usage.tex
            )

foreach(TEX_FILE ${SOURCES}) 
    configure_file(${TEX_FILE} ${TEX_FILE} COPYONLY)
endforeach()

configure_file(${MASTER} ${MASTER} COPYONLY)
add_custom_command(OUTPUT libpniio_ug.pdf 
                   COMMAND ${PDFLATEX_COMPILER} -shell-escape libpniio_ug.tex
                   #COMMAND ${BIBTEX_COMMAND} libpniio_ug
                   COMMAND ${PDFLATEX_COMPILER} -shell-escape libpniio_ug.tex
                   COMMAND ${PDFLATEX_COMPILER} -shell-escape libpniio_ug.tex
                   DEPENDS ${MASTER} ${SOURCES}
                   )

add_custom_target(ug_doc  DEPENDS "libpniio_ug.pdf" )

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/libpniio_ug.pdf" 
        DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}")


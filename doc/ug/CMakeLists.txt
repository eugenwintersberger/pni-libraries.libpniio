#build documentation

#get all the sources for the documentation
set(PDFLATEX_COMPILER pdflatex)
set(BIBTEX_COMMAND bibtex)
set(SOURCES libpniio_ug.tex
            tex/introduction.tex
            tex/installation.tex
    )


add_custom_command(OUTPUT libpniio_ug.pdf 
                   COMMAND ${PDFLATEX_COMPILER} -shell-escape libpniio_ug.tex
                   #COMMAND ${BIBTEX_COMMAND} libpniio_ug
                   COMMAND ${PDFLATEX_COMPILER} -shell-escape libpniio_ug.tex
                   COMMAND ${PDFLATEX_COMPILER} -shell-escape libpniio_ug.tex
                   DEPENDS ${SOURCES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   )

add_custom_target(doc  DEPENDS "libpniio_ug.pdf" )

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/libpniio_ug.pdf" 
        DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}")


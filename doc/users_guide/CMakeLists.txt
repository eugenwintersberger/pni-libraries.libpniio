set(RST_SOURCES index.rst
                introduction.rst
                installation.rst
                usage.rst
                legacy.rst
                
                nexus.rst
                nexus_introduction.rst
                nexus_path.rst
                nexus_files.rst
                nexus_groups.rst
                nexus_retrieval.rst
                nexus_search.rst
                nexus_xml.rst
                ascii_lowlevel.rst
                ascii.rst
                ascii_spreadsheet.rst
                image.rst)

foreach(RST_SOURCE ${RST_SOURCES})
    configure_file(${RST_SOURCE} ${RST_SOURCE} COPYONLY)
endforeach()

add_sphinx_source(${RST_SOURCES})

    
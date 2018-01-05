set(RST_SOURCES index.rst
                introduction.rst
                installation.rst
                usage.rst
                legacy.rst
                nexus_introduction.rst
                nexus_path.rst
                basic_usage.rst
                nexus_files.rst
                nexus_groups.rst)

foreach(RST_SOURCE ${RST_SOURCES})
    configure_file(${RST_SOURCE} ${RST_SOURCE} COPYONLY)
endforeach()

add_sphinx_source(${RST_SOURCES})

    
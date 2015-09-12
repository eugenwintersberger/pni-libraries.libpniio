set(SOURCES nxpath.cpp
            utils.cpp
            parser.cpp
            make_relative.cpp
            )

add_library(nx_path OBJECT ${SOURCES})


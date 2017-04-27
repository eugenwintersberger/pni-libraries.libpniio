set(SOURCES nxpath.cpp
            utils.cpp
            parser.cpp
            make_relative.cpp
            )

add_library(nx_path OBJECT ${SOURCES})
set_property(TARGET nx_path PROPERTY POSITION_INDEPENDENT_CODE ON)


set(SOURCES utils.cpp parser.cpp slice_parser.cpp)

add_library(parser_objects OBJECT ${SOURCES})
set_property(TARGET parser_objects PROPERTY POSITION_INDEPENDENT_CODE ON)

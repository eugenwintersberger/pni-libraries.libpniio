set(SOURCES cbf_reader.cpp dectris_reader.cpp)

add_library(cbf_objects OBJECT ${SOURCES})
set_property(TARGET cbf_objects PROPERTY POSITION_INDEPENDENT_CODE ON)

set(SOURCES scalar_format.cpp vector_format.cpp)

add_library(formatter_objects OBJECT ${SOURCES})
set_property(TARGET formatter_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
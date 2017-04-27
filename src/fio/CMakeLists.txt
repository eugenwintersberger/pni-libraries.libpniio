set(SOURCES fio_reader.cpp)

add_library(fio_objects OBJECT ${SOURCES})
set_property(TARGET fio_objects PROPERTY POSITION_INDEPENDENT_CODE ON)

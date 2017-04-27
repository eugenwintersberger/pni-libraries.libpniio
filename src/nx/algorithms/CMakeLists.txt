set(SOURCES utils.cpp)

add_library(algorithms OBJECT ${SOURCES})
set_property(TARGET algorithms PROPERTY POSITION_INDEPENDENT_CODE ON)


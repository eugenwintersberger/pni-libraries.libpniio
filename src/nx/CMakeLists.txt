set(SOURCES nxdate_time.cpp
            nxlink.cpp
            nxlink_type.cpp
            )

add_subdirectory(h5)
add_subdirectory(xml)
add_subdirectory(nxpath)
add_subdirectory(algorithms)

add_library(nx_objects OBJECT ${SOURCES})
set_property(TARGET nx_objects PROPERTY POSITION_INDEPENDENT_CODE ON)


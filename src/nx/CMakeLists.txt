set(SOURCES nxdate_time.cpp
            nxexceptions.cpp
            nxpath.cpp
            nxpath_utils.cpp
            )

add_subdirectory(h5)
add_subdirectory(xml)

add_library(nx_objects OBJECT ${SOURCES})


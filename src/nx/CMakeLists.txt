set(SOURCES nxdate_time.cpp
            )

add_subdirectory(h5)
add_subdirectory(xml)
add_subdirectory(nxpath)
add_subdirectory(algorithms)

add_library(nx_objects OBJECT ${SOURCES})


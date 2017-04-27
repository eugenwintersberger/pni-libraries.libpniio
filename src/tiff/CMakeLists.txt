set(SOURCES exceptions.cpp
            ifd.cpp
            ifd_entry.cpp
            ifd_entry_reader.cpp
            strip_reader.cpp
            tiff_reader.cpp)

add_library(tiff_objects OBJECT ${SOURCES})
set_property(TARGET tiff_objects PROPERTY POSITION_INDEPENDENT_CODE ON)

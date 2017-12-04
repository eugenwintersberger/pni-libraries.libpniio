set(HEADER_FILES exceptions.hpp 
                 ifd_entry.hpp 
                 ifd_entry_reader.hpp 
                 ifd.hpp
                 rational.hpp 
                 standard.hpp 
                 strip_reader.hpp 
                 tiff_reader.hpp)

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/io/tiff)

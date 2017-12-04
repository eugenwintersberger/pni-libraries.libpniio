set(HEADER_FILES exceptions.hpp 
                 ifd_entry.hpp 
                 ifd_entry_reader.hpp 
                 ifd.hpp
                 rational.hpp 
                 standard.hpp 
                 strip_reader.hpp 
                 tiff_reader.hpp)
                
set(SOURCE_FILES exceptions.cpp
                 ifd.cpp
                 ifd_entry.cpp
                 ifd_entry_reader.cpp
                 strip_reader.cpp
                 tiff_reader.cpp)

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/io/tiff)
       
set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)

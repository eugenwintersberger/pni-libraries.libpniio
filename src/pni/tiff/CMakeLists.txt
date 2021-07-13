set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/exceptions.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/ifd_entry.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/ifd_entry_reader.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/ifd.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/rational.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/standard.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/strip_reader.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/tiff_reader.hpp)
                
set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/exceptions.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/ifd.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/ifd_entry.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/ifd_entry_reader.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/strip_reader.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/tiff_reader.cpp)

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/tiff)
       
set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)

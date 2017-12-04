set(HEADER_FILES  nxpath.hpp 
                  parser.hpp 
                  utils.hpp 
                  make_relative.hpp)
                 
set(SOURCE_FILES nxpath.cpp
                 utils.cpp
                 parser.cpp
                 make_relative.cpp)
                
install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/io/nx/nxpath)

set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)
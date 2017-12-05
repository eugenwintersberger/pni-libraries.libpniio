set(HEADER_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/nxpath.hpp 
                  ${CMAKE_CURRENT_SOURCE_DIR}/parser.hpp 
                  ${CMAKE_CURRENT_SOURCE_DIR}/utils.hpp 
                  ${CMAKE_CURRENT_SOURCE_DIR}/make_relative.hpp)
                 
set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/nxpath.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/make_relative.cpp)
                
install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/io/nx/nxpath)

set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)
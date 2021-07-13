set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/container_iterator.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/container_utils.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/service.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/sfinae_macros.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/utilities)

set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)

set(HEADER_FILES c_index_map_imp.hpp
                 index_map.hpp
                 index_maps.hpp
                 static_index_map.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/types)
set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)

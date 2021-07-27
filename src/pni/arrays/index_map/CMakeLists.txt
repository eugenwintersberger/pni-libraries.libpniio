set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/c_index_map_imp.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/index_map.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/index_maps.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/static_index_map.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/arrays/index_map)
set(PNINEXUS_HEADER_FILES ${PNINEXUS_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)

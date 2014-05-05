set(HEADER_FILES check_rank.hpp 
                 check_type.hpp 
                 io_utils.hpp 
                 nxfield_utils.hpp 
                 search_utils.hpp 
                 types.hpp)

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io/nx/utils)

set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/nxattribute.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/nxdate_time.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/nxdeflate_filter.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/nxfield.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/nxfile.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/nxfilter.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/nxgroup.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/nx_hdf5_implementation.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/nx.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/nximp_code.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/nximp_code_map.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/nximp_map.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/nxlink.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/nxobject.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/nxlink_type.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/nxobject_traits.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/nxobject_type.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/nxpath.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/algorithms.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/xml.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/nxattribute_manager.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/flat_group.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/link.hpp)
                
set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/nxdate_time.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/nxlink.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/nxlink_type.cpp)

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/io/nx)


add_subdirectory("h5")
add_subdirectory("xml")
add_subdirectory("algorithms")
add_subdirectory("nxpath")

set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)
set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)

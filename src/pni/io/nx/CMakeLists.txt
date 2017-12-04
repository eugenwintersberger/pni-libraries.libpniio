set(HEADER_FILES nxattribute.hpp 
                 nxdate_time.hpp 
                 nxdeflate_filter.hpp 
                 nxfield.hpp 
                 nxfile.hpp 
                 nxfilter.hpp 
                 nxgroup.hpp 
                 nx_hdf5_implementation.hpp 
                 nx.hpp 
                 nximp_code.hpp 
                 nximp_code_map.hpp 
                 nximp_map.hpp 
                 nxlink.hpp 
                 nxobject.hpp
                 nxlink_type.hpp 
                 nxobject_traits.hpp
                 nxobject_type.hpp
                 nxpath.hpp
                 algorithms.hpp
                 xml.hpp
                 nxattribute_manager.hpp
                 flat_group.hpp
                 link.hpp)
                
set(SOURCE_FILES nxdate_time.cpp
                 nxlink.cpp
                 nxlink_type.cpp)

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/io/nx)


add_subdirectory("h5")
add_subdirectory("xml")
add_subdirectory("algorithms")
add_subdirectory("nxpath")

set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)
set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)

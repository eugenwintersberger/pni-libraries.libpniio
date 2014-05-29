set(HEADER_FILES nexus_utils.hpp
                 nxattribute.hpp 
                 nxattribute_iterator.hpp 
                 nxconfiguration.hpp 
                 nxdate_time.hpp 
                 nxdeflate_filter.hpp 
                 nxexceptions.hpp 
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
                 nxlink_type.hpp 
                 nxobject_iterator.hpp
                 nxobject_traits.hpp
                 nxobject_type.hpp
                 nxpath.hpp
                 nxpath_utils.hpp
                 nxselection.hpp
                 algorithms.hpp
                 xml.hpp)

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io/nx)


add_subdirectory("h5")
add_subdirectory("xml")
add_subdirectory("utils")
add_subdirectory("algorithms")

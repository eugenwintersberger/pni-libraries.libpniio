set(HEADER_FILES H5Attribute.hpp 
                 H5AttributeObject.hpp 
                 H5Dataset.hpp 
                 H5Dataspace.hpp 
                 H5DatatypeFactory.hpp 
                 H5Datatype.hpp 
                 H5DeflateFilter.hpp 
                 h5_error.hpp 
                 h5_error_stack.hpp 
                 H5File.hpp 
                 H5Filter.hpp 
                 H5Group.hpp 
                 H5LibrarySetup.hpp 
                 h5link.hpp 
                 H5NamedObject.hpp 
                 H5Object.hpp 
                 H5ObjectType.hpp 
                 hdf5_utilities.hpp
                 h5object.hpp
                 h5datatype.hpp
                 h5dataspace.hpp
                 )


install(FILES ${HEADER_FILES} DESTINATION
        ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io/nx/h5)

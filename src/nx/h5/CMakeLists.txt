set(SOURCES H5Attribute.cpp
            H5AttributeObject.cpp
            H5Dataset.cpp
            H5Dataspace.cpp
            H5Datatype.cpp
            H5DatatypeFactory.cpp
            H5DeflateFilter.cpp
            h5_error.cpp
            h5_error_stack.cpp
            H5File.cpp
            H5Group.cpp
            H5LibrarySetup.cpp
            h5link.cpp
            H5NamedObject.cpp
            H5Object.cpp
            hdf5_utilities.cpp
            )


add_library(h5_objects OBJECT ${SOURCES})


set(SOURCES H5Attribute.cpp
            H5AttributeObject.cpp
            H5Dataset.cpp
            H5Dataspace.cpp
            H5Datatype.cpp
            H5DatatypeFactory.cpp
            H5DeflateFilter.cpp
            H5Group.cpp
            H5LibrarySetup.cpp
            h5link.cpp
            H5NamedObject.cpp
            H5Object.cpp

            h5_error.cpp
            h5_error_stack.cpp
            hdf5_utilities.cpp
            object_imp.cpp
            h5object_types.cpp
            h5datatype.cpp
            h5dataspace.cpp
            attribute_utils.cpp
            attribute_imp.cpp
            group_imp.cpp
            file_imp.cpp
            field_imp.cpp
            field_factory.cpp
            h5filter.cpp
            h5deflate_filter.cpp
            )


add_library(h5_objects OBJECT ${SOURCES})


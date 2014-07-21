set(SOURCES
            attribute_imp.cpp
            attribute_utils.cpp
            field_factory.cpp
            field_imp.cpp
            file_imp.cpp
            group_imp.cpp
            h5dataspace.cpp
            h5datatype.cpp
            h5deflate_filter.cpp
            h5_error.cpp
            h5_error_stack.cpp
            h5filter.cpp
            h5link.cpp
            h5object_types.cpp
            hdf5_utilities.cpp
            object_imp.cpp
            string_utils.cpp
            )


add_library(h5_objects OBJECT ${SOURCES})


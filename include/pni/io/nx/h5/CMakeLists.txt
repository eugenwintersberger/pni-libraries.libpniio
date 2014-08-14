set(HEADER_FILES 
                attribute_imp.hpp
                attribute_utils.hpp
                field_factory.hpp
                field_imp.hpp
                file_imp.hpp
                group_imp.hpp
                h5dataspace.hpp
                h5datatype.hpp
                h5deflate_filter.hpp
                h5_error.hpp
                h5_error_stack.hpp
                h5filter.hpp
                h5link.hpp
                h5object_types.hpp
                hdf5_utilities.hpp
                object_imp.hpp
                type_imp.hpp
                selection.hpp
                 )



install(FILES ${HEADER_FILES} DESTINATION
        ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io/nx/h5)

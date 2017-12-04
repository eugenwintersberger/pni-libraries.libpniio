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
                selection_guard.hpp
                 )

set(SOURCE_FILES attribute_imp.cpp
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
                 selection.cpp
                 nullterm_formatter.cpp
                 charpad_formatter.cpp
                 string_formatter.cpp
                 string_formatter_factory.cpp
            )

install(FILES ${HEADER_FILES} DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/pni/io/nx/h5)
       
set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)

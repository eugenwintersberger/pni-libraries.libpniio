set(HEADER_FILES 
                ${CMAKE_CURRENT_SOURCE_DIR}/attribute_imp.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/attribute_utils.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/field_factory.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/field_imp.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/file_imp.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/group_imp.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/h5dataspace.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/h5datatype.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/h5deflate_filter.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/h5_error.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/h5_error_stack.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/h5filter.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/h5link.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/h5object_types.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/hdf5_utilities.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/object_imp.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/type_imp.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/selection.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/selection_guard.hpp
                 )

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/attribute_imp.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/attribute_utils.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/field_factory.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/field_imp.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/file_imp.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/group_imp.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/h5dataspace.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/h5datatype.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/h5deflate_filter.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/h5_error.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/h5_error_stack.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/h5filter.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/h5link.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/h5object_types.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/hdf5_utilities.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/object_imp.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/string_utils.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/selection.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/nullterm_formatter.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/charpad_formatter.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/string_formatter.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/string_formatter_factory.cpp
            )

install(FILES ${HEADER_FILES} DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/pni/io/nx/h5)
       
set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)

#
# manage header files
#

set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/array_arithmetic.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array_operations.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array_selection.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array_factory.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array_view.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array_view_utils.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/index_iterator.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/mdarray.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/scalar.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/scalar_iterator.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/slice.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/index_utilities.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/types)

add_subdirectory("index_map")

#
# build submodule
#
set(FILE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/array_selection.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/slice.cpp)

set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)


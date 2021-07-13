#
# manage header files
#
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/array_holder.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array_holder_interface.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array_iterator.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/value_holder.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/value_holder_interface.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/value.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/value_ref.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/make_array.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/utils.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/type_erasures)

#
# build submodule
# 
set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/array.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/value.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/value_ref.cpp )

set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)

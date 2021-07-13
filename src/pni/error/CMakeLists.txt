#
# manage header files
#
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/exceptions.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/exception_utils.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/types)

#
# build submodule
#
set(SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/exceptions.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/exception_utils.cpp
  )

set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)

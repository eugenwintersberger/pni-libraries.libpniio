#
# manage header files
#
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/binary.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/complex_utils.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/id_type_map.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/type_class_map.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/type_conversion.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/type_id_map.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/type_info.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/types.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/type_utils.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/container_trait.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/bool.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/none.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/unchecked_convertible.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/checked_convertible.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/convertible.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/convert.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/traits.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/types)

#
# build submodule
#
set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/bool.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/complex_utils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/is_unchecked_convertible.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/is_checked_convertible.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/is_convertible.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/none.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/type_conversion.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/type_utils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/traits.cpp
  )

set(PNINEXUS_HEADER_FILES ${PNINEXUS_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNINEXUS_SOURCE_FILES ${PNINEXUS_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)

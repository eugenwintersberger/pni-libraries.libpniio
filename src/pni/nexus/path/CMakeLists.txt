set(HEADER_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/path.hpp 
                  ${CMAKE_CURRENT_SOURCE_DIR}/parser.hpp 
                  ${CMAKE_CURRENT_SOURCE_DIR}/utils.hpp 
                  ${CMAKE_CURRENT_SOURCE_DIR}/make_relative.hpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/path_object.hpp
                 )
                 
set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/path.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/make_relative.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/path_object.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_path.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/get_objects.cpp
                )
                
install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/nexus/path)

set(PNINEXUS_HEADER_FILES ${PNINEXUS_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNINEXUS_SOURCE_FILES ${PNINEXUS_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)
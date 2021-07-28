set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/conversion_trait.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/vector_parser.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/parser.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/string_parser.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/value_parser.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/slice_parser.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/bool_parser.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/complex_parser.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/vector_parser.hpp
                 )
                
set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp 
	             ${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp 
	             ${CMAKE_CURRENT_SOURCE_DIR}/slice_parser.cpp 
	             ${CMAKE_CURRENT_SOURCE_DIR}/bool_parser.cpp
			     ${CMAKE_CURRENT_SOURCE_DIR}/value_parser.cpp 
			     ${CMAKE_CURRENT_SOURCE_DIR}/string_parser.cpp)

install(FILES ${HEADER_FILES}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/parsers)

    
set(PNINEXUS_HEADER_FILES ${PNINEXUS_HEADER_FILES} ${HEADER_FIELS} PARENT_SCOPE)
set(PNINEXUS_SOURCE_FILES ${PNINEXUS_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)
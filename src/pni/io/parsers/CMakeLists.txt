set(HEADER_FILES conversion_trait.hpp
                 vector_parser.hpp
                 parser.hpp
                 string_parser.hpp
                 value_parser.hpp
                 slice_parser.hpp
                 bool_parser.hpp
                 complex_parser.hpp
                 vector_parser.hpp
                 )
                
set(SOURCE_FILES utils.cpp 
	             parser.cpp 
	             slice_parser.cpp 
	             bool_parser.cpp
			     value_parser.cpp 
			    string_parser.cpp)

install(FILES ${HEADER_FILES}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/io/parsers)

    
set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FIELS} PARENT_SCOPE)
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)
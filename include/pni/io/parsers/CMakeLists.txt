set(HEADER_FILES array_parser.hpp delimiter_parser.hpp exceptions.hpp
                 record_parser.hpp slice_parser.hpp value_parser.hpp)

install(FILES ${HEADER_FILES} 
    DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io/parsers)

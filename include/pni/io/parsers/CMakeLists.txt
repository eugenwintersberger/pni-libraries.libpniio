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

install(FILES ${HEADER_FILES}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/io/parsers)

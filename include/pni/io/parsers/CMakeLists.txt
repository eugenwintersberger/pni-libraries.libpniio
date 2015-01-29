set(HEADER_FILES spirit_rules.hpp
                 complex_rule.hpp
                 delimiter_rule.hpp 
                 value_rule.hpp
                 get_rule_type.hpp

                 array_parser.hpp 
                 record_parser.hpp 
                 slice_parser.hpp 
                 container_parser.hpp
                 parser.hpp
                 primitive_type_parser.hpp
                 string_parser.hpp
                 byte_integer_parser.hpp
                 )

install(FILES ${HEADER_FILES} 
    DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io/parsers)

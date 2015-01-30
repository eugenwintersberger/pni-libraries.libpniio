set(HEADER_FILES spirit_rules.hpp
                 complex_rule.hpp
                 delimiter_rule.hpp 
                 value_rule.hpp
                 get_rule_type.hpp
                 sequence_rule.hpp
                 slice_rule.hpp 
                 conversion_trait.hpp

                 vector_parser.hpp
                 parser.hpp
                 string_parser.hpp
                 )

install(FILES ${HEADER_FILES} 
    DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io/parsers)

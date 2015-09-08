set(HEADER_FILES 
                 float_policy.hpp
                 complex_generator.hpp   
                 value_generator.hpp             
                 primitive_generators.hpp
                 spirit_container_traits.hpp

                 get_generator.hpp
                 formatter.hpp                                  
                 scalar_format.hpp
                 vector_format.hpp
                 )

install(FILES ${HEADER_FILES} 
    DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io/formatters)

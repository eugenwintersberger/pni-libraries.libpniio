set(HEADER_FILES 
                 float_policy.hpp
                 complex_generator.hpp

                 get_generator.hpp
                 formatter.hpp
                 )

install(FILES ${HEADER_FILES} 
    DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io/formatters)

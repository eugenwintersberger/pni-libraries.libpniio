set(HEADER_FILES                              
                 scalar_format.hpp
                 vector_format.hpp
                 )

install(FILES ${HEADER_FILES}
    DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io/formatters)

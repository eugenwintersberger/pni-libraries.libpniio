set(HEADER_FILES cbf_reader.hpp dectris_reader.hpp types.hpp)

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io/cbf)

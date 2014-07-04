set(HEADER_FILES  nxpath.hpp parser.hpp utils.hpp )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io/nx/nxpath)

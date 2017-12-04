set(HEADER_FILES  nxpath.hpp 
                  parser.hpp 
                  utils.hpp 
                  make_relative.hpp
                  )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/io/nx/nxpath)

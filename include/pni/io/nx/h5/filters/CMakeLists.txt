set(HEADER_FILES lzf_filter.h lzf.h lzfP.h)
install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io/nx/h5/filters)

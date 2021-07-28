set(SOURCES ascii_io.cpp)


add_executable(ascii_io ascii_io.cpp)
target_link_libraries(ascii_io pninexus)

add_executable(fio_reader fio_reader.cpp)
target_link_libraries(fio_reader pninexus)

add_executable(cbf_reader cbf_reader.cpp)
target_link_libraries(cbf_reader pninexus)

add_executable(tif_reader tif_reader.cpp)
target_link_libraries(tif_reader pninexus)

install(FILES ${SOURCES} 
        DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}${LIBRARY_VERSION}-doc/examples/general")
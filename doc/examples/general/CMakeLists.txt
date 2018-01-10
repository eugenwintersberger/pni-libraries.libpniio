set(SOURCES ascii_io.cpp)


add_executable(ascii_io ascii_io.cpp)
target_link_libraries(ascii_io pniio)

add_executable(fio_reader fio_reader.cpp)
target_link_libraries(fio_reader pniio)

install(FILES ${SOURCES} 
    DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}${LIBRARY_VERSION}-doc/examples/general")
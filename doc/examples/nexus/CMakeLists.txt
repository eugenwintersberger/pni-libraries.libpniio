
set(SOURCES count_detectors.cpp
            count_entries.cpp
            gather_detectors.cpp
            ioqueue.hpp            
            simple_io.cpp
            thread_clireader.cpp
            thread_clireader.hpp
            thread_ex1.cpp
            thread_ex1.hpp
            thread_writer.hpp
            thread_writer.cpp         
            )

add_executable(count_detectors count_detectors.cpp)
target_link_libraries(count_detectors pniio)

add_executable(count_entries count_entries.cpp)
target_link_libraries(count_entries pniio)

add_executable(gather_detectors gather_detectors.cpp)
target_link_libraries(gather_detectors pniio)

add_executable(simple_io simple_io.cpp)
target_link_libraries(simple_io pniio)

add_executable(thread1 thread_ex1.cpp thread_writer.cpp thread_clireader.cpp)
target_link_libraries(thread1 pniio pthread)

install(FILES ${SOURCES} 
    DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}${LIBRARY_VERSION}-doc/examples/nexus")

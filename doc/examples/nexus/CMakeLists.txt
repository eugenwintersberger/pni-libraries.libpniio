
set(SOURCES Makefile
            nxfile_ex1.cpp
            nxgroup_ex1.cpp
            nxgroup_ex2.cpp
            nxnumfield_ex1.cpp
            nxnumfield_ex2.cpp
            nxnumfield_ex4.cpp
            nxstrfield_ex1.cpp
            nxstrfield_ex2.cpp
            nxstrfield_ex2.log
            nxbinfield_ex1.cpp
            nexus.png
            simple_ex1.cpp
            simple_io.cpp
            NXHelper.cpp
            NXHelper.hpp
            thread_ex1.cpp
            nxpath_match.xml
            nxpath_match.cpp
            count_entries.cpp
            count_detectors.cpp
            gather_detectors.cpp
            )
#Motor.hpp
#record_parser.cpp

add_executable(count_detectors count_detectors.cpp)
target_link_libraries(count_detectors pniio)

add_executable(count_entries count_entries.cpp)
target_link_libraries(count_entries pniio)

add_executable(gather_detectors gather_detectors.cpp)
target_link_libraries(gather_detectors pniio)

add_executable(simple_io simple_io.cpp)
target_link_libraries(simple_io pniio)

add_executable(thread1 thread_ex1.cpp)
target_link_libraries(thread1 pniio pthread)

install(FILES ${SOURCES} 
    DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}${LIBRARY_VERSION}-doc/examples/nexus")


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

install(FILES ${SOURCES} 
    DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}${LIBRARY_VERSION}-doc/examples/nexus")

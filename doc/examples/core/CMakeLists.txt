set(SOURCES Makefile
  array_arithmetic1.cpp
            array_arithmetic2.cpp
            array_arithmetic3.cpp
            array_create.cpp
            array_inquery.cpp
            array_linear_access.cpp
            array_multiindex.cpp
            array_stl.cpp
            array_view_container.cpp
            array_view.cpp
             copy_file.cpp
             record.dat
             record2.dat
             example_array2.cpp
             example_array3.cpp
             example_array4.cpp
             type_erasure1.cpp
             type_erasure2.cpp
             type_erasure3.cpp
             type_erasure_record.cpp
             )

foreach(EXAMPLE ${SOURCES})
    configure_file(${EXAMPLE} ${EXAMPLE} COPYONLY)
endforeach()

install(FILES ${SOURCES} 
        DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}${LIBRARY_VERSION}-doc/examples/core"
        OPTIONAL
        COMPONENT doc_examples
        )

add_custom_target(install-examples
    DEPENDS ${SOURCES}
    COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=doc_examples
    -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake)

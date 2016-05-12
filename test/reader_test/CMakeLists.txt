set(SOURCES tiff_reader_test.cpp
            cbf_reader_test.cpp
           )

set(DATAFILES ii8.tiff ii32.tiff iui8.tiff)

foreach(F ${DATAFILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()

set_source_files_properties(tiff_reader_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=Testing data readers")
add_executable(reader_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(reader_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})


add_test(NAME "reader-test" COMMAND reader_test)
add_dependencies(check reader_test)

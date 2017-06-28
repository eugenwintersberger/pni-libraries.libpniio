set(SOURCES tiff_reader_test.cpp
            cbf_reader_test.cpp
           )

set(DATAFILES ii8.tiff 
              ii32.tiff 
              iui8.tiff 
              ui32.tiff 
              idl_file.tif
              LAOS3_05461.cbf)

foreach(F ${DATAFILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()

set_source_files_properties(tiff_reader_test.cpp PROPERTIES
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=Testing data readers")
add_executable(reader_test  ${SOURCES})
target_link_libraries(reader_test pniio Boost::unit_test_framework)
add_test(NAME "reader-test" 
         COMMAND reader_test
         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/reader_test)

add_executable(idl_tif_reader_test idl_tif_reader)
target_link_libraries(idl_tif_reader_test pniio Boost::unit_test_framework)
add_test(NAME "IDL-tif-read"
         COMMAND idl_tif_reader_test
         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/reader_test)

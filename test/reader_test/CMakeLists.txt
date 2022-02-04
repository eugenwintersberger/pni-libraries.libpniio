set(SOURCES tiff_reader_test.cpp
            cbf_reader_test.cpp
           )

set(DATAFILES ii8.tiff 
              ii32.tiff 
              iui8.tiff 
              ui32.tiff 
              idl_file.tif
              LAOS3_05461.cbf
              scan_mca_00001.fio
              tstfile_00012.fio)

foreach(F ${DATAFILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()

set_source_files_properties(tiff_reader_test.cpp PROPERTIES
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=Testing data readers")
add_executable(reader_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(reader_test pninexus h5cpp::h5cpp Boost::unit_test_framework)
add_test(NAME "reader-test" 
         COMMAND reader_test
         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/reader_test)

set_source_files_properties(idl_tif_reader.cpp PROPERTIES
	                        COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=Testing TIF reader with IDL generated files")
add_executable(idl_tif_reader_test EXCLUDE_FROM_ALL idl_tif_reader.cpp)
target_link_libraries(idl_tif_reader_test pninexus h5cpp::h5cpp Boost::unit_test_framework)
add_test(NAME "IDL-tif-read"
         COMMAND idl_tif_reader_test
         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/reader_test)
        
set_source_files_properties(fio_reader_test.cpp PROPERTIES
	                        COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=Testing the FIO reader")
add_executable(fio_reader_test EXCLUDE_FROM_ALL fio_reader_test.cpp)
target_link_libraries(fio_reader_test pninexus h5cpp::h5cpp Boost::unit_test_framework)
add_test(NAME "pni::fio_reader"
	     COMMAND fio_reader_test
	     WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/reader_test)

	         
add_dependencies(check reader_test	                    
  idl_tif_reader_test
  fio_reader_test)

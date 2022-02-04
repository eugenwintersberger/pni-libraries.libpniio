add_executable(exception_record_test EXCLUDE_FROM_ALL exception_record_test.cpp)
target_link_libraries(exception_record_test pninexus h5cpp::h5cpp
                     Boost::unit_test_framework)
target_compile_definitions(exception_record_test PRIVATE
         BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing exception record")
add_dependencies(check exception_record_test)

add_boost_logging_test("Exceptions:exception_record_test"
                       exception_record_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)



add_executable(exception_test EXCLUDE_FROM_ALL exception_test.cpp)
target_link_libraries(exception_test pninexus h5cpp::h5cpp
                      Boost::unit_test_framework)
target_compile_definitions(exception_test PRIVATE
    BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing the exception base class")
add_dependencies(check exception_test)

add_boost_logging_test("Exceptions:exception_test"
                       exception_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)


#===============================================================================
add_executable(memory_allocation_error_test EXCLUDE_FROM_ALL
               memory_allocation_error_test.cpp)
target_link_libraries(memory_allocation_error_test PRIVATE
                      pninexus h5cpp::h5cpp
                      Boost::unit_test_framework)
target_compile_definitions(memory_allocation_error_test
                      PRIVATE
     BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing memory allocation error exception")
add_boost_logging_test("Exceptions:memory_allocation_error"
                       memory_allocation_error_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)
add_dependencies(check memory_allocation_error_test)

#===============================================================================
add_executable(memory_not_allocated_error_test EXCLUDE_FROM_ALL
               memory_not_allocated_error_test.cpp)
target_link_libraries(memory_not_allocated_error_test PRIVATE
                      pninexus h5cpp::h5cpp
                      Boost::unit_test_framework)
target_compile_definitions(memory_not_allocated_error_test
                      PRIVATE
     BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing memory not allocated exception")
add_boost_logging_test("Exceptions:memory_not_allocated_error"
                       memory_not_allocated_error_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)
add_dependencies(check memory_not_allocated_error_test)          

#===============================================================================
add_executable(shape_mismatch_error_test EXCLUDE_FROM_ALL
               shape_mismatch_error_test.cpp)
target_link_libraries(shape_mismatch_error_test PRIVATE
                      pninexus h5cpp::h5cpp
                      Boost::unit_test_framework)
target_compile_definitions(shape_mismatch_error_test
                      PRIVATE
     BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing shape mismatch exception")
add_boost_logging_test("Exceptions:shape_mismatch_error"
                       shape_mismatch_error_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)
add_dependencies(check shape_mismatch_error_test)

#===============================================================================
add_executable(size_mismatch_error_test EXCLUDE_FROM_ALL
               size_mismatch_error_test.cpp)
target_link_libraries(size_mismatch_error_test PRIVATE
                      pninexus h5cpp::h5cpp
                      Boost::unit_test_framework)
target_compile_definitions(size_mismatch_error_test
                      PRIVATE
     BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing size mismatch exception")
add_boost_logging_test("Exceptions:size_mismatch_error"
                       size_mismatch_error_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)
add_dependencies(check size_mismatch_error_test)

#===============================================================================
add_executable(index_error_test EXCLUDE_FROM_ALL
               index_error_test.cpp)
target_link_libraries(index_error_test PRIVATE
                      pninexus h5cpp::h5cpp
                      Boost::unit_test_framework)
target_compile_definitions(index_error_test
                      PRIVATE
     BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing index error exception")
add_boost_logging_test("Exceptions:index_error_test"
                       index_error_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)
add_dependencies(check index_error_test)                      

#===============================================================================
add_executable(key_error_test EXCLUDE_FROM_ALL
               key_error_test.cpp)
target_link_libraries(key_error_test PRIVATE
                      pninexus h5cpp::h5cpp
                      Boost::unit_test_framework)
target_compile_definitions(key_error_test
                      PRIVATE
     BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing key error exception")
add_boost_logging_test("Exceptions:key_error_test"
                       key_error_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)
add_dependencies(check key_error_test)                      

#===============================================================================
add_executable(file_error_test EXCLUDE_FROM_ALL
               file_error_test.cpp)
target_link_libraries(file_error_test PRIVATE
                      pninexus h5cpp::h5cpp
                      Boost::unit_test_framework)
target_compile_definitions(file_error_test
                      PRIVATE
     BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing file error exception")
add_boost_logging_test("Exceptions:file_error_test"
                       file_error_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)
add_dependencies(check file_error_test)                      

#===============================================================================
add_executable(type_error_test EXCLUDE_FROM_ALL
               type_error_test.cpp)
target_link_libraries(type_error_test PRIVATE
                      pninexus h5cpp::h5cpp
                      Boost::unit_test_framework)
target_compile_definitions(type_error_test
                      PRIVATE
     BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing type error exception")
add_boost_logging_test("Exceptions:type_error_test"
                       type_error_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)
add_dependencies(check type_error_test)                      

#===============================================================================
add_executable(value_error_test EXCLUDE_FROM_ALL
               value_error_test.cpp)
target_link_libraries(value_error_test PRIVATE
                      pninexus h5cpp::h5cpp
                      Boost::unit_test_framework)
target_compile_definitions(value_error_test
                      PRIVATE
     BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing value error exception")
add_boost_logging_test("Exceptions:value_error_test"
                       value_error_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)
add_dependencies(check value_error_test)                      

#===============================================================================
add_executable(range_error_test EXCLUDE_FROM_ALL
               range_error_test.cpp)
target_link_libraries(range_error_test PRIVATE
                      pninexus h5cpp::h5cpp
                      Boost::unit_test_framework)
target_compile_definitions(range_error_test
                      PRIVATE
     BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing range error exception")
add_boost_logging_test("Exceptions:range_error_test"
                       range_error_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)
add_dependencies(check range_error_test)                      

#===============================================================================
add_executable(not_implemented_error_test EXCLUDE_FROM_ALL
               not_implemented_error_test.cpp)
target_link_libraries(not_implemented_error_test PRIVATE
                      pninexus h5cpp::h5cpp
                      Boost::unit_test_framework)
target_compile_definitions(not_implemented_error_test
                      PRIVATE
     BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing not-implemented error exception")
add_boost_logging_test("Exceptions:not_implemented_error_test"
                       not_implemented_error_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)
add_dependencies(check not_implemented_error_test)                      

#===============================================================================
add_executable(iterator_error_test EXCLUDE_FROM_ALL
               iterator_error_test.cpp)
target_link_libraries(iterator_error_test PRIVATE
                      pninexus h5cpp::h5cpp
                      Boost::unit_test_framework)
target_compile_definitions(iterator_error_test
                      PRIVATE
     BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing iterator error exception")
add_boost_logging_test("Exceptions:iterator_error_test"
                       iterator_error_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)
add_dependencies(check iterator_error_test)                      

#===============================================================================
add_executable(cli_argument_error_test EXCLUDE_FROM_ALL
               cli_argument_error_test.cpp)
target_link_libraries(cli_argument_error_test PRIVATE
                      pninexus h5cpp::h5cpp
                      Boost::unit_test_framework)
target_compile_definitions(cli_argument_error_test
                      PRIVATE
              BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing CLI argument error exception")
add_boost_logging_test("Exceptions:cli_argument_error_test"
                       cli_argument_error_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)
add_dependencies(check cli_argument_error_test)                      

#===============================================================================
add_executable(cli_option_error_test EXCLUDE_FROM_ALL
               cli_option_error_test.cpp)
target_link_libraries(cli_option_error_test PRIVATE
                      pninexus h5cpp::h5cpp
                      Boost::unit_test_framework)
target_compile_definitions(cli_option_error_test
                      PRIVATE
              BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing CLI option error exception")
add_boost_logging_test("Exceptions:cli_option_error_test"
                       cli_option_error_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)
add_dependencies(check cli_option_error_test)                      

#===============================================================================
add_executable(cli_error_test EXCLUDE_FROM_ALL
               cli_error_test.cpp)
target_link_libraries(cli_error_test PRIVATE
                      pninexus h5cpp::h5cpp
                      Boost::unit_test_framework)
target_compile_definitions(cli_error_test
                      PRIVATE
          BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing general CLI error exception")
add_boost_logging_test("Exceptions:cli_error_test"
                       cli_error_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)
add_dependencies(check cli_error_test)                      

#===============================================================================
add_executable(cli_help_request_test EXCLUDE_FROM_ALL
               cli_help_request_test.cpp)
target_link_libraries(cli_help_request_test PRIVATE
                      pninexus h5cpp::h5cpp
                      Boost::unit_test_framework)
target_compile_definitions(cli_help_request_test
                      PRIVATE
          BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing CLI help request exception")
add_boost_logging_test("Exceptions:cli_help_request_test"
                       cli_help_request_test
                       ${PROJECT_BINARY_DIR}/test/exceptions)
add_dependencies(check cli_help_request_test)                      

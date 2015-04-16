set(SOURCES attribute_tests.cpp
            scalar_attribute_test_complex128.cpp
            scalar_attribute_test_complex32.cpp
            scalar_attribute_test_complex64.cpp
            scalar_attribute_test_float128.cpp
            scalar_attribute_test_float32.cpp
            scalar_attribute_test_float64.cpp
            scalar_attribute_test_int16.cpp
            scalar_attribute_test_int32.cpp
            scalar_attribute_test_int64.cpp
            scalar_attribute_test_int8.cpp
            scalar_attribute_test_uint16.cpp
            scalar_attribute_test_uint32.cpp
            scalar_attribute_test_uint64.cpp
            scalar_attribute_test_uint8.cpp
            )

set(XMLFILES  scalar_attribute_complex128.xml
              scalar_attribute_complex32.xml
              scalar_attribute_complex64.xml
              scalar_attribute_float128.xml
              scalar_attribute_float32.xml
              scalar_attribute_float64.xml
              scalar_attribute_int16.xml
              scalar_attribute_int32.xml
              scalar_attribute_int64.xml
              scalar_attribute_int8.xml
              scalar_attribute_uint16.xml
              scalar_attribute_uint32.xml
              scalar_attribute_uint64.xml
              scalar_attribute_uint8.xml
             )


foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

add_executable(attribute_tests ${SOURCES})
target_link_libraries(attribute_tests pniio ${CPPUNIT_LIBRARIES})
add_test(NAME "XML::attribute_tests"
         COMMAND attribute_tests)

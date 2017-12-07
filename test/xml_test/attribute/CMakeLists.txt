
#-----------------------------------------------------------------------------
# build common code for attributes
#-----------------------------------------------------------------------------
add_library(attr_test_common EXCLUDE_FROM_ALL OBJECT attr_utils.cpp)
target_include_directories(attr_test_common PRIVATE
${PROJECT_BINARY_DIR}/test/xml_test/attribute)

set(CLEANFILES)

#-----------------------------------------------------------------------------
# data types and test data for scalar attributes
#-----------------------------------------------------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(TYPES uint8 int8 uint16 int16 uint32 int32 uint64 int64
              float32 float64
              complex32 complex64
              string
              bool_t)

    set(TYPEIDS UINT8 INT8 UINT16 INT16 UINT32 INT32 UINT64 INT64
               FLOAT32 FLOAT64
               COMPLEX32 COMPLEX64
               STRING BOOL)

    set(DATA_STRS 1 -4 200 -234 4000 23456 4013945 -4013945
                  2.3455 -1.233e+4
                  "34.+j123.e-3" "-23.-I8.203"
                  "hello word a stupid text"
                  true)

    set(DATA_CPPS 1 -4 200 -234 4000 23456 4013945 -4013945
                  2.3455f -1.233e+4
                  "34.f,123.e-3f" "-23.,-8.203"
                  "\"hello word a stupid text\""
                  true)

else()
    set(TYPES uint8 int8 uint16 int16 uint32 int32 uint64 int64
              float32 float64 float128 complex32 complex64 complex128 string
              bool_t)

    set(TYPEIDS UINT8 INT8 UINT16 INT16 UINT32 INT32 UINT64 INT64
               FLOAT32 FLOAT64 FLOAT128
               COMPLEX32 COMPLEX64 COMPLEX128
               STRING BOOL)

    set(DATA_STRS 1 -4 200 -234 4000 23456 4013945 -4013945
                  2.3455 -1.233e+4  123.24354e-4
                  "34.+j123.e-3" "-23.-I8.203" "123.+I340."
                  "hello word a stupid text"
                  true)

    set(DATA_CPPS 1 -4 200 -234 4000 23456 4013945 -4013945
                  2.3455f -1.233e+4  123.24354e-4
                  "34.f,123.e-3f" "-23.,-8.203" "123,340"
                  "\"hello word a stupid text\""
                  true)
endif()

#------------------------------------------------------------------------------
# generating test code for scalar attribute data
#------------------------------------------------------------------------------

list(LENGTH TYPES NTYPES)
math(EXPR TYPERANGE "${NTYPES}-1")

set(GEN_SRC_PATH ${PROJECT_BINARY_DIR}/test/xml_test/attribute)

foreach(index RANGE ${TYPERANGE})
    list(GET TYPES     ${index} TYPE)
    list(GET TYPEIDS   ${index} TYPEID)
    list(GET DATA_STRS ${index} DATA_STR)
    list(GET DATA_CPPS ${index} CPP_DATA)

    message(STATUS "generate scalar attribute test for type ${TYPE} ...")
    set(CPPFILE scalar_attribute_test_${TYPE}.cpp)
    set(XMLFILE scalar_attribute_test_${TYPE}.xml)
    set(NXSFILE scalar_attribute_test_${TYPE}.nxs )
    set(TARGET_NAME scalar_attribute_test_${TYPE})
    configure_file(scalar_attribute_test.xml.in ${XMLFILE} @ONLY)

    if(TYPE STREQUAL float128)
        message(STATUS "setup for float128 comparison")
        set(EQUALITY_CHECK "BOOST_CHECK_CLOSE(float128(data),expected,1.e-14);")
    elseif(TYPE STREQUAL complex128)
        message(STATUS "setup for complex128 comnparison")
        set(EQUALITY_CHECK "BOOST_CHECK_CLOSE(std::real(data),std::real(expected),1.e-14);\n
                            BOOST_CHECK_CLOSE(std::imag(data),std::imag(expected),1.e-14);")
    else()
        set(EQUALITY_CHECK "BOOST_CHECK_EQUAL(data,expected);")
    endif()

    #configure the source file and set the target source
    configure_file(scalar_attribute_test.cpp.in ${CPPFILE} @ONLY)
    set(TARGET_SRC ${GEN_SRC_PATH}/${CPPFILE})

    add_executable(${TARGET_NAME} EXCLUDE_FROM_ALL ${TARGET_SRC}
                                  $<TARGET_OBJECTS:attr_test_common>
                                  $<TARGET_OBJECTS:xml_test_common>
                                  $<TARGET_OBJECTS:test_common>
    )
    target_compile_definitions(${TARGET_NAME} PRIVATE
    "BOOST_TEST_DYN_LINK;BOOST_TEST_MODULE=testing scalar XML attributes of type ${TYPE}")
    target_link_libraries(${TARGET_NAME} PRIVATE pniio Boost::unit_test_framework
    )
    target_include_directories(${TARGET_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/test/xml_test/attribute)

    add_boost_logging_test("XML:attribute:${TYPE}:scalar" ${TARGET_NAME}
                            ${GEN_SRC_PATH} )

    list(APPEND CLEANFILES "${CPPFILE} ${NXSFILE} ${XMLFILE}")
endforeach()

#-----------------------------------------------------------------------------
# data types and test data for array attributes
#-----------------------------------------------------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(ARR_TYPES uint8 int8 uint16 int16 uint32 int32 uint64 int64
              float32 float64
              complex32 complex64
              bool_t)

    set(ARR_TYPEIDS UINT8 INT8 UINT16 INT16 UINT32 INT32 UINT64 INT64
               FLOAT32 FLOAT64
               COMPLEX32 COMPLEX64  BOOL)

    set(ARR_DATA_STRS "1 2 3" "-4 3 -10" "200 300 400" "-234 500 -34"
                      "4000 2000 345" "23456 -3453 40392" "4013945 39458 14056"
                      "-4013945 304213 -405982"
                      "2.3455 -34.e+2 -42.e-5"
                      "-1.233e+4 239e-3 30495.e-8"
                      "34.+j123.e-3 34.e-2+I98.3 453.98-i743.29"
                      "-23.-I8.203 893.e+4-j23.12 9.e-8+I732.e+3"
                      "true true false")
    set(ARR_DATA_CPPS "1, 2, 3" "-4, 3, -10" "200, 300, 400" "-234, 500, -34"
                      "4000, 2000, 345" "23456, -3453, 40392" "4013945,39458,14056"
                      "-4013945, 304213, -405982"
                      "2.3455f, -34.e+2f, -42.e-5f"
                      "-1.233e+4, 239e-3, 30495.e-8"
                      "{34.f,123.e-3f},{34.e-2f,98.3f},{453.98f,-743.29f}"
                      "{-23.,-8.203},{893e+4,-23.12},{9.e-8,732e+3}"
                      "true,true,false")
else()
    set(ARR_TYPES uint8 int8 uint16 int16 uint32 int32 uint64 int64
              float32 float64 float128 complex32 complex64 complex128
              bool_t)

    set(ARR_TYPEIDS UINT8 INT8 UINT16 INT16 UINT32 INT32 UINT64 INT64
               FLOAT32 FLOAT64 FLOAT128
               COMPLEX32 COMPLEX64 COMPLEX128 BOOL)

    set(ARR_DATA_STRS "1 2 3" "-4 3 -10" "200 300 400" "-234 500 -34"
                      "4000 2000 345" "23456 -3453 40392" "4013945 39458 14056"
                      "-4013945 304213 -405982"
                      "2.3455 -34.e+2 -42.e-5"
                      "-1.233e+4 239e-3 30495.e-8"
                      "123.24354e-4 40394.e-4 1.23e+5"
                      "34.+j123.e-3 34.e-2+I98.3 453.98-i743.29"
                      "-23.-I8.203 893.e+4-j23.12 9.e-8+I732.e+3"
                      "123.+I340. -I34.9 345.2"
                      "true true false")
    set(ARR_DATA_CPPS "1, 2, 3" "-4, 3, -10" "200, 300, 400" "-234, 500, -34"
                      "4000, 2000, 345" "23456, -3453, 40392" "4013945,39458,14056"
                      "-4013945, 304213, -405982"
                      "2.3455f, -34.e+2f, -42.e-5f"
                      "-1.233e+4, 239e-3, 30495.e-8"
                      "123.24354e-4, 40394.e-4, 1.23e+5"
                      "{34.f,123.e-3f},{34.e-2f,98.3f},{453.98f,-743.29f}"
                      "{-23.,-8.203},{893e+4,-23.12},{9.e-8,732e+3}"
                      "{123,340},{0.,-34.9},{345.2,0.}"
                      "true,true,false")
endif()

#------------------------------------------------------------------------------
# generating test code for array attribute data
#------------------------------------------------------------------------------

list(LENGTH ARR_TYPES NTYPES)
math(EXPR TYPERANGE "${NTYPES}-1")

foreach(index RANGE ${TYPERANGE})
    list(GET ARR_TYPES ${index} TYPE)
    list(GET ARR_TYPEIDS ${index} TYPEID)
    list(GET ARR_DATA_STRS ${index} DATA_STR)
    list(GET ARR_DATA_CPPS ${index} CPP_DATA)

    message(STATUS "generate array attribute test for type ${TYPE} ...")
    set(CPPFILE array_attribute_test_${TYPE}.cpp)
    set(XMLFILE array_attribute_test_${TYPE}.xml)
    set(NXSFILE array_attribute_test_${TYPE}.nxs )
    set(TARGET_NAME array_attribute_test_${TYPE})
    configure_file(array_attribute_test.xml.in ${XMLFILE} @ONLY)

    if(TYPE STREQUAL float128)
        message(STATUS "setup for float128 comparison")
        set(EQUALITY_CHECK "BOOST_CHECK_CLOSE(float128(*d_iter),*r_iter,1.e-14);")
    elseif(TYPE STREQUAL complex128)
        message(STATUS "setup for complex128 comnparison")
        set(EQUALITY_CHECK "BOOST_CHECK_CLOSE(std::real(*d_iter),std::real(*r_iter),1.e-14);\n
                            BOOST_CHECK_CLOSE(std::imag(*d_iter),std::imag(*r_iter),1.e-14);")
    else()
        set(EQUALITY_CHECK "BOOST_CHECK_EQUAL(*d_iter,*r_iter);")
    endif()

    #configure the source file and set the target source
    configure_file(array_attribute_test.cpp.in ${CPPFILE} @ONLY)
    set(TARGET_SRC ${GEN_SRC_PATH}/${CPPFILE})

    add_executable(${TARGET_NAME} EXCLUDE_FROM_ALL ${TARGET_SRC}
                                  $<TARGET_OBJECTS:attr_test_common>
                                  $<TARGET_OBJECTS:xml_test_common>
                                  $<TARGET_OBJECTS:test_common>
    )
    target_compile_definitions(${TARGET_NAME} PRIVATE
    "BOOST_TEST_DYN_LINK;BOOST_TEST_MODULE=testing array XML attributes of type ${TYPE}")
    target_link_libraries(${TARGET_NAME} PRIVATE pniio Boost::unit_test_framework
    )
    target_include_directories(${TARGET_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/test/xml_test/attribute
    )

    add_boost_logging_test("XML:attribute:${TYPE}:array" ${TARGET_NAME}
                            ${GEN_SRC_PATH} )

endforeach()

set_directory_properties(PROPPERTIES
ADDITIONAL_MAKE_CLEAN_FILES "${CLEANFILES}}")

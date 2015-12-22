#-----------------------------------------------------------------------------
# data types and test data for scalar attributes 
#-----------------------------------------------------------------------------
set(TYPES uint8 int8 uint16 int16 uint32 int32 uint64 int64
          float32 float64 float128 complex32 complex64 complex128 string
          bool_t)

set(TYPEIDS UINT8 INT8 UINT16 INT16 UINT32 INT32 UINT64 INT64 
           FLOAT32 FLOAT64 FLOAT128
           COMPLEX32 COMPLEX64 COMPLEX128
           STRING BOOL)

set(DATA_STRS 1 -4 200 -234 4000 23456 4013945 -4013945 
              2.3455 -1.233e+4  123.24354e-4 
              "34.+j123.e-3" "-23.-I8.203" "123+I340"
              "hello word a stupid text"
              true)

set(DATA_CPPS 1 -4 200 -234 4000 23456 4013945 -4013945 
              2.3455 -1.233e+4  123.24354e-4 
              "34.,123.e-3" "-23.,-8.203" "123,340"
              "\"hello word a stupid text\""
              true)

#------------------------------------------------------------------------------
# generating test code for scalar attribute data
#------------------------------------------------------------------------------

list(LENGTH TYPES NTYPES)
math(EXPR TYPERANGE "${NTYPES}-1")
set(CPPFILES)
set(XMLFILES)
set(NXSFILES)

foreach(index RANGE ${TYPERANGE})
    list(GET TYPES ${index} TYPE)
    list(GET TYPEIDS ${index} TYPEID)
    list(GET DATA_STRS ${index} DATA_STR)
    list(GET DATA_CPPS ${index} CPP_DATA)

    message(STATUS "generate scalar field test for type ${TYPE} ...")
    set(XMLFILE scalar_field_test_${TYPE}.xml)
    list(APPEND XMLFILES ${XMLFILE})
    list(APPEND NXSFILES "scalar_field_test_${TYPE}.nxs")
    configure_file(scalar_field_test.xml.in ${XMLFILE} @ONLY)
    
    if(TYPE STREQUAL float128)
        message(STATUS "setup for float128 comparison")
        set(EQUALITY_CHECK "BOOST_CHECK_CLOSE(@TYPE@(data),expected,1.e-14);")
    elseif(TYPE STREQUAL complex128)
        message(STATUS "setup for complex128 comnparison")
        set(EQUALITY_CHECK "BOOST_CHECK_CLOSE(std::real(data),std::real(expected),1.e-14);\n\
                            BOOST_CHECK_CLOSE(std::imag(data),std::imag(expected),1.e-14);")
    else()
        set(EQUALITY_CHECK "BOOST_CHECK_EQUAL(data,expected);")
    endif()

    set(CPPFILE scalar_field_test_${TYPE}.cpp)
    list(APPEND CPPFILES ${CPPFILE})
    configure_file(scalar_field_test.cpp.in ${CPPFILE} @ONLY)


    if(index EQUAL 0)

        message(STATUS "Set flags for main file...")
        set_source_files_properties(${CPPFILE} PROPERTIES
            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK;BOOST_TEST_MODULE=testing xml attributes")
    endif()
                 
endforeach()

                   
#-----------------------------------------------------------------------------
# finally build the test target
#-----------------------------------------------------------------------------
add_library(field_test_common OBJECT EXCLUDE_FROM_ALL field_utils.cpp)

include_directories(${CMAKE_SOURCE_DIR}/test ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(field_test EXCLUDE_FROM_ALL ${CPPFILES}
                            $<TARGET_OBJECTS:field_test_common>)

target_link_libraries(field_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME "XML::field_tests"
         COMMAND field_test)

add_dependencies(check field_test)



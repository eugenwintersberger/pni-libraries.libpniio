#-----------------------------------------------------------------------------
# data types and test data for scalar attributes 
#-----------------------------------------------------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(TYPES uint8 int8 uint16 int16 uint32 int32 uint64 int64
              float32 float64 
              complex32 complex64 
              string 
              bool_t)

    set(DATA_STRS 1 -4 200 -234 4000 23456 4013945 -4013945 
                  2.3455 -1.233e+4  
                  "34.+j123.e-3" "-23.-I8.203" 
                  "hello word a stupid text"
                  true)

else()
    set(TYPES uint8 int8 uint16 int16 uint32 int32 uint64 int64
              float32 float64 float128 
              complex32 complex64 complex128 
              string 
              bool_t)

    set(DATA_STRS 1 -4 200 -234 4000 23456 4013945 -4013945 
                  2.3455 -1.233e+4  123.24354e-4 
                  "34.+j123.e-3" "-23.-I8.203" "123+I340"
                  "hello word a stupid text"
                  true)
endif()

#------------------------------------------------------------------------------
# generating test code for scalar attribute data
#------------------------------------------------------------------------------

list(LENGTH TYPES NTYPES)
math(EXPR TYPERANGE "${NTYPES}-1")
set(XMLFILES)

foreach(index RANGE ${TYPERANGE})
    list(GET TYPES ${index} TYPE)
    list(GET DATA_STRS ${index} DATA_STR)

    message(STATUS "generate scalar field test for type ${TYPE} ...")
    if(TYPE STREQUAL bool_t)
        set(XMLFILE scalar_test_bool.xml)
    else()
        set(XMLFILE scalar_test_${TYPE}.xml)
    endif()
    list(APPEND XMLFILES ${XMLFILE})
    configure_file(scalar_test.xml.in ${XMLFILE} @ONLY)
endforeach()

#-----------------------------------------------------------------------------
# data types and test data for array fields
#-----------------------------------------------------------------------------

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(ARR_TYPES uint8 int8 uint16 int16 uint32 int32 uint64 int64
          float32 float64 
          complex32 complex64 
          bool_t)

    set(ARR_DATA_STRS "1 2 3" "-4 3 -10" "200 300 400" "-234 500 -34"
                  "4000 2000 345" "23456 -3453 40392" "4013945 39458 14056"
                  "-4013945 304213 -405982"
                  "2.3455 -34.e+2 -42.e-5"
                  "-1.233e+4 239e-3 30495.e-8"
                  "34.+j123.e-3 34.e-2+I98.3 453.98-i743.29"
                  "-23.-I8.203 893e+4-j23.12 9.e-8+I732e+3"
                  "true true false")

else()
    set(ARR_TYPES uint8 int8 uint16 int16 uint32 int32 uint64 int64
          float32 float64 float128 
          complex32 complex64 complex128 
          bool_t)

    set(ARR_DATA_STRS "1 2 3" "-4 3 -10" "200 300 400" "-234 500 -34"
                  "4000 2000 345" "23456 -3453 40392" "4013945 39458 14056"
                  "-4013945 304213 -405982"
                  "2.3455 -34.e+2 -42.e-5"
                  "-1.233e+4 239e-3 30495.e-8"
                  "123.24354e-4 40394.e-4 1.23e+5"
                  "34.+j123.e-3 34.e-2+I98.3 453.98-i743.29"
                  "-23.-I8.203 893e+4-j23.12 9.e-8+I732e+3"
                  "123+I340 -I34.9 345.2"
                  "true true false")
endif()

#------------------------------------------------------------------------------
# generating test code for array field data
#------------------------------------------------------------------------------

list(LENGTH ARR_TYPES NTYPES)
math(EXPR TYPERANGE "${NTYPES}-1")

foreach(index RANGE ${TYPERANGE})
    list(GET ARR_TYPES ${index} TYPE)
    list(GET ARR_DATA_STRS ${index} DATA_STR)

    message(STATUS "generate array field test for type ${TYPE} ...")
    if(TYPE STREQUAL bool_t)
        set(XMLFILE multidim_test_bool.xml)
    else()
        set(XMLFILE multidim_test_${TYPE}.xml)
    endif()
    list(APPEND XMLFILES ${XMLFILE})
    configure_file(multidim_test.xml.in ${XMLFILE} @ONLY)

endforeach()
                   
#-----------------------------------------------------------------------------
# finally build the test target
#-----------------------------------------------------------------------------
add_library(field_test_common OBJECT field_utils.cpp)
target_compile_definitions(field_test_common PUBLIC BOOST_ALL_DYN_LINK)

include_directories(${CMAKE_SOURCE_DIR}/test ${CMAKE_CURRENT_SOURCE_DIR})
set_source_files_properties(field_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=testing XML field operations")
add_executable(field_test field_test.cpp
                          multidim_field_test.cpp
                          scalar_field_test.cpp
                          $<TARGET_OBJECTS:test_common>
                          $<TARGET_OBJECTS:xml_test_common>
                          $<TARGET_OBJECTS:field_test_common>)

target_link_libraries(field_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME "XML::field_tests"
         COMMAND field_test)

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set_property(TEST "XML::field_tests" APPEND PROPERTY
        ENVIRONMENT "PATH=${PATH_STRING}")
endif()


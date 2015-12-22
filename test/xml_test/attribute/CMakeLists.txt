
#-----------------------------------------------------------------------------
# list of types for which tests should be generated
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

    message(STATUS "generate scalar attribute test for type ${TYPE} ...")
    set(XMLFILE scalar_attribute_test_${TYPE}.xml)
    list(APPEND XMLFILES ${XMLFILE})
    list(APPEND NXSFILES "scalar_attribute_test_${TYPE}.nxs")
    configure_file(scalar_attribute_test.xml.in ${XMLFILE} @ONLY)
    
    if(TYPE STREQUAL float128)
        message(STATUS "setup for float128 comparison")
        set(EQUALITY_CHECK "BOOST_CHECK_CLOSE(@TYPE@(data),expected,1.e-14);")
    elseif(TYPE STREQUAL complex128)
        message(STATUS "setup for complex128 comnparison")
        set(EQUALITY_CHECK "BOOST_CHECK_CLOSE(std::real(data),std::real(expected),1.e-14);\n\
                            BOOST_CHECK_CLOSE(std::imag(data),std::imag(expected),1.e-1);")
    else()
        set(EQUALITY_CHECK "BOOST_CHECK_EQUAL(data,expected);")
    endif()

    set(CPPFILE scalar_attribute_test_${TYPE}.cpp)
    list(APPEND CPPFILES ${CPPFILE})
    configure_file(scalar_attribute_test.cpp.in ${CPPFILE} @ONLY)


    if(index EQUAL 0)

        message(STATUS "Set flags for main file...")
        set_source_files_properties(${CPPFILE} PROPERTIES
            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK;BOOST_TEST_MODULE=testing xml attributes")
    endif()
                 
endforeach()

set_directory_properties(PROPPERTIES 
                         ADDITIONAL_MAKE_CLEAN_FILES "${CPPFILES} ${XMLFILES} ${NXSFILES}")
           

#-----------------------------------------------------------------------------
# generate files required for scalar tests
#-----------------------------------------------------------------------------
#generate the list of required files
#set(SCALAR_SRCS)
#foreach(TYPE ${TYPES})
#    #set(XMLFILE scalar_attribute_${TYPE}.xml)
#    set(CPPFILE scalar_attribute_test_${TYPE}.cpp)
#    set(HPPFILE scalar_attribute_test_${TYPE}.hpp)
#
#    list(INSERT SCALAR_SRCS ${HPPFILE} ${CPPFILE} ${XMLFILE})
#endforeach()

#generate the files by calling the appropriate Python script
#add_custom_command(OUTPUT ${SCALAR_SRCS}
#                   COMMAND python generate_scalar_tests.py
#                   DEPENDS generate_scalar_tests.py
#                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

#-----------------------------------------------------------------------------
# generate files required for multidimensional tests
#-----------------------------------------------------------------------------
#generate the list of required files
#set(MDIM_SRCS)
#foreach(TYPE ${TYPES})
#        
#        if(NOT "${TYPE}" STREQUAL "string")
#            set(XMLFILE multidim_attribute_${TYPE}.xml)
#            set(CPPFILE multidim_attribute_test_${TYPE}.cpp)
#            set(HPPFILE multidim_attribute_test_${TYPE}.hpp)
#            list(INSERT MDIM_SRCS ${HPPFILE} ${CPPFILE} ${XMLFILE})
#        endif()
#
#endforeach()
#
#message("${MDIM_SRCS}")
#
#generate the files by calling the appropriate Python script
#add_custom_command(OUTPUT ${MDIM_SRCS}
#                   COMMAND python generate_multidim_tests.py
#                   DEPENDS generate_multidim_tests.py
#                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

#-----------------------------------------------------------------------------
# build common code for attributes
#-----------------------------------------------------------------------------
add_library(attr_test_common OBJECT EXCLUDE_FROM_ALL attr_utils.cpp)


#-----------------------------------------------------------------------------
# finally build the test target
#-----------------------------------------------------------------------------
include_directories(${CMAKE_SOURCE_DIR}/test ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(attribute_tests EXCLUDE_FROM_ALL ${CPPFILES} 
               $<TARGET_OBJECTS:attr_test_common>)
target_link_libraries(attribute_tests pniio
               ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME "XML::attribute_tests"
         COMMAND attribute_tests)

add_dependencies(check attribute_tests)

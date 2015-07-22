#-----------------------------------------------------------------------------
# list of types for which tests should be generated
#-----------------------------------------------------------------------------
set(TYPES uint8 int8 uint16 int16 uint32 int32 uint64 int64
          float32 float64 float128 complex32 complex64 complex128 string
          bool_t)

#-----------------------------------------------------------------------------
# copy generator scripts
#-----------------------------------------------------------------------------
configure_file(generate_scalar_tests.py generate_scalar_tests.py COPYONLY)
configure_file(generate_multidim_tests.py generate_multidim_tests.py COPYONLY)

#-----------------------------------------------------------------------------
# generate files required for scalar tests
#-----------------------------------------------------------------------------
#generate the list of required files
set(SCALAR_SRCS)
foreach(TYPE ${TYPES})
    set(XMLFILE scalar_field_${TYPE}.xml)
    set(CPPFILE scalar_field_test_${TYPE}.cpp)
    set(HPPFILE scalar_field_test_${TYPE}.hpp)

    list(INSERT SCALAR_SRCS ${HPPFILE} ${CPPFILE} ${XMLFILE})
endforeach()

#generate the files by calling the appropriate Python script
add_custom_command(OUTPUT ${SCALAR_SRCS}
                   COMMAND python generate_scalar_tests.py
                   DEPENDS generate_scalar_tests.py
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

#-----------------------------------------------------------------------------
# generate files required for multidimensional tests
#-----------------------------------------------------------------------------
#generate the list of required files
set(MDIM_SRCS)
foreach(TYPE ${TYPES})
        
        if(NOT "${TYPE}" STREQUAL "string")
            set(XMLFILE multidim_field_${TYPE}.xml)
            set(CPPFILE multidim_field_test_${TYPE}.cpp)
            set(HPPFILE multidim_field_test_${TYPE}.hpp)
            list(INSERT MDIM_SRCS ${HPPFILE} ${CPPFILE} ${XMLFILE})
        endif()

endforeach()

message("${MDIM_SRCS}")

#generate the files by calling the appropriate Python script
add_custom_command(OUTPUT ${MDIM_SRCS}
                   COMMAND python generate_multidim_tests.py
                   DEPENDS generate_multidim_tests.py
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
                   
#-----------------------------------------------------------------------------
# finally build the test target
#-----------------------------------------------------------------------------
include_directories(${CMAKE_SOURCE_DIR}/test)
add_executable(field_test EXCLUDE_FROM_ALL field_tests.cpp 
                            ${SCALAR_SRCS} 
                            ${MDIM_SRCS}
                            $<TARGET_OBJECTS:test_common>)
target_link_libraries(field_test pniio ${CPPUNIT_LIBRARIES})
add_test(NAME "XML::field_tests"
         COMMAND field_test)



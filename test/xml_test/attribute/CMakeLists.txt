
#-----------------------------------------------------------------------------
# list of types for which tests should be generated
#-----------------------------------------------------------------------------
set(TYPES uint8 int8 uint16 int16 uint32 int32 uint64 int64
          float32 float64 float128 complex32 complex64 complex128 string
          bool)

#-----------------------------------------------------------------------------
# copy generator scripts
#-----------------------------------------------------------------------------
configure_file(generate_scalar_tests.py generate_scalar_tests.py COPYONLY)

#-----------------------------------------------------------------------------
# generate files required for scalar tests
#-----------------------------------------------------------------------------
#generate the list of required files
set(SCALAR_SRCS)
foreach(TYPE ${TYPES})
    set(XMLFILE scalar_attribute_${TYPE}.xml)
    set(CPPFILE scalar_attribute_test_${TYPE}.cpp)
    set(HPPFILE scalar_attribute_test_${TYPE}.hpp)

    list(INSERT SCALAR_SRCS ${HPPFILE} ${CPPFILE} ${XMLFILE})
endforeach()

#generate the files by calling the appropriate Python script
add_custom_command(OUTPUT ${SCALAR_SRCS}
                   COMMAND python generate_scalar_tests.py
                   DEPENDS generate_scalar_tests.py
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

#-----------------------------------------------------------------------------
# finally build the test target
#-----------------------------------------------------------------------------
include_directories(${CMAKE_SOURCE_DIR}/test)
add_executable(attribute_tests attribute_tests.cpp ${SCALAR_SRCS} 
               $<TARGET_OBJECTS:test_common>)
target_link_libraries(attribute_tests pniio ${CPPUNIT_LIBRARIES})
add_test(NAME "XML::attribute_tests"
         COMMAND attribute_tests)

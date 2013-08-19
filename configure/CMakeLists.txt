include(CheckTypeSize)
include(CheckCXXSourceCompiles)
include(FindPkgConfig)
include(FindHDF5)


#===================================check the size of data types===============
check_type_size(uint8_t UINT8_SIZE)
if(NOT ${UINT8_SIZE} EQUAL 1)
    message(FATAL_ERROR "uint8_t size is not 1Byte!")
endif()

check_type_size(int8_t INT8_SIZE)
if(NOT ${INT8_SIZE} EQUAL 1)
    message(FATAL_ERROR "int8_t size is not 1Byte!")
endif()

check_type_size(uint16_t UINT16_SIZE)
if(NOT ${UINT16_SIZE} EQUAL 2)
    message(FATAL_ERROR "uint16_t size is not 2Byte!")
endif()

check_type_size(int16_t INT16_SIZE)
if(NOT ${INT16_SIZE} EQUAL 2)
    message(FATAL_ERROR "int16_t size is not 2Byte!")
endif()

check_type_size(uint32_t UINT32_SIZE)
if(NOT ${UINT32_SIZE} EQUAL 4)
    message(FATAL_ERROR "uint32_t size is not 4Byte!")
endif()

check_type_size(int32_t INT32_SIZE)
if(NOT ${INT32_SIZE} EQUAL 4)
    message(FATAL_ERROR "int32_t size is not 4Byte!")
endif()

check_type_size(uint64_t UINT64_SIZE)
if(NOT ${UINT64_SIZE} EQUAL 8)
    message(FATAL_ERROR "uint64_t size is not 8Byte!")
endif()

check_type_size(int64_t INT64_SIZE)
if(NOT ${INT64_SIZE} EQUAL 8)
    message(FATAL_ERROR "int64_t size is not 8Byte!")
endif()

check_type_size(float FLOAT32_SIZE)
if(NOT ${FLOAT32_SIZE} EQUAL 4)
    message(FATAL_ERROR "float size is not 4Byte!")
endif()

check_type_size(double FLOAT64_SIZE)
if(NOT ${FLOAT64_SIZE} EQUAL 8)
    message(FATAL_ERROR "double size is not 8Byte!")
endif()

check_type_size("long double" FLOAT128_SIZE)
if(NOT ${FLOAT128_SIZE} EQUAL 16)
    message(FATAL_ERROR "long double size is not 16Byte!")
endif()

#=================try to figure out some compiler capabilities=================
file(READ "bind_test.cpp" BIND_TEST_SOURCE)
check_cxx_source_compiles("${BIND_TEST_SOURCE}"  BIND_COMPILER_CHECK)
if(NOT BIND_COMPILER_CHECK)
    add_definitions(-DNO_STD_BIND)
endif()

file(READ "constexpr_test.cpp" CONST_EXPR_TEST_SOURCE)
check_cxx_source_compiles("${CONST_EXPR_TEST_SOURCE}" CONST_EXPR_TEST)
if(NOT CONST_EXPR_TEST)
    add_definitions(-DNOCEXPR)
endif()

file(READ "enum_bug_test.cpp" ENUM_BUG_TEST_SOURCE)
check_cxx_source_compiles("${ENUM_BUG_TEST_SOURCE}" ENUM_BUG_TEST)
if(NOT ENUM_BUG_TEST)
    add_definitions(-DENUMBUG)
endif()

file(READ "explicit_conversion_test.cpp" EXPLICIT_CONVERSION_TEST_SOURCE)
check_cxx_source_compiles("${EXPLICIT_CONVERSION_TEST_SOURCE}"
    EXPLICIT_CONVERSION_TEST)
if(NOT EXPLICIT_CONVERSION_TEST)
    add_definitions(-DNOEXPLICITCONV)
endif()

file(READ "foreach_test.cpp" FOREACH_TEST_SOURCE)
check_cxx_source_compiles("${FOREACH_TEST_SOURCE}" FOREACH_TEST)
if(NOT FOREACH_TEST)
    add_definitions(-DNOFOREACH)
endif()

file(READ "lambda_function_test.cpp" LAMBDA_FUNCTION_TEST_SOURCE)
check_cxx_source_compiles("${LAMBDA_FUNCTION_TEST_SOURCE}" LAMBDA_FUNCTION_TEST)
if(NOT LAMBDA_FUNCTION_TEST)
    add_definitions(-DNO_LAMBDA_FUNC)
endif()

file(READ "nullptr_test.cpp" NULLPTR_TEST_SOURCE)
check_cxx_source_compiles("${NULLPTR_TEST_SOURCE}" NULLPTR_TEST)
if(NOT NULLPTR_TEST)
    add_definitions(-Dnullptr=NULL)
endif()

file(READ "random_test.cpp" RANDOM_TEST_SOURCE)
check_cxx_source_compiles("${RANDOM_TEST_SOURCE}" RANDOM_TEST)
if(NOT RANDOM_TEST)
    add_definitions(-DNOCPPRAND)
endif()

file(READ "template_alias_test.cpp" TEMPLATE_ALIAS_TEST_SOURCE)
check_cxx_source_compiles("${TEMPLATE_ALIAS_TEST_SOURCE}" TEMPLATE_ALIAS_TEST)
if(NOT TEMPLATE_ALIAS_TEST)
    add_definitions(-DNOTMPALIAS)
endif()

#==========================check for libraries=====================================
#the only thing we have to do here is to check for pnicore
pkg_search_module(PNICORE_PKG REQUIRED pnicore)
pkg_search_module(CPPUNIT_PKG REQUIRED cppunit)

link_directories(${CPPUNIT_PKG_LIBRARY_DIRS})


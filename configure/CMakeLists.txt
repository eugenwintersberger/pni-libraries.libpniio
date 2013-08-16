include(CheckTypeSize)
include(CheckCXXSourceCompiles)
include(FindPkgConfig)

#===================================check the size of data types===============
check_type_size(uint8_t UINT8_SIZE)
if(NOT ${UINT8_SIZE} EQUAL 1)
    message(FATAL_ERROR "uint8_t size is not 1Byte!")
endif(NOT ${UINT8_SIZE}  EQUAL 1)

check_type_size(int8_t INT8_SIZE)
if(NOT ${INT8_SIZE} EQUAL 1)
    message(FATAL_ERROR "int8_t size is not 1Byte!")
endif(NOT ${INT8_SIZE}  EQUAL 1)

check_type_size(uint16_t UINT16_SIZE)
if(NOT ${UINT16_SIZE} EQUAL 2)
    message(FATAL_ERROR "uint16_t size is not 2Byte!")
endif(NOT ${UINT16_SIZE}  EQUAL 2)

check_type_size(int16_t INT16_SIZE)
if(NOT ${INT16_SIZE} EQUAL 2)
    message(FATAL_ERROR "int16_t size is not 2Byte!")
endif(NOT ${INT16_SIZE}  EQUAL 2)

check_type_size(uint32_t UINT32_SIZE)
if(NOT ${UINT32_SIZE} EQUAL 4)
    message(FATAL_ERROR "uint32_t size is not 4Byte!")
endif(NOT ${UINT32_SIZE}  EQUAL 4)

check_type_size(int32_t INT32_SIZE)
if(NOT ${INT32_SIZE} EQUAL 4)
    message(FATAL_ERROR "int32_t size is not 4Byte!")
endif(NOT ${INT32_SIZE}  EQUAL 4)

check_type_size(uint64_t UINT64_SIZE)
if(NOT ${UINT64_SIZE} EQUAL 8)
    message(FATAL_ERROR "uint64_t size is not 8Byte!")
endif(NOT ${UINT64_SIZE}  EQUAL 8)

check_type_size(int64_t INT64_SIZE)
if(NOT ${INT64_SIZE} EQUAL 8)
    message(FATAL_ERROR "int64_t size is not 8Byte!")
endif(NOT ${INT64_SIZE}  EQUAL 8)

check_type_size(float FLOAT32_SIZE)
if(NOT ${FLOAT32_SIZE} EQUAL 4)
    message(FATAL_ERROR "float size is not 4Byte!")
endif(NOT ${FLOAT32_SIZE}  EQUAL 4)

check_type_size(double FLOAT64_SIZE)
if(NOT ${FLOAT64_SIZE} EQUAL 8)
    message(FATAL_ERROR "double size is not 8Byte!")
endif(NOT ${FLOAT64_SIZE}  EQUAL 8)

check_type_size("long double" FLOAT128_SIZE)
if(NOT ${FLOAT128_SIZE} EQUAL 16)
    message(FATAL_ERROR "long double size is not 16Byte!")
endif(NOT ${FLOAT128_SIZE}  EQUAL 16)

#=================try to figure out some compiler capabilities=================
file(READ "bind_test.cpp" BIND_TEST_SOURCE)
check_cxx_source_compiles("${BIND_TEST_SOURCE}"  BIND_COMPILER_CHECK)
if(NOT BIND_COMPILER_CHECK)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNO_STD_BIND" )
endif(NOT BIND_COMPILER_CHECK)

file(READ "constexpr_test.cpp" CONST_EXPR_TEST_SOURCE)
check_cxx_source_compiles("${CONST_EXPR_TEST_SOURCE}" CONST_EXPR_TEST)
if(NOT CONST_EXPR_TEST)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOCEXPR")
endif(NOT CONST_EXPR_TEST)

file(READ "enum_bug_test.cpp" ENUM_BUG_TEST_SOURCE)
check_cxx_source_compiles("${ENUM_BUG_TEST_SOURCE}" ENUM_BUG_TEST)
if(NOT ENUM_BUG_TEST)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DENUMBUG")
endif(NOT ENUM_BUG_TEST)

file(READ "explicit_conversion_test.cpp" EXPLICIT_CONVERSION_TEST_SOURCE)
check_cxx_source_compiles("${EXPLICIT_CONVERSION_TEST_SOURCE}"
    EXPLICIT_CONVERSION_TEST)
if(NOT EXPLICIT_CONVERSION_TEST)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOEXPLICITCONV")
endif(NOT EXPLICIT_CONVERSION_TEST)

file(READ "foreach_test.cpp" FOREACH_TEST_SOURCE)
check_cxx_source_compiles("${FOREACH_TEST_SOURCE}" FOREACH_TEST)
if(NOT FOREACH_TEST)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOFOREACH")
endif(NOT FOREACH_TEST)

file(READ "lambda_function_test.cpp" LAMBDA_FUNCTION_TEST_SOURCE)
check_cxx_source_compiles("${LAMBDA_FUNCTION_TEST_SOURCE}" LAMBDA_FUNCTION_TEST)
if(NOT LAMBDA_FUNCTION_TEST)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNO_LAMBDA_FUNC")
endif(NOT LAMBDA_FUNCTION_TEST)

file(READ "nullptr_test.cpp" NULLPTR_TEST_SOURCE)
check_cxx_source_compiles("${NULLPTR_TEST_SOURCE}" NULLPTR_TEST)
if(NOT NULLPTR_TEST)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Dnullptr=NULL")
endif(NOT NULLPTR_TEST)

file(READ "random_test.cpp" RANDOM_TEST_SOURCE)
check_cxx_source_compiles("${RANDOM_TEST_SOURCE}" RANDOM_TEST)
if(NOT RANDOM_TEST)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOCPPRAND")
endif(NOT RANDOM_TEST)

file(READ "template_alias_test.cpp" TEMPLATE_ALIAS_TEST_SOURCE)
check_cxx_source_compiles("${TEMPLATE_ALIAS_TEST_SOURCE}" TEMPLATE_ALIAS_TEST)
if(NOT TEMPLATE_ALIAS_TEST)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOTMPALIAS")
endif(NOT TEMPLATE_ALIAS_TEST)

#==========================check for libraries=====================================
#the only thing we have to do here is to check for pnicore
pkg_search_module(PNIIO_BUILD REQUIRED pnicore)


include(CheckTypeSize)
include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(FindBoost)
include(FindPkgConfig)

if(NOT PKG_CONFIG_FOUND)
    message("Could not find pkg-config ... try without it!")
endif()

if("${CMAKE_FAMILY_VERSION}" EQUAL "2.6")
    find_library(HDF5_FOUND hdf5 ${HDF5_C_LIBRARY_DIRS})
    include_directories(${HDF5_INCLUDE_DIRS}) 
else()
    include(FindHDF5)
endif()
    
if(NOT HDF5_FOUND)
    message("HDF5 not found:")
    message(FATAL "Please set HDF5_C_INCLUDE_DIRS and HDF5_LIBRARY_DIRS manually!")
endif()
if(NOT CMAKE_BUILD_TYPE)
    message("No build type specified - default is RELEASE")
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

#setup for GNU CXX compiler
if(CMAKE_COMPILER_IS_GNUCXX)
    message("found GNU compiler ...")
    if(CMAKE_BUILD_TYPE MATCHES RELEASE)
        message("setup for release build ...")
        add_definitions(-O3)
    elseif(CMAKE_BUILD_TYPE MATCHES DEBUG)
        message("setup for debug build ...")
        add_definitions(-O0 -g)
    endif()
endif()

#=====================need to check compiler flags=============================
#check for supported c++11 flags

#store the original state of CMAKE_REQUIRED_FLAGS
set(CMAKE_REQUIRED_FLAGS_ORIG "${CMAKE_REQUIRED_FLAGS}")

set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS_ORIG} -std=c++11")
check_cxx_source_compiles("int main() { return 0; }" HAS_CXX11_FLAG)

set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS_ORIG} -std=c++0x")
check_cxx_source_compiles("int main() { return 0; }" HAS_CXX0X_FLAG)

if(HAS_CXX11_FLAG)
    add_definitions(-std=c++11)
    set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS_ORIG} -std=c++11")
else()
    if(HAS_CXX0X_FLAG)
        add_definitions(-std=c++0x)
        set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS_ORIG} -std=c++0x")
    else()
        message(FATAL_ERROR,"Compiler does not support C++11 compiler flag")
    endif()
endif()
                          

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
if((NOT ${FLOAT128_SIZE} EQUAL 16) AND (NOT ${FLOAT128_SIZE} EQUAL 12))
    message("Long Double is of size ${FLOAT128_SIZE}")
    message(FATAL_ERROR "long double size is not 16Byte or 12Byte!")
endif()

#=================try to figure out some compiler capabilities=================
file(READ "configure/bind_test.cpp" BIND_TEST_SOURCE)
check_cxx_source_compiles("${BIND_TEST_SOURCE}"  BIND_COMPILER_CHECK)
if(NOT BIND_COMPILER_CHECK)
    add_definitions(-DNO_STD_BIND)
endif()

file(READ "configure/constexpr_test.cpp" CONST_EXPR_TEST_SOURCE)
check_cxx_source_compiles("${CONST_EXPR_TEST_SOURCE}" CONST_EXPR_TEST)
if(NOT CONST_EXPR_TEST)
    add_definitions(-DNOCEXPR)
endif()

file(READ "configure/enum_bug_test.cpp" ENUM_BUG_TEST_SOURCE)
check_cxx_source_compiles("${ENUM_BUG_TEST_SOURCE}" ENUM_BUG_TEST)
if(NOT ENUM_BUG_TEST)
    add_definitions(-DENUMBUG)
endif()

file(READ "configure/explicit_conversion_test.cpp" EXPLICIT_CONVERSION_TEST_SOURCE)
check_cxx_source_compiles("${EXPLICIT_CONVERSION_TEST_SOURCE}"
    EXPLICIT_CONVERSION_TEST)
if(NOT EXPLICIT_CONVERSION_TEST)
    add_definitions(-DNOEXPLICITCONV)
endif()

file(READ "configure/foreach_test.cpp" FOREACH_TEST_SOURCE)
check_cxx_source_compiles("${FOREACH_TEST_SOURCE}" FOREACH_TEST)
if(NOT FOREACH_TEST)
    add_definitions(-DNOFOREACH)
endif()

file(READ "configure/lambda_function_test.cpp" LAMBDA_FUNCTION_TEST_SOURCE)
check_cxx_source_compiles("${LAMBDA_FUNCTION_TEST_SOURCE}" LAMBDA_FUNCTION_TEST)
if(NOT LAMBDA_FUNCTION_TEST)
    add_definitions(-DNO_LAMBDA_FUNC)
endif()

file(READ "configure/nullptr_test.cpp" NULLPTR_TEST_SOURCE)
check_cxx_source_compiles("${NULLPTR_TEST_SOURCE}" NULLPTR_TEST)
if(NOT NULLPTR_TEST)
    add_definitions(-Dnullptr=NULL)
endif()

file(READ "configure/random_test.cpp" RANDOM_TEST_SOURCE)
check_cxx_source_compiles("${RANDOM_TEST_SOURCE}" RANDOM_TEST)
if(NOT RANDOM_TEST)
    add_definitions(-DNOCPPRAND)
endif()

file(READ "configure/template_alias_test.cpp" TEMPLATE_ALIAS_TEST_SOURCE)
check_cxx_source_compiles("${TEMPLATE_ALIAS_TEST_SOURCE}" TEMPLATE_ALIAS_TEST)
if(NOT TEMPLATE_ALIAS_TEST)
    add_definitions(-DNOTMPALIAS)
endif()

#==========================check for libraries=====================================
#the only thing we have to do here is to check for pnicore
pkg_search_module(PNICORE_PKG REQUIRED pnicore)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.41 COMPONENTS program_options system regex)

if(PKG_CONFIG_FOUND)
    pkg_search_module(CPPUNIT REQUIRED cppunit)
endif()



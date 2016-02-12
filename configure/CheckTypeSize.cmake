include(CheckTypeSize)

#------------------------------------------------------------------------------
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
if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    if(NOT ${FLOAT128_SIZE} EQUAL 8)
        message(FATAL_ERROR "Long double size is not 8 Byte on Windows")
    endif()
else()
    if((NOT ${FLOAT128_SIZE} EQUAL 16) AND (NOT ${FLOAT128_SIZE} EQUAL 12))
        message("Long Double is of size ${FLOAT128_SIZE}")
        message(FATAL_ERROR "long double size is not 16Byte or 12Byte!")
    endif()
endif()

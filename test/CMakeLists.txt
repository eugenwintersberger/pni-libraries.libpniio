
#need to define the version of the library

include(${PROJECT_SOURCE_DIR}/cmake/common/BoostTestConfig.cmake)

link_directories(${PNICORE_PKG_LIBRARY_DIRS} ${HDF5_LIBRARY_DIRS})
include_directories(${pnicore_INCLUDE_DIRS} ${hdf5_INCLUDE_DIRS})

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

set(COMMON_SRC base_fixture.cpp)
add_library(test_common OBJECT ${COMMON_SRC})



add_executable(environment_test environment_test.cpp)
add_test(NAME "Environment:test"
         COMMAND environment_test
         WOWRKING_DIRECTORY ${PROJECT_BINARY_DIR}/test)



add_executable(parser_complex_test parser_complex_test.cpp)
target_link_libraries(parser_complex_test pniio)


add_subdirectory(xml_test)
add_subdirectory(hdf5_imp_test)
add_subdirectory(nexus_lowlevel_test)
add_subdirectory(parser_test)
add_subdirectory(algorithm_test)
add_subdirectory(reader_test)
add_subdirectory(nxpath_test)
add_subdirectory(formatter_test)
add_subdirectory(logs)
#add_subdirectory(benchmarks)

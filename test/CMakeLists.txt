
#need to define the version of the library

include(${PROJECT_SOURCE_DIR}/cmake/common/BoostTestConfig.cmake)

link_directories(${PNICORE_PKG_LIBRARY_DIRS} ${HDF5_LIBRARY_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)

set(COMMON_SRC base_fixture.cpp)
add_library(test_common EXCLUDE_FROM_ALL OBJECT ${COMMON_SRC})



add_executable(environment_test EXCLUDE_FROM_ALL environment_test.cpp)
#add_test(NAME "Environment:test"
#         COMMAND environment_test
#         WOWRKING_DIRECTORY ${PROJECT_BINARY_DIR}/test)



add_executable(parser_complex_test EXCLUDE_FROM_ALL parser_complex_test.cpp)
target_link_libraries(parser_complex_test pniio)


add_subdirectory(parser_test)
add_subdirectory(reader_test)
add_subdirectory(formatter_test)
add_subdirectory(logs)
add_subdirectory(nexus)
add_subdirectory(regressions)
#add_subdirectory(benchmarks)

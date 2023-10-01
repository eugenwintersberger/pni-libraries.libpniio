
#need to define the version of the library
find_package(h5cpp REQUIRED)
get_target_property(H5CPP_INCLUDE_DIRS h5cpp::h5cpp INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${PROJECT_SOURCE_DIR}/src ${HDF5_INCLUDE_DIRS} ${H5CPP_INCLUDE_DIRS})

include(${PROJECT_SOURCE_DIR}/cmake/BoostTestConfig.cmake)

link_directories(${PNICORE_PKG_LIBRARY_DIRS} ${HDF5_LIBRARY_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)


# set(COMMON_SRC base_fixture.cpp)
set(COMMON_SRC base_fixture.cpp compare.cpp data_generator.cpp)
add_library(test_common EXCLUDE_FROM_ALL OBJECT ${COMMON_SRC})
target_include_directories(test_common PRIVATE ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)



add_executable(parser_complex_test EXCLUDE_FROM_ALL parser_complex_test.cpp)
target_link_libraries(parser_complex_test pninexus h5cpp::h5cpp)

#
# build test program for the random number generator
#
# add_executable(rand_test EXCLUDE_FROM_ALL "rand_test.cpp" $<TARGET_OBJECTS:test_common>)
# target_link_libraries(rand_test PRIVATE pninexus h5cpp::h5cpp)

#
# build random number generator
#
# add_executable(rand_gen EXCLUDE_FROM_ALL rand_gen.cpp)
# target_link_libraries(rand_gen pninexus h5cpp::h5cpp)

#
# build the environment test program
#

# add_executable(environment_test EXCLUDE_FROM_ALL environment_test.cpp)
# add_test(NAME "Environment:test"
#          COMMAND environment_test
#          WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test)
# add_dependencies(check test_common 
#                        rand_test 
#                        rand_gen 
#                        environment_test)

# add_subdirectory(parser_test)
# add_subdirectory(reader_test)
# add_subdirectory(formatter_test)
# add_subdirectory(logs)
add_subdirectory(nexus)
# add_subdirectory(regressions)
#add_subdirectory(benchmarks)
# add_subdirectory(index_maps)
# add_subdirectory(types)
# add_subdirectory(arrays)

# add_subdirectory(utils_test)
# add_subdirectory(type_erasures)
# add_subdirectory(config)
# add_subdirectory(math)
# add_subdirectory(error)
# add_subdirectory(exceptions)

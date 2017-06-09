
#need to define the version of the library

link_directories(${PNICORE_PKG_LIBRARY_DIRS} ${HDF5_LIBRARY_DIRS})
include_directories(${pnicore_INCLUDE_DIRS} ${hdf5_INCLUDE_DIRS})

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

set(COMMON_SRC base_fixture.cpp)
add_library(test_common OBJECT ${COMMON_SRC})

macro(set_shared_test_defs source_list mod_description)
    list(GET ${source_list} 0 FIRST_SOURCE_FILE)
    message(STATUS "First source file is ${FIRST_SOURCE_FILE}")
    set_source_files_properties(${FIRST_SOURCE_FILE} PROPERTIES
                                COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=${mod_description}")
endmacro()

#
# need to setup the PATH environment on Windows - this is important 
# otherwise the tests will not run since they would not be able to find teh 
# appropriate libraries
#
if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    get_filename_component(Boost_ROOT_PATH ${Boost_LIBRARY_DIRS} DIRECTORY)
    get_filename_component(HDF5_ROOT_PATH ${HDF5_LIBRARY_DIRS} DIRECTORY)

    set(PATH_STRING
        "$ENV{PATH};$<TARGET_FILE_DIR:pniio>;${HDF5_ROOT_PATH}/bin;${Boost_ROOT_PATH}/bin;${Boost_ROOT_PATH}/lib;$<TARGET_FILE_DIR:pnicore_shared>;${ZLIB_ROOT_PATH}/../bin")
    string(REPLACE ";" "\\;" PATH_STRING "${PATH_STRING}")
endif()

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    message(STATUS "Set PATH in the test environments to: ${PATH_STRING}")
endif()

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)

    add_executable(environment_test environment_test.cpp)
    add_test(NAME "Environment:test"
             COMMAND environment_test
             WOWRKING_DIRECTORY ${PROJECT_BINARY_DIR}/test)
    set_property(TEST "Environment:test" APPEND PROPERTY
        ENVIRONMENT "PATH=${PATH_STRING}")
endif()

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
#add_subdirectory(benchmarks)

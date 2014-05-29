
#need to define the version of the library
set(TEST_SOURCES 
    ./data.cpp
    ./TestHelpers.cpp
    ./pniiotest.cpp
    ./EqualityCheck.cpp
)

set(COMMON_SRC EqualityCheck.cpp data.cpp TestHelpers.cpp)
add_library(test_common OBJECT ${COMMON_SRC})

link_directories(${PNICORE_PKG_LIBRARY_DIRS} ${HDF5_LIBRARY_DIRS})
include_directories(${PNICORE_PKG_INCLUDE_DIRS} ${HDF5_INCLUDE_DIRS})
link_directories("${CMAKE_CURRENT_BINARY_DIR}/../src")
include_directories(${PNICORE_PKG_INCLUDE_DIRS})
add_executable(pniiotest ${TEST_SOURCES})

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

    #add libraries
    target_link_libraries(pniiotest ${CPPUNIT_LIBRARIES})

endif()

target_link_libraries(pniiotest pniio dl)

add_subdirectory(xml_test)
add_subdirectory(utils_test)
add_subdirectory(hdf5_imp_test)
add_subdirectory(nexus_lowlevel_test)
add_subdirectory(parser_test)
add_subdirectory(algorithm_test)


add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/reader_tests/iui8.tiff ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/reader_tests/ii8.tiff ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET pniiotest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/reader_tests/ii32.tiff ${CMAKE_CURRENT_BINARY_DIR})


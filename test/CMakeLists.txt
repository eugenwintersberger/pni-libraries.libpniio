
#need to define the version of the library
set(COMMON_SRC EqualityCheck.cpp data.cpp TestHelpers.cpp)
add_library(test_common OBJECT ${COMMON_SRC})

link_directories(${PNICORE_PKG_LIBRARY_DIRS} ${HDF5_LIBRARY_DIRS})
include_directories(${PNICORE_PKG_INCLUDE_DIRS} ${HDF5_INCLUDE_DIRS})
link_directories("${CMAKE_CURRENT_BINARY_DIR}/../src")
include_directories(${PNICORE_PKG_INCLUDE_DIRS})

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

endif()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

add_subdirectory(xml_test)
add_subdirectory(hdf5_imp_test)
#add_subdirectory(nexus_lowlevel_test)
#add_subdirectory(parser_test)
#add_subdirectory(algorithm_test)
#add_subdirectory(reader_test)
add_subdirectory(nxpath_test)
add_subdirectory(formatter_test)


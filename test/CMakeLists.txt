
#need to define the version of the library
file(GLOB_RECURSE TEST_SOURCES *.cpp)

link_directories(${PNICORE_PKG_LIBRARY_DIRS} ${HDF5_LIBRARY_DIRS})
include_directories(${PNICORE_PKG_INCLUDE_DIRS} ${HDF5_INCLUDE_DIRS})
link_directories("${CMAKE_CURRENT_BINARY_DIR}/../src")
include_directories(${PNICORE_PKG_INCLUDE_DIRS})
add_executable(pniiotest ${TEST_SOURCES})
target_link_libraries(pniiotest pniio ${CPPUNIT_PKG_LIBRARIES})


set(SOURCES H5AttributeObjectTest.cpp
            H5AttributeTest.cpp
            H5DatasetTest.cpp
            H5DataspaceTest.cpp
            H5DatatypeTest.cpp
            H5FileTest.cpp
            H5GroupTest.cpp
            H5LinkTest.cpp
            H5NamedObjectTest.cpp
            H5ObjectTest.cpp
            hdf5_imp_test.cpp
            h5object_test.cpp
           )

add_executable(hdf5_imp_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(hdf5_imp_test pniio ${CPPUNIT_LIBRARIES})
add_test(hdf5_imp_test hdf5_imp_test)


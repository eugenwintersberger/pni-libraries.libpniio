set(SOURCES 
            #H5AttributeObjectTest.cpp
            #H5DatasetTest.cpp
            #H5DataspaceTest.cpp
            #H5DatatypeTest.cpp
            #H5GroupTest.cpp
            #H5LinkTest.cpp
            #H5NamedObjectTest.cpp
            #H5ObjectTest.cpp
            hdf5_imp_test.cpp
            h5datatype_test.cpp
            h5dataspace_test.cpp
            object_imp_test.cpp
            file_imp_test.cpp
            group_imp_test.cpp
            attribute_imp_test.cpp
            file_imp_test.cpp
            field_imp_test.cpp
           )

add_executable(hdf5_imp_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(hdf5_imp_test pniio ${CPPUNIT_LIBRARIES})
add_test(hdf5_imp_test hdf5_imp_test)


set(SOURCES 
            h5link_test.cpp
            hdf5_imp_test.cpp
            h5datatype_test.cpp
            h5dataspace_test.cpp
            object_imp_test.cpp
            file_imp_test.cpp
            group_imp_test.cpp
            attribute_imp_test.cpp
            file_imp_test.cpp
            field_imp_test.cpp
            h5object_types_test.cpp
            hdf5_utilities_test.cpp
            attribute_utils_test.cpp
           )

add_executable(hdf5_imp_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(hdf5_imp_test pniio ${CPPUNIT_LIBRARIES})
add_test(NAME "HDF5:implementation-test" 
         COMMAND hdf5_imp_test)


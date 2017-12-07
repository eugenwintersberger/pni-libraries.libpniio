set(SOURCES h5link_test.cpp
            h5_imp_test_utils.cpp
            h5datatype_test.cpp
            h5dataspace_test.cpp
            object_imp_test.cpp
            file_imp_test.cpp
            group_imp_test.cpp
            attribute_imp_test.cpp
            field_imp_test.cpp
            h5object_types_test.cpp
            hdf5_utilities_test.cpp
            attribute_utils_test.cpp
           )

set_boost_test_definitions(SOURCES "testing HDF5 implementation")
add_executable(hdf5_imp_test EXCLUDE_FROM_ALL ${SOURCES} )
target_link_libraries(hdf5_imp_test pniio Boost::unit_test_framework)
add_boost_logging_test("HDF5:implementation-test"
                       hdf5_imp_test
                       ${PROJECT_BINARY_DIR}/test/hdf5_imp_test)

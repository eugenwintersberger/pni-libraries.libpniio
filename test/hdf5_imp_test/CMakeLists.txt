set(SOURCES h5_imp_test_utils.cpp
            h5link_test.cpp
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


set_source_files_properties(h5link_test.cpp PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; 
                            BOOST_TEST_MODULE=testing HDF5 implementation")

add_executable(hdf5_imp_test EXCLUDE_FROM_ALL ${SOURCES} )
target_link_libraries(hdf5_imp_test pniio ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME "HDF5:implementation-test" 
         COMMAND hdf5_imp_test)

add_dependencies(check hdf5_imp_test)


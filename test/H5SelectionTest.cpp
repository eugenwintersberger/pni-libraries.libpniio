//implementation of H5Selection tests

#include "H5SelectionTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5SelectionTest);

//-----------------------------------------------------------------------------
void H5SelectionTest::setUp(){
    _shape.rank(3);
    _shape.dim(0,0); 
    _shape.dim(1,12); 
    _shape.dim(2,57);

    _chunk = Shape(_shape);
    _chunk.dim(0,1);

    _file.create("H5SelectionTest.h5",true,0);
    _dset = H5Dataset("array",_file,TypeID::FLOAT32,_shape,_chunk);
}

//-----------------------------------------------------------------------------
void H5SelectionTest::tearDown(){
    _dset.close();
    _file.close();
}

//-----------------------------------------------------------------------------
void H5SelectionTest::test_creation(){
    std::cout<<"H5SelectionTest::test_creation-------------------------------";
    std::cout<<std::endl;

    H5Selection s1 = _dset.selection();
    CPPUNIT_ASSERT(s1.shape() == _shape);

    
    //using copy constructor
    H5Selection s2 = s1;
    CPPUNIT_ASSERT(s2.shape() == s1.shape());

    //using move constructor
    H5Selection s3 = std::move(s1);
    CPPUNIT_ASSERT(s3.shape() == s2.shape());
    CPPUNIT_ASSERT(s3.shape() != s1.shape());

}

//-----------------------------------------------------------------------------
void H5SelectionTest::test_assignment(){
    std::cout<<"H5SelectionTest::test_assignment-----------------------------";
    std::cout<<std::endl;

    H5Selection s1 = _dset.selection();
    H5Selection s2 = _dset.selection();

    s1.offset(0,1);
    
    CPPUNIT_ASSERT(s2.offset() != s1.offset());

    //copy assignment
    s2 = s1;
    CPPUNIT_ASSERT(s2.offset() == s1.offset());

    //move assignment
    H5Selection s3 = _dset.selection();
    s3 = std::move(s1);
    CPPUNIT_ASSERT(s3.shape() == s2.shape());
    CPPUNIT_ASSERT(s3.shape() != s1.shape());

}

//-----------------------------------------------------------------------------
void H5SelectionTest::test_setup(){
    std::cout<<"H5SelectionTest::test_setup-----------------------------------";
    std::cout<<std::endl;
    
    H5Selection s1 = _dset.selection();

    CPPUNIT_ASSERT(s1.offset(0) == 0);
    CPPUNIT_ASSERT(s1.stride(0) == 1);

    s1.offset(1)=5;
    CPPUNIT_ASSERT(s1.offset(1) == 5);
    s1.stride(2)=10;
    CPPUNIT_ASSERT(s1.stride(2) == 10);


}

//-----------------------------------------------------------------------------
void H5SelectionTest::test_write_simple_types(){
    std::cout<<"void H5SelectionTest::test_write_simple_types()-----------------";
    std::cout<<std::endl;

    //start with a scalar dataset
    Shape s(1);
    Shape cs(1); cs.dim(0,1);
    H5Dataset array_ds("array_dataset",_file,TypeID::FLOAT32,s,cs);
    array_ds.extend(0);

    H5Selection selection = array_ds.selection();
    selection.count(0,1);
    selection.offset(0,0);
    double value = 1;
    CPPUNIT_ASSERT_NO_THROW(selection.write(value));
    array_ds.extend(0);
    selection.offset(0,1);
    value = 2;
    CPPUNIT_ASSERT_NO_THROW(selection.write(value));
    CPPUNIT_ASSERT(array_ds.rank() == 1);
    CPPUNIT_ASSERT(array_ds.size() == 2);


    //extensible string dataset
    String str="hello";
    H5Dataset string_ds("string_ds",_file,TypeID::STRING,s,cs);

    CPPUNIT_ASSERT_NO_THROW(string_ds.extend(0));

    selection = string_ds.selection();
    selection.offset(0,0); 
    selection.count(0,1);
    CPPUNIT_ASSERT_NO_THROW(selection.write(str));

    CPPUNIT_ASSERT_NO_THROW(string_ds.extend(0));
    selection.offset(0,1);
    str = "this is a text";
//    std::cout<<string_ds.shape()<<std::endl;
//    std::cout<<selection.shape()<<std::endl;
//    std::cout<<string_ds.space().rank()<<std::endl;
//    std::cout<<string_ds.space().size()<<std::endl;
    CPPUNIT_ASSERT_NO_THROW(selection.write(str));

}

//-----------------------------------------------------------------------------
void H5SelectionTest::test_read_simple_types(){
    std::cout<<"void H5SelectionTest::test_read_simple_types()-----------------";
    std::cout<<std::endl;
    double value = 1.2;
    double read = 0.;

    //----------write data with selection--------------------------
    Shape s(1);
    Shape cs(1); cs.dim(0,1);
    H5Dataset array_ds("array_dataset",_file,TypeID::FLOAT32,s,cs);
    H5Selection selection = array_ds.selection();
    selection.offset(0,0); selection.count(0,1);
    array_ds.extend(0);
    CPPUNIT_ASSERT_NO_THROW(selection.write(value));

    array_ds.extend(0);
    selection.offset(0,1);
    value = 2.3;
    CPPUNIT_ASSERT_NO_THROW(selection.write(value));
   
    array_ds.extend(0);
    selection.offset(0,2);
    value = -9.234;
    CPPUNIT_ASSERT_NO_THROW(selection.write(value));
    
    H5Dataset array_ds2("array_dataset2",_file,TypeID::FLOAT32,s,cs);
    selection = array_ds2.selection();
    selection.offset(0,0); 
    selection.count(0,1);
    array_ds2.extend(0);
    CPPUNIT_ASSERT_NO_THROW(selection.write(value));

    array_ds2.extend(0);
    selection.offset(0,1);
    value = 2.3;
    CPPUNIT_ASSERT_NO_THROW(selection.write(value));
   
    array_ds2.extend(0);
    selection.offset(0,2);
    value = -9.234;
    CPPUNIT_ASSERT_NO_THROW(selection.write(value));


    //----------read back data with selection-----------------------
    selection.offset(0,0);
    CPPUNIT_ASSERT_NO_THROW(selection.read(read));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(read,1.2,1.e-6);
    selection.offset(0,1);
    CPPUNIT_ASSERT_NO_THROW(selection.read(read));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(read,2.3,1.e-6);
    selection.offset(0,2);
    CPPUNIT_ASSERT_NO_THROW(selection.read(read));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(read,-9.234,1.e-5);


    //extensible string dataset
    String str="hello";
    s.dim(0,0);
    H5Dataset string_ds("string_ds",_file,TypeID::STRING,s,cs);
    selection = string_ds.selection();
    string_ds.extend(0);
    selection.offset(0,0);
    selection.count(0,1);
    CPPUNIT_ASSERT_NO_THROW(selection.write(str));
    string_ds.extend(0);
    selection.offset(0,1);
    str = "this is a text";
    CPPUNIT_ASSERT_NO_THROW(selection.write(str));

}
//-----------------------------------------------------------------------------
void H5SelectionTest::test_write_scalar(){
    std::cout<<"void H5SelectionTest::test_write_scalar()-----------------------";
    std::cout<<std::endl;
    Float32Scalar s(1,"scalar","au","test scalar");

    Shape sh(1); sh.dim(0,0);
    Shape cs(1); cs.dim(0,1);
    H5Dataset array_ds("array_ds",_file,s.type_id(),sh,cs);
    array_ds.extend(0);
    H5Selection selection = array_ds.selection();
    selection.offset(0,0); 
    selection.count(0,1);
    CPPUNIT_ASSERT_NO_THROW(selection.write(s));
    s = -0.2334;
    selection.offset(0,1);
    array_ds.extend(0);
    CPPUNIT_ASSERT_NO_THROW(selection.write(s));

    H5Dataset array_ds2("array_ds2",_file,s.type_id(),sh,cs);
    s = 1;
    selection = array_ds2.selection();
    array_ds2.extend(0);
    selection.offset(0,0); 
    selection.count(0,1);
    CPPUNIT_ASSERT_NO_THROW(selection.write(s));
    s = -0.2334;
    selection.offset(0,1);
    array_ds.extend(0);
    CPPUNIT_ASSERT_NO_THROW(selection.write(s));


}

//-----------------------------------------------------------------------------
void H5SelectionTest::test_write_array(){
    std::cout<<"void H5SelectionTest::test_write_array()-----------------------";
    std::cout<<std::endl;

    Shape s(2); s.dim(0,3); s.dim(1,5);
    UInt32Array a(s,"det","cps","useless data");
    a = 24;


    Shape cs(3); cs.dim(0,1); cs.dim(1,s[0]); cs.dim(2,s[1]);
    Shape ds(3); ds.dim(0,0); ds.dim(1,s[0]); ds.dim(2,s[1]);
    H5Dataset earray_ds("earray_2",_file,a.type_id(),ds,cs);
    H5Selection selection = earray_ds.selection(); 
    earray_ds.extend(0);
    CPPUNIT_ASSERT_NO_THROW(selection.write(a));
    a = 100;
    earray_ds.extend(0);
    selection.offset(0,1);
    CPPUNIT_ASSERT_NO_THROW(selection.write(a));
}

//-----------------------------------------------------------------------------
void H5SelectionTest::test_write_buffer(){
    std::cout<<"void H5SelectionTest::test_write_buffer()----------------------";
    std::cout<<std::endl;

    Buffer<Binary> buffer(128);
    Shape s(1); s.dim(0,128); 

    Shape cs(1); cs.dim(0,buffer.size());
    s.dim(0,0);
    H5Dataset ebin_ds("binary_2",_file,TypeID::BINARY,s,cs);
    H5Selection selection = ebin_ds.selection();
    ebin_ds.extend(0,1024);
    selection.count(0,1024);
    buffer = 100;
    CPPUNIT_ASSERT_NO_THROW(selection.write(buffer));
    ebin_ds.extend(0,1024);
    selection.offset(0,1024);
    buffer = 200;
    CPPUNIT_ASSERT_NO_THROW(selection.write(buffer));
}

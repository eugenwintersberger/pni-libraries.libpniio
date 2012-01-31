#include "H5DatasetTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(H5DatasetTest);


void H5DatasetTest::setUp(){
    _file.create("H5DatasetTest.h5",true,0);
    _group =H5Group("data",_file);
}

//-----------------------------------------------------------------------------
void H5DatasetTest::tearDown(){
    _group.close();
    _file.close();
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_creation(){
    std::cout<<"void H5DatasetTest::test_creation()---------------------------";
    std::cout<<std::endl;
    Shape s(2);
    s.dim(0,10);
    s.dim(1,50);

    //create contiguous dataset
    H5Dataset ds1("ds1",_group,TypeID::FLOAT32,s);
    CPPUNIT_ASSERT(ds1.is_valid());
    CPPUNIT_ASSERT(ds1.type_id()==TypeID::FLOAT32);

    //create a chunked dataset
    Shape cs(2);
    cs.dim(0,1);
    cs.dim(1,50);
    H5Dataset ds2("ds2",_group,TypeID::UINT32,s,cs);
    CPPUNIT_ASSERT(ds2.is_valid());
    CPPUNIT_ASSERT(ds2.type_id() == TypeID::UINT32);

    //create a scalar dataset
    H5Dataset ds3("ds3",_group,TypeID::FLOAT128);
    CPPUNIT_ASSERT(ds3.is_valid());
    CPPUNIT_ASSERT(ds3.type_id() == TypeID::FLOAT128);

    //test copy constructor
    H5Dataset ds4 = ds2;
    CPPUNIT_ASSERT(ds4.is_valid());
    CPPUNIT_ASSERT(ds2.is_valid());
    CPPUNIT_ASSERT(ds4.type_id() == ds2.type_id());

    //test move constructor
    H5Dataset ds5 = std::move(ds4);
    CPPUNIT_ASSERT(ds5.is_valid());
    CPPUNIT_ASSERT(!ds4.is_valid());
    CPPUNIT_ASSERT(ds5.type_id() == ds2.type_id());
    
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_assignment(){
    std::cout<<"void H5DatasetTest::test_assignment()-------------------------";
    std::cout<<std::endl;
    
    Shape s(2);
    s.dim(0,1024);
    s.dim(1,512);
    H5Dataset ds("ds",_group,TypeID::FLOAT32,s);

    H5Dataset ds1;

    //testing copy assignment
    CPPUNIT_ASSERT_NO_THROW(ds1 = ds);
    CPPUNIT_ASSERT(ds1.is_valid());
    CPPUNIT_ASSERT(ds.is_valid());
    
    //testing move assignment
    H5Dataset ds2;
    CPPUNIT_ASSERT_NO_THROW(ds2 = std::move(ds1));
    CPPUNIT_ASSERT(ds2.is_valid());
    CPPUNIT_ASSERT(!ds1.is_valid());


}

//----------------------------------------------------------------------------
void H5DatasetTest::test_inquery(){
    std::cout<<"void H5DatasetTest::test_inquery()----------------------------";
    std::cout<<std::endl;

    Shape s(2);
    s.dim(0,1024); s.dim(1,512);
    H5Dataset ds("ds",_file,TypeID::FLOAT128,s);

    CPPUNIT_ASSERT(ds.is_valid());
    CPPUNIT_ASSERT(ds.type_id() == TypeID::FLOAT128);
    CPPUNIT_ASSERT(ds.shape() == s);

}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_resize(){
    std::cout<<"void H5DatasetTest::test_resize()-----------------------------";
    std::cout<<std::endl;

    //create base shape
    Shape s(2);
    s.dim(0,0); s.dim(1,1024);
    Shape cs(2);
    cs.dim(0,1); cs.dim(1,1024);

    H5Dataset ds("ds",_group,TypeID::UINT32,s,cs);

    CPPUNIT_ASSERT_NO_THROW(ds.extend(0));
    s.dim(0,1);
    CPPUNIT_ASSERT(ds.shape() == s);
    s.dim(0,4);
    CPPUNIT_ASSERT_NO_THROW(ds.extend(0,3));
    CPPUNIT_ASSERT(ds.shape() == s);

    //reshape the dataset
    Shape ns(2);
    ns.dim(0,100);ns.dim(1,512);
    ds.resize(ns);
    CPPUNIT_ASSERT(ds.shape() == ns);
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_write_simple_types(){
    std::cout<<"void H5DatasetTest::test_write_simple_types()-----------------";
    std::cout<<std::endl;

    //start with a scalar dataset
    H5Dataset scalar_ds("scalar_dataset",_group,TypeID::FLOAT32);
    double value =1.23;
    CPPUNIT_ASSERT_NO_THROW(scalar_ds.write(value));

    Shape s(1);
    Shape cs(1); cs.dim(0,1);
    H5Dataset array_ds("array_dataset",_group,TypeID::FLOAT32,s,cs);

    s.dim(0,1);
    CPPUNIT_ASSERT_NO_THROW(array_ds.resize(s));
    H5Selection selection(cs);
    CPPUNIT_ASSERT_NO_THROW(array_ds.write(selection,value));
    s.dim(0,2);
    CPPUNIT_ASSERT_NO_THROW(array_ds.resize(s));
    selection.offset(0,1);
    value = -9.234;
    CPPUNIT_ASSERT_NO_THROW(array_ds.write(selection,value));
    CPPUNIT_ASSERT_NO_THROW(array_ds.extend(0,1));
    value = 100.23;
    selection.offset(0,2);
    CPPUNIT_ASSERT_NO_THROW(array_ds.write(selection,value));


    //extensible string dataset
    String str="hello";
    s.dim(0,0);
    H5Dataset string_ds("string_ds",_group,TypeID::STRING,s,cs);
    string_ds.extend(0);
    selection.offset(0,0);
    CPPUNIT_ASSERT_NO_THROW(string_ds.write(selection,str));
    string_ds.extend(0);
    selection.offset(0,1);
    str = "this is a text";
    CPPUNIT_ASSERT_NO_THROW(string_ds.write(selection,str));

    //try a scalar string field
    H5Dataset sstring_ds("scalar_string_ds",_group,TypeID::STRING);
    CPPUNIT_ASSERT_NO_THROW(sstring_ds.write(str));
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_write_scalar(){
    std::cout<<"void H5DatasetTest::test_write_scalar()-----------------------";
    std::cout<<std::endl;

    Float32Scalar s(100.233,"scdata","a.u.","a simple scalar value");
    H5Dataset scalar_ds("scalar_ds",_group,s.type_id());
    CPPUNIT_ASSERT_NO_THROW(scalar_ds.write(s));

    Shape sh(1); sh.dim(0,0);
    Shape cs(1); cs.dim(0,1);
    H5Dataset array_ds("array_ds",_group,s.type_id(),sh,cs);
    array_ds.extend(0);
    H5Selection selection(cs);
    CPPUNIT_ASSERT_NO_THROW(array_ds.write(selection,s));
    s = -0.2334;
    selection.offset(0,1);
    array_ds.extend(0);
    CPPUNIT_ASSERT_NO_THROW(array_ds.write(selection,s));

}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_write_array(){
    std::cout<<"void H5DatasetTest::test_write_array()-----------------------";
    std::cout<<std::endl;

    Shape s(2); s.dim(0,3); s.dim(1,5);
    UInt32Array a(s,"det","cps","useless data");
    a = 24;

    H5Dataset array_ds("array_1",_group,a.type_id(),s);
    CPPUNIT_ASSERT_NO_THROW(array_ds.write(a));

    Shape cs(3); cs.dim(0,1); cs.dim(1,s[0]); cs.dim(2,s[1]);
    Shape ds(3); ds.dim(0,0); ds.dim(1,s[0]); ds.dim(2,s[1]);
    H5Dataset earray_ds("earray_2",_group,a.type_id(),ds,cs);
    H5Selection selection(cs); 
    earray_ds.extend(0);
    CPPUNIT_ASSERT_NO_THROW(earray_ds.write(selection,a));
    a = 100;
    earray_ds.extend(0);
    selection.offset(0,1);
    CPPUNIT_ASSERT_NO_THROW(earray_ds.write(selection,a));
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_write_buffer(){
    std::cout<<"void H5DatasetTest::test_write_buffer()----------------------";
    std::cout<<std::endl;

    Buffer<Binary> buffer(128);
    Shape s(1); s.dim(0,128); 
    H5Dataset bin_ds("binary_1",_group,TypeID::BINARY,s);
    CPPUNIT_ASSERT_NO_THROW(bin_ds.write(buffer));

    Shape cs(1); cs.dim(0,buffer.size());
    s.dim(0,0);
    H5Dataset ebin_ds("binary_2",_group,buffer.type_id(),s,cs);
    


}


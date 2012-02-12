#include "H5DatasetTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(H5DatasetTest);


void H5DatasetTest::setUp(){
    _file = H5File::create_file("H5DatasetTest.h5",true,0);
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
    H5Dataspace space = {10,50};
    H5Datatype type   = H5DatatypeFactory::create_type<TypeID::FLOAT32>();

    //create contiguous dataset
    H5Dataset ds1("ds1",_group,type,space);
    CPPUNIT_ASSERT(ds1.is_valid());
    CPPUNIT_ASSERT(ds1.type_id()==TypeID::FLOAT32);

    //create a chunked dataset
    Shape cs(2);
    cs.dim(0,1);
    cs.dim(1,50);
    type = H5DatatypeFactory::create_type<TypeID::UINT32>();
    H5Dataset ds2("ds2",_group,type,space,cs);
    CPPUNIT_ASSERT(ds2.is_valid());
    CPPUNIT_ASSERT(ds2.type_id() == TypeID::UINT32);

    //create a scalar dataset
    type = H5DatatypeFactory::create_type<TypeID::FLOAT128>();
    H5Dataset ds3("ds3",_group,type);
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
    H5Datatype type = H5DatatypeFactory::create_type<TypeID::FLOAT32>();
    H5Dataspace space = {1024,512};
    H5Dataset ds("ds",_group,type,space);

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
    H5Datatype type = H5DatatypeFactory::create_type<Float128>();
    H5Dataspace space = {1024,512};
    H5Dataset ds("ds",_file,type,space);

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
    H5Datatype type = H5DatatypeFactory::create_type<UInt32>();
    H5Dataspace space({0,1024},{H5Dataspace::UNLIMITED,H5Dataspace::UNLIMITED});

    H5Dataset ds("ds",_group,type,space,cs);

    CPPUNIT_ASSERT_NO_THROW(ds.extend(0));
    s.dim(0,1);
    CPPUNIT_ASSERT(ds.rank()  == s.rank());
    CPPUNIT_ASSERT(ds.shape() == s);
    s.dim(0,4);
    CPPUNIT_ASSERT_NO_THROW(ds.extend(0,3));
    CPPUNIT_ASSERT(ds.rank()  == s.rank());
    CPPUNIT_ASSERT(ds.shape() == s);

    s.rank(1); s.dim(0,0);
    cs.rank(1); cs.dim(0,1);
    type = H5DatatypeFactory::create_type<String>();
    CPPUNIT_ASSERT_NO_THROW(space = H5Dataspace({0},{H5Dataspace::UNLIMITED}));
    H5Dataset ss("ss",_group,type,space,cs);
    CPPUNIT_ASSERT(ss.rank() == 1);
    CPPUNIT_ASSERT(ss.size() == 0);
    CPPUNIT_ASSERT_NO_THROW(ss.extend(0));
    CPPUNIT_ASSERT(ss.rank() == 1);
    CPPUNIT_ASSERT(ss.size() == 1);
    CPPUNIT_ASSERT_NO_THROW(ss.extend(0,10));
    CPPUNIT_ASSERT(ss.rank() == 1);
    CPPUNIT_ASSERT(ss.size() == 11);

    //reshape the dataset
    Shape ns(2);
    ns.dim(0,100);ns.dim(1,512);
    CPPUNIT_ASSERT_NO_THROW(ds.resize(ns));
    CPPUNIT_ASSERT(ds.shape() == ns);
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_write_simple_types(){
    std::cout<<"void H5DatasetTest::test_write_simple_types()-----------------";
    std::cout<<std::endl;

    //start with a scalar dataset
    H5Datatype type = H5DatatypeFactory::create_type<Float32>();
    H5Dataset scalar_ds("scalar_dataset",_group,type);
    double value =1.23;
    CPPUNIT_ASSERT_NO_THROW(scalar_ds.write(value));

    Shape s(1); s.dim(0,1);
    Shape cs(1); cs.dim(0,1); 
    H5Dataset array_ds("array_dataset",_group,type,{1},cs);
    CPPUNIT_ASSERT_NO_THROW(array_ds.write(value));

    //extensible string dataset
    String str="hello";
    type = H5DatatypeFactory::create_type<String>();
    H5Dataspace space = {1};
    H5Dataset string_ds("string_ds",_group,type,space,cs);
    CPPUNIT_ASSERT_NO_THROW(string_ds.write(str));

    //try a scalar string field
    H5Dataset sstring_ds("scalar_string_ds",_group,type);
    CPPUNIT_ASSERT_NO_THROW(sstring_ds.write(str));
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_read_simple_types(){
    std::cout<<"void H5DatasetTest::test_read_simple_types()-----------------";
    std::cout<<std::endl;

    test_write_simple_types();

    double value = 0.;
    H5Dataset ds = _group["scalar_dataset"];
    CPPUNIT_ASSERT_NO_THROW(ds.read(value));
    std::cout<<value<<std::endl;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(value,1.23,1e-6);

    ds = _group["array_dataset"];
    value = 0.;
    CPPUNIT_ASSERT_NO_THROW(ds.read(value));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(value,1.23,1e-6);

}
//-----------------------------------------------------------------------------
void H5DatasetTest::test_write_scalar(){
    std::cout<<"void H5DatasetTest::test_write_scalar()-----------------------";
    std::cout<<std::endl;

    Float32Scalar s(100.233,"scdata","a.u.","a simple scalar value");
    H5Datatype type = H5DatatypeFactory::create_type<Float32>();
    H5Dataset scalar_ds("scalar_ds",_group,type);
    CPPUNIT_ASSERT_NO_THROW(scalar_ds.write(s));

    //EXCEPTION TESTS ARE MISSING

}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_read_scalar(){
    std::cout<<"void H5DatasetTest::test_read_scalar()-----------------------";
    std::cout<<std::endl;

    test_write_scalar();

    H5Dataset ds = _group["scalar_ds"];
    Float64Scalar f64("scalar","au","scalar data");
    CPPUNIT_ASSERT_NO_THROW(ds.read(f64));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(f64.value(),100.233,1.e-5);

    //EXCEPTION TESTS ARE MISSING
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_write_array(){
    std::cout<<"void H5DatasetTest::test_write_array()-----------------------";
    std::cout<<std::endl;

    Shape s(2); s.dim(0,3); s.dim(1,5);
    UInt32Array a(s,"det","cps","useless data");
    a = 24;

    H5Datatype type = H5DatatypeFactory::create_type<UInt32>();
    H5Dataspace space = {3,5};
    H5Dataset array_ds("array_1",_group,type,space);
    CPPUNIT_ASSERT_NO_THROW(array_ds.write(a));

    Shape cs(3); cs.dim(0,1); cs.dim(1,s[0]); cs.dim(2,s[1]);
    Shape ds(3); ds.dim(0,1); ds.dim(1,s[0]); ds.dim(2,s[1]);
    space = H5Dataspace({1,3,5});
    H5Dataset earray_ds("earray_2",_group,type,space,cs);
    CPPUNIT_ASSERT_THROW(earray_ds.write(a),ShapeMissmatchError);
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_read_array(){
    test_write_array();

    H5Dataset d = _group["array_1"];
    UInt32Array a(d.shape(),"det","cps","detector data");
    CPPUNIT_ASSERT_NO_THROW(d.read(a));

    for(size_t i=0;i<a.shape().size();i++) CPPUNIT_ASSERT(a[i] == 24);
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_write_buffer(){
    std::cout<<"void H5DatasetTest::test_write_buffer()----------------------";
    std::cout<<std::endl;

    Buffer<Binary> buffer(128);
    Shape s(1); s.dim(0,128); 
    buffer = 10;
    H5Datatype type = H5DatatypeFactory::create_type<TypeID::BINARY>();
    H5Dataspace space = {128};
    H5Dataset bin_ds("binary_1",_group,type,space);
    CPPUNIT_ASSERT_NO_THROW(bin_ds.write(buffer));

    Shape cs(1); cs.dim(0,buffer.size());
    s.dim(0,128);
    buffer = 200;
    H5Dataset ebin_ds("binary_2",_group,type,space,cs);
    CPPUNIT_ASSERT_NO_THROW(ebin_ds.write(buffer));

    buffer.allocate(100);
    CPPUNIT_ASSERT_THROW(bin_ds.write(buffer),SizeMissmatchError);
}

//------------------------------------------------------------------------------
void H5DatasetTest::test_read_buffer(){
    std::cout<<"void H5DatasetTest::test_read_buffer()------------------------";
    std::cout<<std::endl;

    test_write_buffer();
    H5Dataset ds = _group.open("binary_1");
    Buffer<Binary> buffer(ds.size());
    CPPUNIT_ASSERT_NO_THROW(ds.read(buffer));
    for(size_t i=0;i<buffer.size();i++) CPPUNIT_ASSERT(buffer[i] == 10);

    ds = _group["binary_2"];
    buffer.allocate(ds.size());
    CPPUNIT_ASSERT_NO_THROW(ds.read(buffer));
    for(size_t i=0;i<buffer.size();i++) CPPUNIT_ASSERT(buffer[i] == 200);

    buffer.allocate(100);
    CPPUNIT_ASSERT_THROW(ds.read(buffer),SizeMissmatchError);
}


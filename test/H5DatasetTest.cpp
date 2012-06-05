#include "H5DatasetTest.hpp"
#include "../src/h5/H5DeflateFilter.hpp"

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
    Shape s{10,50};
    H5Dataspace space = {10,50};
    H5Datatype type   = H5DatatypeFactory::create_type<TypeID::FLOAT32>();

    //create contiguous dataset
    H5Dataset ds1("ds1",_group,type,space);
    CPPUNIT_ASSERT(ds1.is_valid());
    CPPUNIT_ASSERT(ds1.type_id()==TypeID::FLOAT32);

    //create a chunked dataset
    Shape cs{1,50};
    type = H5DatatypeFactory::create_type<TypeID::UINT32>();
    H5Dataset ds2("ds2",_group,type,space,cs);
    CPPUNIT_ASSERT(ds2.is_valid());
    CPPUNIT_ASSERT(ds2.type_id() == TypeID::UINT32);

    //create a scalar dataset
    type = H5DatatypeFactory::create_type<TypeID::FLOAT128>();
    H5Dataset ds3("ds3",_group,type,H5Dataspace());
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

    //create a chunked datatype with a filter
    H5DeflateFilter filter(9,true);
    H5Dataset dsc("compressed_data",_group,type,space,cs,filter);
    
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_assignment(){
    std::cout<<"void H5DatasetTest::test_assignment()-------------------------";
    std::cout<<std::endl;
    
    Shape s{1024,512};
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

    Shape s = {1024,512};
    H5Datatype type = H5DatatypeFactory::create_type<Float128>();
    H5Dataspace space = {1024,512};
    H5Dataset ds("ds",_file,type,space);

    CPPUNIT_ASSERT(ds.is_valid());
    CPPUNIT_ASSERT(ds.type_id() == TypeID::FLOAT128);
    CPPUNIT_ASSERT(ds.shape() == s);

    H5Dataset ds2("/scan_1/detector/data",_file,type,space);
    CPPUNIT_ASSERT(ds2.path() == "/scan_1/detector/data");
    CPPUNIT_ASSERT(ds2.base() == "/scan_1/detector");
    CPPUNIT_ASSERT(ds2.name() == "data");
    H5Group g = ds2.parent();
    CPPUNIT_ASSERT(g.is_valid());
    CPPUNIT_ASSERT(g.path() == "/scan_1/detector");
    CPPUNIT_ASSERT(g.base() == "/scan_1");
    CPPUNIT_ASSERT(g.name() == "detector");
    g = _file.open("/scan_1/detector");
    CPPUNIT_ASSERT(g.path() == "/scan_1/detector");
    CPPUNIT_ASSERT(g.base() == "/scan_1");
    CPPUNIT_ASSERT(g.name() == "detector");
    CPPUNIT_ASSERT_NO_THROW(ds = g.open("/scan_1/detector/data"));
    CPPUNIT_ASSERT(ds2.path() == "/scan_1/detector/data");
    CPPUNIT_ASSERT(ds2.base() == "/scan_1/detector");
    CPPUNIT_ASSERT(ds2.name() == "data");

}

void H5DatasetTest::test_linking()
{
    std::cout<<"void H5DatasetTest::test_linking()------------------------------";
    std::cout<<std::endl;

    //checking internal links
    H5Datatype type = H5DatatypeFactory::create_type<Float128>();
    H5Dataspace space;
    H5Dataset d("/data/test/dir/data",_file,type,space);
    CPPUNIT_ASSERT_NO_THROW(d.link("/collection/data"));
    CPPUNIT_ASSERT(_file.exists("/collection/data"));

    H5Group ref = _file.open("/data/test");
    CPPUNIT_ASSERT_NO_THROW(d.link(ref,"whatever"));
    CPPUNIT_ASSERT(_file.exists("/data/test/whatever"));


}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_resize(){
    std::cout<<"void H5DatasetTest::test_resize()-----------------------------";
    std::cout<<std::endl;

    //create base shape
    Shape s{0,1024};
    Shape cs{1,1024};
    H5Datatype type = H5DatatypeFactory::create_type<UInt32>();
    H5Dataspace space({0,1024},{H5Dataspace::UNLIMITED,H5Dataspace::UNLIMITED});

    H5Dataset ds("ds",_group,type,space,cs);

    CPPUNIT_ASSERT_NO_THROW(ds.grow(0));
    s = Shape({1,1024});
    CPPUNIT_ASSERT(ds.rank()  == s.rank());
    CPPUNIT_ASSERT(ds.shape() == s);
    s = Shape({4,1024});
    CPPUNIT_ASSERT_NO_THROW(ds.grow(0,3));
    CPPUNIT_ASSERT(ds.rank()  == s.rank());
    CPPUNIT_ASSERT(ds.shape() == s);

    s = {0};
    cs = {1};
    type = H5DatatypeFactory::create_type<String>();
    CPPUNIT_ASSERT_NO_THROW(space = H5Dataspace({0},{H5Dataspace::UNLIMITED}));
    H5Dataset ss("ss",_group,type,space,cs);
    CPPUNIT_ASSERT(ss.rank() == 1);
    CPPUNIT_ASSERT(ss.size() == 0);
    CPPUNIT_ASSERT_NO_THROW(ss.grow(0));
    CPPUNIT_ASSERT(ss.rank() == 1);
    CPPUNIT_ASSERT(ss.size() == 1);
    CPPUNIT_ASSERT_NO_THROW(ss.grow(0,10));
    CPPUNIT_ASSERT(ss.rank() == 1);
    CPPUNIT_ASSERT(ss.size() == 11);

    //reshape the dataset
    Shape ns{100,512};
    CPPUNIT_ASSERT_NO_THROW(ds.resize(ns));
    CPPUNIT_ASSERT(ds.shape() == ns);
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_write_simple_types(){
    std::cout<<"void H5DatasetTest::test_write_simple_types()-----------------";
    std::cout<<std::endl;

    //start with a scalar dataset
    H5Datatype type = H5DatatypeFactory::create_type<Float32>();
    H5Dataset scalar_ds("scalar_dataset",_group,type,H5Dataspace());
    double value =1.23;
    CPPUNIT_ASSERT_NO_THROW(scalar_ds.write(value));

    Shape s{1};
    Shape cs{1}; 
    H5Dataset array_ds("array_dataset",_group,type,{1},cs);
    CPPUNIT_ASSERT_NO_THROW(array_ds.write(value));

    //extensible string dataset
    String str="hello";
    type = H5DatatypeFactory::create_type<String>();
    H5Dataspace space = {1};
    H5Dataset string_ds("string_ds",_group,type,space,cs);
    CPPUNIT_ASSERT_NO_THROW(string_ds.write(str));

    //try a scalar string field
    H5Dataset sstring_ds("scalar_string_ds",_group,type,H5Dataspace());
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
    H5Dataset scalar_ds("scalar_ds",_group,type,H5Dataspace());
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

    Shape s{3,5};
    auto a = ArrayFactory<UInt32>::create(s);
    a.name("det"); a.unit("cps"); a.description("useless data");
    a = 24;

    H5Datatype type = H5DatatypeFactory::create_type<UInt32>();
    H5Dataspace space = {3,5};
    H5Dataset array_ds("array_1",_group,type,space);
    CPPUNIT_ASSERT_NO_THROW(array_ds.write(a));

    Shape cs{1,s[0],s[1]};
    Shape ds{1,s[0],s[1]};
    space = H5Dataspace({1,3,5});
    H5Dataset earray_ds("earray_2",_group,type,space,cs);
    CPPUNIT_ASSERT_THROW(earray_ds.write(a),ShapeMissmatchError);
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_read_array(){
    test_write_array();

    H5Dataset d = _group["array_1"];
    auto a = ArrayFactory<UInt32>::create(d.shape());
    a.name("det"); a.unit("cps"); a.description("detector data");
    CPPUNIT_ASSERT_NO_THROW(d.read(a));

    for(size_t i=0;i<a.shape().size();i++) CPPUNIT_ASSERT(a[i] == 24);
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_write_buffer(){
    std::cout<<"void H5DatasetTest::test_write_buffer()----------------------";
    std::cout<<std::endl;

    Buffer<Binary> buffer(128);
    Shape s{128}; 
    buffer = 10;
    H5Datatype type = H5DatatypeFactory::create_type<TypeID::BINARY>();
    H5Dataspace space = {128};
    H5Dataset bin_ds("binary_1",_group,type,space);
    CPPUNIT_ASSERT_NO_THROW(bin_ds.write(buffer));

    Shape cs{buffer.size()};
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


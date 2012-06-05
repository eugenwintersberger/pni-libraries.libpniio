//implementation of H5Selection tests

#include "H5SelectionTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5SelectionTest);

//-----------------------------------------------------------------------------
void H5SelectionTest::setUp(){
    _shape = {1,12,57};

    _chunk = Shape(_shape);

    _file = H5File::create_file("H5SelectionTest.h5",true,0);
    H5Datatype type = H5DatatypeFactory::create_type<TypeID::FLOAT32>();
    H5Dataspace space(_shape);
    _dset = H5Dataset("array",_file,type,space,_chunk);
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

    CPPUNIT_ASSERT(_dset.shape() == _shape);
    H5Selection s1 =  _dset.selection();
    CPPUNIT_ASSERT(s1.shape() == _shape);

    
    //using copy constructor
    H5Selection s2= s1;
    CPPUNIT_ASSERT(s2.shape() == s1.shape());

    //using move constructor
    H5Selection s3;
    CPPUNIT_ASSERT_NO_THROW(s3= std::move(s1));
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
    Shape cs = {1};
    H5Datatype type = H5DatatypeFactory::create_type<Float32>();
    H5Dataspace space({0},{H5Dataspace::UNLIMITED});
    H5Dataset array_ds("array_dataset",_file,type,space,cs);
    array_ds.grow(0);

    H5Selection selection = array_ds.selection();
    selection.count(0,1);
    selection.offset(0,0);
    double value = 1;
    CPPUNIT_ASSERT_NO_THROW(selection.write(value));
    array_ds.grow(0);
    selection.offset(0,1);
    value = 2;
    CPPUNIT_ASSERT_NO_THROW(selection.write(value));
    CPPUNIT_ASSERT(array_ds.rank() == 1);
    CPPUNIT_ASSERT(array_ds.size() == 2);


    //extensible string dataset
    String str="hello";
    type = H5DatatypeFactory::create_type<String>();
    H5Dataset string_ds("string_ds",_file,type,space,cs);

    CPPUNIT_ASSERT_NO_THROW(string_ds.grow(0));

    selection = string_ds.selection();
    selection.offset(0,0); 
    selection.count(0,1);
    CPPUNIT_ASSERT_NO_THROW(selection.write(str));

    CPPUNIT_ASSERT_NO_THROW(string_ds.grow(0));
    selection.offset(0,1);
    str = "this is a text";
//    std::cout<<string_ds.shape()<<std::endl;
//    std::cout<<selection.shape()<<std::endl;
//    std::cout<<string_ds.space().rank()<<std::endl;
//    std::cout<<string_ds.space().size()<<std::endl;
    std::cout<<string_ds.space()<<std::endl;
    CPPUNIT_ASSERT_NO_THROW(selection.write(str));

}

//-----------------------------------------------------------------------------
void H5SelectionTest::test_read_simple_types(){
    std::cout<<"void H5SelectionTest::test_read_simple_types()-----------------";
    std::cout<<std::endl;
    double value = 1.2;
    double read = 0.;

    //----------write data with selection--------------------------
    Shape cs = {1};
    H5Datatype type = H5DatatypeFactory::create_type<Float32>();
    H5Dataspace space({0},{H5Dataspace::UNLIMITED});
    H5Dataset array_ds("array_dataset",_file,type,space,cs);
    H5Selection selection = array_ds.selection();
    selection.offset(0,0); selection.count(0,1);
    array_ds.grow(0);
    CPPUNIT_ASSERT_NO_THROW(selection.write(value));

    array_ds.grow(0);
    selection.offset(0,1);
    value = 2.3;
    CPPUNIT_ASSERT_NO_THROW(selection.write(value));
   
    array_ds.grow(0);
    selection.offset(0,2);
    value = -9.234;
    CPPUNIT_ASSERT_NO_THROW(selection.write(value));
   
    H5Dataset array_ds2("array_dataset2",_file,type,space,cs);
    selection = array_ds2.selection();
    selection.offset(0,0); 
    selection.count(0,1);
    array_ds2.grow(0);
    CPPUNIT_ASSERT_NO_THROW(selection.write(value));

    array_ds2.grow(0);
    selection.offset(0,1);
    value = 2.3;
    CPPUNIT_ASSERT_NO_THROW(selection.write(value));
   
    array_ds2.grow(0);
    selection.offset(0,2);
    value = -9.234;
    CPPUNIT_ASSERT_NO_THROW(selection.write(value));


    //----------read back data with selection-----------------------
    selection.offset(0,0);
    CPPUNIT_ASSERT_NO_THROW(selection.read(read));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(read,-9.234,1.e-6);
    selection.offset(0,1);
    CPPUNIT_ASSERT_NO_THROW(selection.read(read));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(read,2.3,1.e-6);
    selection.offset(0,2);
    CPPUNIT_ASSERT_NO_THROW(selection.read(read));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(read,-9.234,1.e-5);


    //extensible string dataset
    String str="hello";
    type = H5DatatypeFactory::create_type<String>();
    space = H5Dataspace({0},{H5Dataspace::UNLIMITED});
    H5Dataset string_ds("string_ds",_file,type,space,cs);
    selection = string_ds.selection();
    string_ds.grow(0);
    selection.offset(0,0);
    selection.count(0,1);
    CPPUNIT_ASSERT_NO_THROW(selection.write(str));
    string_ds.grow(0);
    selection.offset(0,1);
    str = "this is a text";
    CPPUNIT_ASSERT_NO_THROW(selection.write(str));

    //read back data
    String sread;
    selection.offset(0,0);
    CPPUNIT_ASSERT_NO_THROW(selection.read(sread));
    CPPUNIT_ASSERT(sread == "hello");
    selection.offset(0,1);
    CPPUNIT_ASSERT_NO_THROW(selection.read(sread));
    CPPUNIT_ASSERT(sread == "this is a text");

}
//-----------------------------------------------------------------------------
void H5SelectionTest::test_write_scalar(){
    std::cout<<"void H5SelectionTest::test_write_scalar()-----------------------";
    std::cout<<std::endl;
    Float32Scalar s(1,"scalar","au","test scalar");

    Shape sh{0};
    Shape cs{1};
    H5Dataspace space({0},{H5Dataspace::UNLIMITED});
    H5Datatype type = H5DatatypeFactory::create_type<Float32>();
    H5Dataset array_ds("array_ds",_file,type,space,cs);
    array_ds.grow(0);
    H5Selection selection = array_ds.selection();
    selection.offset(0,0); 
    selection.count(0,1);
    CPPUNIT_ASSERT_NO_THROW(selection.write(s));
    s = -0.2334;
    selection.offset(0,1);
    array_ds.grow(0);
    CPPUNIT_ASSERT_NO_THROW(selection.write(s));


    H5Dataset array_ds2("array_ds2",_file,type,space,cs);
    s = 1;
    selection = array_ds2.selection();
    array_ds2.grow(0);
    selection.offset(0,0); 
    selection.count(0,1);
    CPPUNIT_ASSERT_NO_THROW(selection.write(s));
    s = -0.2334;
    selection.offset(0,1);
    array_ds2.grow(0);
    CPPUNIT_ASSERT_NO_THROW(selection.write(s));
}

//-----------------------------------------------------------------------------
void H5SelectionTest::test_read_scalar(){
    std::cout<<"void H5SelectionTest::test_read_scalar()----------------------";
    std::cout<<std::endl;

    //generate data
    test_write_scalar();

    //get dataset and selection object
    H5Dataset ds = _file["array_ds"];
    H5Selection selection = ds.selection();

    selection.offset(0,0);
    selection.count(0,1);

    Float64Scalar scalar("scalar","a.u","scalar data");

    CPPUNIT_ASSERT_NO_THROW(selection.read(scalar));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(scalar.value(),1,1.e-6);
    selection.offset(0,1);
    CPPUNIT_ASSERT_NO_THROW(selection.read(scalar));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(scalar.value(),-0.2334,1.e-6);

}

//-----------------------------------------------------------------------------
void H5SelectionTest::test_write_array(){
    std::cout<<"void H5SelectionTest::test_write_array()-----------------------";
    std::cout<<std::endl;

    //create the array from which to write data
    Shape s = {3,5};
    auto a = ArrayFactory<UInt32>::create(s);
    a.name("det"); a.unit("cps"); a.description("useless data");
    CPPUNIT_ASSERT(a.is_allocated());
    a = 24;

    //create dataspace and datatype
    Shape cs = {0,3,5};
    H5Dataspace space({0,3,5},{H5Dataspace::UNLIMITED,3,5});
    H5Datatype type = H5DatatypeFactory::create_type<UInt32>();

    //create the dataset and selection object
    cs = {1,3,5};
    H5Dataset earray_ds("earray_2",_file,type,space,cs);
    H5Selection selection = earray_ds.selection(); 
    selection.offset({0,0,0});
    selection.count({1,3,5});

    CPPUNIT_ASSERT_NO_THROW(earray_ds.grow(0));
    CPPUNIT_ASSERT_NO_THROW(selection.write(a));
    a = 100;
    earray_ds.grow(0);
    selection.offset(0,1);
    CPPUNIT_ASSERT_NO_THROW(selection.write(a));
}

//-----------------------------------------------------------------------------
void H5SelectionTest::test_read_array(){
    std::cout<<"void H5SelectionTest::test_read_array()----------------------";
    std::cout<<std::endl;

    //create data
    test_write_array();

    //get dataset and selection
    H5Dataset ds = _file.open("earray_2");
    H5Selection selection = ds.selection();

    selection.offset(0,0);
    selection.count(0,1);
    
}

//-----------------------------------------------------------------------------
void H5SelectionTest::test_write_buffer(){
    std::cout<<"void H5SelectionTest::test_write_buffer()----------------------";
    std::cout<<std::endl;

    Buffer<Binary> buffer(128);

    Shape cs = {buffer.size()};
    H5Datatype type = H5DatatypeFactory::create_type<Binary>();
    H5Dataspace space({0},{H5Dataspace::UNLIMITED});
    H5Dataset ebin_ds("binary_2",_file,type,space,cs);
    H5Selection selection = ebin_ds.selection();
    ebin_ds.grow(0,128);
    selection.count(0,128);
    buffer = 100;
    CPPUNIT_ASSERT_NO_THROW(selection.write(buffer));
    ebin_ds.grow(0,128);
    selection.offset(0,128);
    buffer = 200;
    CPPUNIT_ASSERT_NO_THROW(selection.write(buffer));
}

//------------------------------------------------------------------------------
void H5SelectionTest::test_read_buffer(){
    std::cout<<"void H5SelectionTest::test_read_buffer()----------------------";
    std::cout<<std::endl;

    //generate data
    test_write_buffer();

    //get dataspace and selection
    H5Dataset ds = _file["binary_2"];
    H5Selection selection = ds.selection();

    selection.offset(0,0);
    selection.count(0,64);

    Buffer<Binary> buffer(selection.size());
    CPPUNIT_ASSERT_NO_THROW(selection.read(buffer));
    for(size_t i=0;i<buffer.size();i++) CPPUNIT_ASSERT(buffer[i] == 100);
   
    selection.offset(0,64);
    CPPUNIT_ASSERT_NO_THROW(selection.read(buffer));
    for(size_t i=0;i<buffer.size();i++) CPPUNIT_ASSERT(buffer[i] == 100);
    
    selection.offset(0,128);
    CPPUNIT_ASSERT_NO_THROW(selection.read(buffer));
    for(size_t i=0;i<buffer.size();i++) CPPUNIT_ASSERT(buffer[i] == 200);

}

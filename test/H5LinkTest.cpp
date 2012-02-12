
#include "H5LinkTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5LinkTest);

//-----------------------------------------------------------------------------
void H5LinkTest::setUp(){
    _file1 = H5File::create_file("H5LinkTest1.h5",true,0);
    _file2 = H5File::create_file("H5LinkTest2.h5",true,0);
}

//------------------------------------------------------------------------------
void H5LinkTest::tearDown(){
    _file1.close();
    _file2.close();
}

//------------------------------------------------------------------------------
void H5LinkTest::test_internal(){
    std::cout<<"void H5LinkTest::test_internal()-----------------------------";
    std::cout<<std::endl;

    H5Datatype type = H5DatatypeFactory::create_type<Float64>();
    H5Dataspace space;
    H5Dataset ds("data",_file1,type,space);
    Float64 value = 100.1234;
    CPPUNIT_ASSERT_NO_THROW(ds.write(value));

    CPPUNIT_ASSERT_NO_THROW(H5Link::create("/data",_file1,"data_1_link_1"));
    CPPUNIT_ASSERT_NO_THROW(H5Link::create("data",_file1,"data_1_link_2"));
    CPPUNIT_ASSERT_NO_THROW(H5Link::create(ds,_file1,"data_1_link_3"));

    H5Dataset dread;
    CPPUNIT_ASSERT_NO_THROW(dread = _file1.open("data_1_link_1"));
    Float64 read;
    CPPUNIT_ASSERT_NO_THROW(dread.read(read));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(value,read,1.e-6);
    
    CPPUNIT_ASSERT_NO_THROW(dread = _file1.open("data_1_link_2"));
    CPPUNIT_ASSERT_NO_THROW(dread.read(read));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(value,read,1.e-6);

    CPPUNIT_ASSERT_NO_THROW(dread = _file1.open("data_1_link_3"));
    CPPUNIT_ASSERT_NO_THROW(dread.read(read));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(value,read,1.e-6);

    //links can also be created in advance
    CPPUNIT_ASSERT_NO_THROW(H5Link::create("/detector/counts",_file1,"detdat"));
    type = H5DatatypeFactory::create_type<UInt16>();
    CPPUNIT_ASSERT_NO_THROW(ds=H5Dataset("/detector/counts",_file1,type,space));
    UInt16 scalar = 1024;
    UInt16 sread = 0;
    CPPUNIT_ASSERT_NO_THROW(ds.write(scalar));
    dread = _file1.open("detdat");
    CPPUNIT_ASSERT_NO_THROW(dread.read(sread));
    CPPUNIT_ASSERT(sread == scalar);
}

//------------------------------------------------------------------------------
void H5LinkTest::test_external(){
    std::cout<<"void H5LinkTest::test_external()-----------------------------";
    std::cout<<std::endl;
    
    H5Datatype type = H5DatatypeFactory::create_type<Float64>();
    H5Dataspace space;

    //create target in the first file
    H5Dataset dwrite("data",_file1,type,space);
    //write some data
    Float64 wval = -1.25091;
    CPPUNIT_ASSERT_NO_THROW(dwrite.write(wval));

    //create the external link in the second file

    CPPUNIT_ASSERT_NO_THROW(H5Link::create("H5LinkTest1.h5:/data",
                _file2,"external/data"));

    Float64 read;
    H5Dataset dread = _file2.open("/external/data");
    CPPUNIT_ASSERT_NO_THROW(dread.read(read));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(wval,read,1.e-6);

}


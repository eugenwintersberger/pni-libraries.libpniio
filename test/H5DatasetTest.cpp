#include "H5DatasetTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5DatasetTest);


void H5DatasetTest::setUp(){
    _file.create("H5DatasetTest.h5",true,0);
    _group =H5Group("data",_file);
}

void H5DatasetTest::tearDown(){
    _group.close();
    _file.close();
}

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



#include "H5GroupTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5GroupTest);


//-----------------------------------------------------------------------------
void H5GroupTest::setUp(){
    file = H5File::create_file("H5GroupTest.h5",true,0);
}

//-----------------------------------------------------------------------------
void H5GroupTest::tearDown(){
    file.close();
}

//-----------------------------------------------------------------------------
void H5GroupTest::test_creation(){
    std::cout<<"void H5GroupTest::test_creation()-----------------------------";
    std::cout<<std::endl;
    H5Group g; //default constructor

    CPPUNIT_ASSERT(!g.is_valid());

    //create directly using the constructor
    H5Group g1("group1",file);
    CPPUNIT_ASSERT(g1.is_valid());
    CPPUNIT_ASSERT(g1.name()=="group1");

    //create a group from another group
    H5Group g2("group12",g1);
    CPPUNIT_ASSERT(g2.is_valid());

    //using the copy constructor
    H5Group g3 = g2;
    CPPUNIT_ASSERT(g3.is_valid());
    CPPUNIT_ASSERT(g2.is_valid());

    //using the move constructor
    H5Group g4 = std::move(g2);
    CPPUNIT_ASSERT(g4.is_valid());
    CPPUNIT_ASSERT(!g2.is_valid());

    //testing creation of a full path
    H5Group g5("group5/test/directory",file);
    CPPUNIT_ASSERT(g5.is_valid());

    CPPUNIT_ASSERT(g5.name() == "directory");
    CPPUNIT_ASSERT(g5.path() == "/group5/test/directory");
    CPPUNIT_ASSERT(g5.base() == "/group5/test");
}

//-----------------------------------------------------------------------------
void H5GroupTest::test_assignment(){
    std::cout<<"void H5GroupTest::test_assignment()---------------------------";
    std::cout<<std::endl;

    H5Group g("group1",file);
    H5Group g1,g2;
    
    //test copy assignment
    CPPUNIT_ASSERT_NO_THROW(g1 = g);
    CPPUNIT_ASSERT(g1.is_valid());
    CPPUNIT_ASSERT(g.is_valid());

    //test move assignment
    CPPUNIT_ASSERT_NO_THROW(g2 = std::move(g));
    CPPUNIT_ASSERT(g2.is_valid());
    CPPUNIT_ASSERT(!g.is_valid());

    g.close();
    g1.close();
    g2.close();
}

//-----------------------------------------------------------------------------
void H5GroupTest::test_linking()
{
    std::cout<<"void H5GroupTest::test_linking()------------------------------";
    std::cout<<std::endl;

    //checking internal links
    H5Group g("/data/test/dir",file);
    CPPUNIT_ASSERT_NO_THROW(g.link("/collection/dir"));
    CPPUNIT_ASSERT(file.exists("/collection/dir"));

    H5Group ref = file.open("/data/test");
    CPPUNIT_ASSERT_NO_THROW(g.link(ref,"whatever"));
    CPPUNIT_ASSERT(file.exists("/data/test/whatever"));


    //check external links
    H5File file2 = H5File::create_file("H5GroupTest2.h5",true,0);
    H5Group("/detector/data",file2);
        
    CPPUNIT_ASSERT_NO_THROW(file.link("H5GroupTest2.h5:/detector/data",
                "external/detector/data"));
    CPPUNIT_ASSERT(file.exists("/external/detector/data"));

    
}

//------------------------------------------------------------------------------
void H5GroupTest::test_openobjects(){
    std::cout<<"void H5GroupTest::test_openobjects()--------------------------";
    std::cout<<std::endl;
        
    H5Group g("/test/data/detector",file);
    H5Group det;

    CPPUNIT_ASSERT_NO_THROW(det = file.open("/test/data/detector"));
    CPPUNIT_ASSERT(det.is_valid());
    CPPUNIT_ASSERT(det.path() == "/test/data/detector");
    CPPUNIT_ASSERT(det.base() == "/test/data");
    CPPUNIT_ASSERT(det.name() == "detector");

    H5Group p;
    CPPUNIT_ASSERT_NO_THROW(p = det.parent());
    CPPUNIT_ASSERT(p.path() == "/test/data");
    CPPUNIT_ASSERT(p.base() == "/test");
    CPPUNIT_ASSERT(p.name() == "data");

    H5Group test;
    CPPUNIT_ASSERT_NO_THROW(test = file["test"]);
    CPPUNIT_ASSERT(test.is_valid());
    H5Group data;
    CPPUNIT_ASSERT_NO_THROW(data = test["data"]);
    CPPUNIT_ASSERT_NO_THROW(det = test["data/detector"]);
    CPPUNIT_ASSERT(data.is_valid());
    CPPUNIT_ASSERT(det.is_valid());
}

//------------------------------------------------------------------------------
void H5GroupTest::test_attributes(){
    std::cout<<"void H5GroupTest::test_attributes()---------------------------";
    std::cout<<std::endl;
    H5Group g("data",file);

    //-----------------read and write a string attribute-----------------------
    String comment = "hello world";
    CPPUNIT_ASSERT_NO_THROW(g.attr<String>("comment").write(comment));
    //read the attribute back
    String str_value;
    CPPUNIT_ASSERT_NO_THROW(str_value = g.attr("comment").read<String>());
    CPPUNIT_ASSERT(str_value.size() == comment.size());
    CPPUNIT_ASSERT(str_value == comment);

    //--------------read and write a scalar attribute--------------------------
    Float32Scalar scalar(0.2,"atribute","a.u.","scalar attribute");
    CPPUNIT_ASSERT_NO_THROW(g.attr<Float32>("pressure").write(scalar));
    Float64Scalar sc_value("attribute","a.u.","scalar attribute");
    CPPUNIT_ASSERT_NO_THROW(sc_value = g.attr("pressure").read<Float64Scalar>());
    CPPUNIT_ASSERT(sc_value == scalar);

    //-------------read and write an array attribute--------------------------
    Shape s(2);
    s.dim(0,10); s.dim(1,3);
    UInt16Array data(s);
    data=113;
    CPPUNIT_ASSERT_NO_THROW(g.attr<UInt16>("data",data.shape()).write(data));
    Float32Array ar_value;
    CPPUNIT_ASSERT_NO_THROW(ar_value = g.attr("data").read<Float32Array>());
    CPPUNIT_ASSERT(data[0] == ar_value[0]);

    //----------------try the game with plain old data-------------------------
    Float32 fvalue;
    CPPUNIT_ASSERT_NO_THROW(fvalue = g.attr("pressure").read<Float32>());
    CPPUNIT_ASSERT(fvalue == sc_value);
    CPPUNIT_ASSERT(g.attr("pressure").name() == "pressure");

    //is the other way around workding
    UInt16 sca = 291;
    CPPUNIT_ASSERT_NO_THROW(g.attr<UInt16>("SCA").write(sca));
    UInt32Scalar sca_value;
    CPPUNIT_ASSERT_NO_THROW(sca_value = g.attr("SCA").read<UInt32Scalar>());
    CPPUNIT_ASSERT(sca_value == sca);

    //================now we need to check exceptions==========================
    CPPUNIT_ASSERT_THROW(g.attr("data").write(sca),ShapeMissmatchError);
    CPPUNIT_ASSERT_THROW(g.attr("SCA").write(data),ShapeMissmatchError);
    CPPUNIT_ASSERT_THROW(g.attr("data").write(sca_value),ShapeMissmatchError);

    CPPUNIT_ASSERT_THROW(g.attr("data").read<Float32Scalar>(),ShapeMissmatchError);
    CPPUNIT_ASSERT_THROW(g.attr("SCA").read<UInt32Array>(),ShapeMissmatchError);
    CPPUNIT_ASSERT_THROW(g.attr("comment").read<Float32Scalar>(),H5AttributeError);

}

//------------------------------------------------------------------------------
void H5GroupTest::test_attribute_manipulation(){
    std::cout<<"void H5GrouTest::test_attribute_manipulation()---------------";
    std::cout<<std::endl;

    CPPUNIT_ASSERT_NO_THROW(file.attr<String>("strattr"));
    CPPUNIT_ASSERT_NO_THROW(file.attr<Float64>("temperature"));
    CPPUNIT_ASSERT_NO_THROW(file.attr<UInt8>("sca_value"));
    file.flush();
    
    std::cout<<"number of attribute: "<<file.nattr()<<std::endl;
    CPPUNIT_ASSERT(file.nattr() == 4);

    //removeing objects
    CPPUNIT_ASSERT(file.has_attr("strattr"));
    CPPUNIT_ASSERT(!file.has_attr("bla"));
    CPPUNIT_ASSERT_NO_THROW(file.del_attr("strattr"));
    CPPUNIT_ASSERT(!file.has_attr("strattr"));
    CPPUNIT_ASSERT_THROW(file.del_attr("bla"),H5AttributeError);

}

//-----------------------------------------------------------------------------
void H5GroupTest::test_comparison()
{
    std::cout<<"void H5GroupTest::test_comparison()---------------------------";
    std::cout<<std::endl;

    H5Group("group1/data",file);

    H5Group g1 = file["group1/data"];
    H5Group g2 = file["group1/data"];

    CPPUNIT_ASSERT(g1 == g2);

    g2 = file["group1"];
    CPPUNIT_ASSERT(g2 != g1);
}


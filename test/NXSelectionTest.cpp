#include "NXSelectionTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NXSelectionTest);

void NXSelectionTest::setUp()
{
    file = NXFile::create_file("NXSelectionTest.h5",true);
}

void NXSelectionTest::tearDown()
{
    file.close();
}

void NXSelectionTest::test_creation()
{
    std::cout<<"void NXSelectionTest::test_creation()-------------------------";
    std::cout<<std::endl;

    Shape s = {0,100};
    NXField field = file.create_field<Float32>("array",s);
    NXSelection sel = field.selection();

    CPPUNIT_ASSERT(sel.shape() == s);
    CPPUNIT_ASSERT(sel.rank() == field.rank());
    CPPUNIT_ASSERT(sel.shape() == field.shape());

}

void NXSelectionTest::test_assignment()
{
    std::cout<<"void NXSelectionTest::test_assignment()-----------------------";
    std::cout<<std::endl;

    Shape s = {1,100};
    NXField field = file.create_field<Float32>("array",s);
    NXSelection sel = field.selection();

    CPPUNIT_ASSERT(sel.size() == field.size());

    NXSelection s1 = sel;
    CPPUNIT_ASSERT(s1.shape() == sel.shape());
    CPPUNIT_ASSERT(s1.size() == sel.size());

    NXSelection s2 = std::move(sel);
    CPPUNIT_ASSERT(s2.size() == field.size());
    CPPUNIT_ASSERT(sel.size() == 0);
}

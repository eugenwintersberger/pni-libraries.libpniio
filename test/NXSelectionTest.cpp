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


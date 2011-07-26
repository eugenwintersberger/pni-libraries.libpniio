//testing class for ArrayShape objects

#ifndef __LIBPNIUTILS_ARRAYSHAPE_HPP__
#define __LIBPNIUTILS_ARRAYSHAPE_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "NXFile.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;

class NXFileTest: public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(NXFileTest);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testOpen);
	CPPUNIT_TEST_SUITE_END();
private:
public:
	void setUp();
	void tearDown();

	//testing basic file functionality
	void testCreation();
	void testOpen();


};

#endif

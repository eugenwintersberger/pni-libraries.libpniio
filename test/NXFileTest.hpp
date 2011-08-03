//testing class for ArrayShape objects

#ifndef __LIBPNIUTILS_ARRAYSHAPE_HPP__
#define __LIBPNIUTILS_ARRAYSHAPE_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include<boost/filesystem.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;
using namespace boost::filesystem;

class NXFileTest: public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(NXFileTest);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testOpen);
	CPPUNIT_TEST(testAttributes);
	CPPUNIT_TEST(testAttributeExceptions);
	CPPUNIT_TEST_SUITE_END();
private:
	String _fname1;
	String _fname2;
public:
	void setUp();
	void tearDown();

	//testing basic file functionality
	void testCreation();
	void testOpen();
	void testAttributes();
	void testAttributeExceptions();


};

#endif

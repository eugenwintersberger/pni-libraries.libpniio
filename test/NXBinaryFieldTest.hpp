/*
 * NXBinaryFieldTest.hpp
 *
 *  Created on: Dec 5, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef NXBINARYFIELDTEST_HPP_
#define NXBINARYFIELDTEST_HPP_

#include "NX.hpp"
#include <pni/utils/Buffer.hpp>
#include <pni/utils/PNITypes.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

using namespace pni::utils;
using namespace pni::nx::h5;

class NXBinaryFieldTest:public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(NXBinaryFieldTest);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testAssignment);
	CPPUNIT_TEST(testOpen);
	CPPUNIT_TEST(testAppend);
	CPPUNIT_TEST(testGetAll);
	CPPUNIT_TEST(testGet);
	CPPUNIT_TEST(testSet);
	CPPUNIT_TEST(testStreamIO);
	CPPUNIT_TEST_SUITE_END();
private:
	NXFile file;
	Binary testdata[10];
public:
	void setUp();
	void tearDown();

	void testCreation();
	void testAssignment();
	void testOpen();
	void testAppend();
	void testGetAll();
	void testGet();
	void testSet();
	void testStreamIO();

};

#endif /* NXBINARYFIELDTEST_HPP_ */

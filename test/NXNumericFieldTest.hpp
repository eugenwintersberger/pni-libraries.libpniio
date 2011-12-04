/*
 * NXNumericFieldTest.hpp
 *
 *  Created on: Dec 3, 2011
 *      Author: eugen
 */

#ifndef NXNUMERICFIELDTEST_HPP_
#define NXNUMERICFIELDTEST_HPP_

#include "NX.hpp"
#include <pni/utils/Index.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include<boost/filesystem.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;
using namespace boost::filesystem;

class NXNumericFieldTest:public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(NXNumericFieldTest);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testAssignment);
	CPPUNIT_TEST(testAppend);
	CPPUNIT_TEST(testGetIndividual);
	CPPUNIT_TEST(testGetAll);
	//CPPUNIT_TEST(testOpen);
	CPPUNIT_TEST_SUITE_END();
private:
	NXFile file;
	static const UInt64 n=10;
	UInt16 testdata[10];
	static const UInt64 nx=2;
	static const UInt64 ny=3;
public:
	void setUp();
	void tearDown();
	void testCreation();
	void testAssignment();
	void testOpen();
	void testAppend();
	void testGetIndividual();
	void testGetAll();

};

#endif /* NXNUMERICFIELDTEST_HPP_ */

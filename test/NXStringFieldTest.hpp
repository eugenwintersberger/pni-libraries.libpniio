/*
 * NXStringFieldTest.hpp
 *
 *  Created on: Dec 5, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef NXSTRINGFIELDTEST_HPP_
#define NXSTRINGFIELDTEST_HPP_

#include <vector>

#include "NX.hpp"
#include <pni/utils/Index.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

using namespace pni::utils;
using namespace pni::nx::h5;

class NXStringFieldTest:public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(NXStringFieldTest);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testAssignment);
	CPPUNIT_TEST(testOpen);
	CPPUNIT_TEST(testAppend);
	CPPUNIT_TEST(testGetIndividual);
	CPPUNIT_TEST(testGetAll);
	CPPUNIT_TEST_SUITE_END();
private:
	NXFile file;
	std::vector<String> strdata;
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

#endif /* NXSTRINGFIELDTEST_HPP_ */

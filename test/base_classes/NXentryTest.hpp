/*
 * NXrootTest.hpp
 *
 *  Created on: Sep 23, 2011
 *      Author: eugen
 */

#ifndef NXENTRYTEST_HPP_
#define NXENTRYTEST_HPP_

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../../src/NX.hpp"
#include "../../src/NXBaseClasses.hpp"

using namespace pni::nx::h5;

class NXentryTest:public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(NXentryTest);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testStringFields);
	CPPUNIT_TEST(testScalarFields);
	CPPUNIT_TEST(testObjectFields);
	CPPUNIT_TEST_SUITE_END();
private:
	NXroot f;
public:
	void setUp();
	void tearDown();

	void testCreation();
	void testStringFields();
	void testScalarFields();
	void testObjectFields();

	void testEntry();

};

#endif /* NXENTRYTEST_HPP_ */

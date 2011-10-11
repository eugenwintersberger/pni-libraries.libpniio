/*
 * NXrootTest.hpp
 *
 *  Created on: Sep 23, 2011
 *      Author: eugen
 */

#ifndef NXROOTTEST_HPP_
#define NXROOTTEST_HPP_

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../../src/NX.hpp"
#include "../../src/NXBaseClasses.hpp"

class NXrootTest:public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(NXrootTest);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testOpen);
	CPPUNIT_TEST(testAttributes);
	CPPUNIT_TEST(testEntry);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();

	void testCreation();
	void testOpen();
	void testAttributes();
	void testEntry();

};

#endif /* NXROOTTEST_HPP_ */

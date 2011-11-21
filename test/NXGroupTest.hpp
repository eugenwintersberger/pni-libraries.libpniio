/*
 * NXGroupTest.hpp
 *
 *  Created on: Aug 4, 2011
 *      Author: eugen
 */

#ifndef NXGROUPTEST_HPP_
#define NXGROUPTEST_HPP_

#include "NX.hpp"

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include<boost/filesystem.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;
using namespace boost::filesystem;

class NXGroupTest: public CppUnit::TestFixture  {
	CPPUNIT_TEST_SUITE(NXGroupTest);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testOpen);
	CPPUNIT_TEST(testAttributes);
	CPPUNIT_TEST(testAttributeExceptions);
	CPPUNIT_TEST(testInternalLinks);
	CPPUNIT_TEST(testExistence);
	CPPUNIT_TEST(testRemove);
	CPPUNIT_TEST(testAssignment);
	CPPUNIT_TEST_SUITE_END();
private:
	String _fname;
	NXFile _f;

	String          _write_str_attr;
	Float64Scalar   _write_scalar_attr;
	ArrayShape      _shape;
	Int16Array      _write_array_attr;
	Complex64Scalar _write_cmplx_scalar;
	String          _read_str_attr;
	Float64Scalar   _read_scalar_attr;
	Int16Array      _read_array_attr;
	Complex64Scalar _read_cmplx_scalar;
public:
	void setUp();
	void tearDown();
	void testCreation();
	void testOpen();
	void testAttributes();
	void testAttributeExceptions();
	void testInternalLinks();
	void testExistence();
	void testRemove();
	void testAssignment();
};

#endif /* NXGROUPTEST_HPP_ */

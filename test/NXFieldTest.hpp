/*
 * NXFieldTest.hpp
 *
 *  Created on: Aug 5, 2011
 *      Author: eugen
 */

#ifndef NXFIELDTEST_HPP_
#define NXFIELDTEST_HPP_

#include "NX.hpp"
#include <pni/utils/Index.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include<boost/filesystem.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;
using namespace boost::filesystem;


class NXFieldTest: public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(NXFieldTest);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testOpen);
	CPPUNIT_TEST(testReadData);
	CPPUNIT_TEST(testReadDataExceptions);
	CPPUNIT_TEST(testWriteData);
	CPPUNIT_TEST(testWriteDataExceptions);
	CPPUNIT_TEST(testAttributes);
	CPPUNIT_TEST(testAttributeExceptions);
	CPPUNIT_TEST(testLinks);
	CPPUNIT_TEST(testSelection);
	CPPUNIT_TEST(testSelectionFast);
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

	Float64Array _f64_data_array_write;
	Float64Array _f64_data_array_read;
	Complex64Array _c64_data_array_write;
	Complex64Array _c64_data_array_read;
	ArrayShape _data_shape;
public:
	void setUp();
	void tearDown();

	void testCreation();
	void testOpen();
	void testReadData();
	void testReadDataExceptions();
	void testWriteData();
	void testWriteDataExceptions();
	void testAttributes();
	void testAttributeExceptions();
	void testLinks();
	void testSelection();
	void testSelectionFast();

};

#endif /* NXFIELDTEST_HPP_ */

/*
 * Declaration of Nexus object template.
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * NXGroupTest.hpp
 *
 *  Created on: Aug 4, 2011
 *      Author: Eugen Wintersberger
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
    CPPUNIT_TEST(test_linking);
    CPPUNIT_TEST(test_comparison);
	CPPUNIT_TEST_SUITE_END();
private:
	String _fname;
	NXFile _f;

	String          _write_str_attr;
	Float64Scalar   _write_scalar_attr;
	Shape 	        _shape;
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
    void test_linking();
    void test_comparison();
};

#endif /* NXGROUPTEST_HPP_ */

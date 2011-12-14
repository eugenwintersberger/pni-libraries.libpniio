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
 * NXNumericFieldTest.hpp
 *
 *  Created on: Dec 3, 2011
 *      Author: Eugen Wintersberger
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
	CPPUNIT_TEST(testOpen);
	CPPUNIT_TEST(testSet);
	CPPUNIT_TEST_SUITE_END();
private:
	NXFile file;
	static const UInt64 n=10;
	UInt16 testdata[10];
	Shape  fshape;
	size_t nx;
	size_t ny;
public:
	void setUp();
	void tearDown();
	void testCreation();
	void testAssignment();
	void testOpen();
	void testAppend();
	void testGetIndividual();
	void testGetAll();
	void testSet();

};

#endif /* NXNUMERICFIELDTEST_HPP_ */

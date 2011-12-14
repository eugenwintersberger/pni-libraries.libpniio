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
 * NXBinaryFieldTest.hpp
 *
 *  Created on: Dec 5, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef NXBINARYFIELDTEST_HPP_
#define NXBINARYFIELDTEST_HPP_

#include "NX.hpp"
#include <pni/utils/Buffer.hpp>
#include <pni/utils/Types.hpp>

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

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
	CPPUNIT_TEST(testSet);
	CPPUNIT_TEST(testStreamWrite);
	CPPUNIT_TEST(testStreamRead);
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
	void testSet();
	void testStreamRead();
	void testStreamWrite();


};

#endif /* NXSTRINGFIELDTEST_HPP_ */

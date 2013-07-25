/*
 * Declaration of Nexus object template.
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * NXGroupTest.hpp
 *
 *  Created on: Aug 4, 2011
 *      Author: Eugen Wintersberger
 */

#pragma once

#include <pni/io/nx/nx.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>


using namespace pni::core;
using namespace pni::io::nx::h5;

class NXGroupTest: public CppUnit::TestFixture  
{
	CPPUNIT_TEST_SUITE(NXGroupTest);
	CPPUNIT_TEST(test_creation);
	CPPUNIT_TEST(test_open);
    CPPUNIT_TEST(test_parent);
//	CPPUNIT_TEST(test_internal_links);
    CPPUNIT_TEST(test_iterator);
	CPPUNIT_TEST(test_existance);
	CPPUNIT_TEST(test_remove);
	CPPUNIT_TEST(test_assignment);
 //   CPPUNIT_TEST(test_linking);
    CPPUNIT_TEST(test_comparison);
	CPPUNIT_TEST_SUITE_END();
private:
	string _fname;
	nxfile _f;
public:
	void setUp();
	void tearDown();
	void test_creation();
	void test_open();
//	void test_internal_links();
	void test_existance();
	void test_remove();
	void test_assignment();
//    void test_linking();
    void test_comparison();
    void test_iterator();
    void test_parent();
};


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
 *************************************************************************/

//testing class for ArrayShape objects

#ifndef __LIBPNIUTILS_ARRAYSHAPE_HPP__
#define __LIBPNIUTILS_ARRAYSHAPE_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>

#include "NX.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;

class NXFileTest: public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(NXFileTest);
	CPPUNIT_TEST(test_creation);
	CPPUNIT_TEST(test_open);
    CPPUNIT_TEST(test_iterator);
    CPPUNIT_TEST(test_inquery);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();

	//testing basic file functionality
	void test_creation();
	void test_open();
    void test_iterator();
    void test_inquery();


};

#endif

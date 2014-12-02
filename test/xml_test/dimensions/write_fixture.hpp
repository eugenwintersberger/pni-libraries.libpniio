//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Dec 2, 2014
//      Author: Eugen Wintersberger
//
#pragma once

#include <list>
#include <boost/current_function.hpp>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml/dimensions.hpp>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace pni::core;
using namespace pni::io::nx;

class write_fixture : public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(write_fixture);
        CPPUNIT_TEST(test_write_1);
        CPPUNIT_TEST(test_write_2);
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();
        
        void test_write_1();
        void test_write_2();
};

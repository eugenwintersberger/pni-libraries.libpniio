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
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <boost/current_function.hpp>
#include <functional>
#include <random>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace pni::core;
using namespace pni::io::nx;


/*!
\brief test for XML data operations

Test checks operations on XML node data. 
*/
class scalar_bool_attribute_fixture : public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(scalar_bool_attribute_fixture);
        CPPUNIT_TEST(test_bool);
        CPPUNIT_TEST(test_bool_t);
        CPPUNIT_TEST_SUITE_END();

        xml::node get_first(const string &s);
    public:
        void setUp();
        void tearDown();

        void test_bool();
        void test_bool_t();
        
};

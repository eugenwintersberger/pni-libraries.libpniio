//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Aor 29, 2015
//      Author: Eugen Wintersberger
//

#pragma once

#include <pni/io/formatters/formatter.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

using namespace pni::core;
using namespace pni::io;

class mdarray_formatter_test:public CppUnit::TestFixture 
{
        CPPUNIT_TEST_SUITE(mdarray_formatter_test);
        CPPUNIT_TEST(test_default);
        CPPUNIT_TEST(test_costum_sep);
        CPPUNIT_TEST(test_costum_start_stop);
        CPPUNIT_TEST(test_full_costum);
        CPPUNIT_TEST_SUITE_END();

        typedef dynamic_array<int16>  input_type; 
        typedef formatter<input_type>      formatter_type;        
        formatter_type format;
        input_type     input;

    public:
        void setUp();
        void tearDown();
        void test_default();
        void test_costum_sep();
        void test_costum_start_stop();
        void test_full_costum();
};



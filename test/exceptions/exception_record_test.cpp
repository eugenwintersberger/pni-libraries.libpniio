//
// (c) Copyright <2017> DESY
//
// This file is part of pninexus.
//
// pninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pninexus.  If not, see <http://www.gnu.org/licenses/>.
// 
// ===========================================================================
//
// Created: Mon 22 May, 2017
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include "../boost_unit_test.hpp"

#include <pni/error.hpp>
using namespace pni;

BOOST_AUTO_TEST_SUITE(exceptions_record_test)

    BOOST_AUTO_TEST_CASE(manual_creation)
    {
        exception_record record("test.cpp",100,"void function(int)");

        BOOST_CHECK_EQUAL(record.file(),"test.cpp");
        BOOST_CHECK_EQUAL(record.line(),100);
        BOOST_CHECK_EQUAL(record.function(),"void function(int)");
    }

    BOOST_AUTO_TEST_CASE(macro_reation)
    {
        exception_record record = EXCEPTION_RECORD;
        BOOST_CHECK_EQUAL(record.line(),42);
    }

BOOST_AUTO_TEST_SUITE_END()

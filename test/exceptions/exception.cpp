//
// (c) Copyright 2017 DESY
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
#include <boost/test/unit_test.hpp>

#include <pni/error.hpp>

using namespace pni;

BOOST_AUTO_TEST_SUITE(exception_test)
    
    BOOST_AUTO_TEST_CASE(default_construction)
    {
        exception e;
        BOOST_CHECK_EQUAL(e.name(),"");
        BOOST_CHECK_EQUAL(e.description(),"");
        BOOST_CHECK_EQUAL(e.size(),0);
    }

    BOOST_AUTO_TEST_CASE(name_construction)
    {
        exception e("test_error");
        BOOST_CHECK_EQUAL(e.name(),"test_error");
        BOOST_CHECK_EQUAL(e.description(),"");
        BOOST_CHECK_EQUAL(e.size(),0);
    }

    BOOST_AUTO_TEST_CASE(record_construction)
    {
        exception_record r("test.cpp",100,"int function()");
        exception e("test_error",r);
        BOOST_CHECK_EQUAL(e.name(),"test_error");
        BOOST_CHECK_EQUAL(e.description(),"");
        BOOST_CHECK_EQUAL(e.size(),1);
    }

BOOST_AUTO_TEST_SUITE_END()

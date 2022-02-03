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
#include "../boost_unit_test.hpp"
#include <sstream>
#include <pni/error.hpp>

using namespace pni;

void function1()
{
    throw exception("test_error",EXCEPTION_RECORD,"single throw test");
}

void function2()
{

    try
    {
        function1();
    }
    catch(exception &error)
    {
        error.push_back(EXCEPTION_RECORD);
        throw error;
    }
}

BOOST_AUTO_TEST_SUITE(exception_test)
    
    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(default_construction)
    {
        BOOST_TEST_MESSAGE("Default construction ...");
        exception e;
        BOOST_CHECK_EQUAL(e.name(),"");
        BOOST_CHECK_EQUAL(e.description(),"");
        BOOST_CHECK_EQUAL(e.size(),0);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(name_construction)
    {
        BOOST_TEST_MESSAGE("Construction from name ...");
        exception e("test_error");
        BOOST_CHECK_EQUAL(e.name(),"test_error");
        BOOST_CHECK_EQUAL(e.description(),"");
        BOOST_CHECK_EQUAL(e.size(),0);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(record_construction)
    {
        BOOST_TEST_MESSAGE("Construction from record ...");
        exception_record r("test.cpp",100,"int function()");
        exception e("test_error",r);
        BOOST_CHECK_EQUAL(e.name(),"test_error");
        BOOST_CHECK_EQUAL(e.description(),"");
        BOOST_CHECK_EQUAL(e.size(),1);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(single_throw)
    {
        BOOST_TEST_MESSAGE("Single throw ...");
        try
        {
            function1();
        }
        catch(const exception &error)
        {
            BOOST_TEST_MESSAGE("Single exception thrown - testing results...");
            BOOST_CHECK_EQUAL(error.name(),"test_error");
            BOOST_CHECK_EQUAL(error.description(),"single throw test");
            BOOST_CHECK_EQUAL(error.size(),1);

            for(auto record: error)
            {
                BOOST_CHECK_EQUAL(record.line(),32);
                std::stringstream ss;
                ss<<"Record: "<<record;
                BOOST_TEST_MESSAGE(ss.str());
            }
        }
        catch(...)
        {
            BOOST_CHECK(false);
        }

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(exception_forward)
    {
        BOOST_TEST_MESSAGE("Double throw ...");
        try
        {
            function2();
        }
        catch(const exception &error)
        {
            BOOST_TEST_MESSAGE(" - testing results...");
            BOOST_CHECK_EQUAL(error.name(),"test_error");
            BOOST_CHECK_EQUAL(error.description(),"single throw test");
            BOOST_CHECK_EQUAL(error.size(),2);
            
            for(auto record: error)
            {
                std::stringstream ss;
                ss<<"Record: "<<record;
                BOOST_TEST_MESSAGE(ss.str());
            }
        }

    }

BOOST_AUTO_TEST_SUITE_END()

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
// Created: Tue 23 May, 2017
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <boost/test/unit_test.hpp>
#include <sstream>
#include <pni/error.hpp>

using namespace pni;

BOOST_AUTO_TEST_SUITE(shape_mismatch_error_test)

    
    BOOST_AUTO_TEST_CASE(default_construction)
    {
        shape_mismatch_error error;
        BOOST_CHECK_EQUAL(error.name(),"shape_mismatch_error");
        BOOST_CHECK_EQUAL(error.size(),0);
        BOOST_CHECK_EQUAL(error.description(),"");
    }

    BOOST_AUTO_TEST_CASE(record_construction)
    {
        shape_mismatch_error error(PNINEXUS_EXCEPTION_RECORD,"test error");
        BOOST_CHECK_EQUAL(error.name(),"shape_mismatch_error");
        BOOST_CHECK_EQUAL(error.size(),1);
        BOOST_CHECK_EQUAL(error.description(),"test error");
    }

    BOOST_AUTO_TEST_CASE(output_stream)
    {
        shape_mismatch_error error(PNINEXUS_EXCEPTION_RECORD,"test error");
        std::stringstream stream;
        stream<<error<<std::endl;
        BOOST_TEST_MESSAGE(stream.str());
    }

BOOST_AUTO_TEST_SUITE_END()

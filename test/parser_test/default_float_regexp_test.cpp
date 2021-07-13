//
// (c) Copyright 2017 DESY
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
// Created on: Jun 7, 2017
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#include <boost/test/unit_test.hpp>
#include <pni/parsers/parser.hpp>

using namespace pni::core;
using namespace pni::io;

BOOST_AUTO_TEST_SUITE(default_float_regexp_test)

    BOOST_AUTO_TEST_CASE(test_no_exponent)
    {
        BOOST_CHECK(boost::regex_match("123.3",default_float_regexp));
        BOOST_CHECK(boost::regex_match("-1.23455",default_float_regexp));
        BOOST_CHECK(boost::regex_match("+23345.2134",default_float_regexp));
        BOOST_CHECK(boost::regex_match("1234.",default_float_regexp));
        BOOST_CHECK(boost::regex_match("-12344.",default_float_regexp));
        BOOST_CHECK(boost::regex_match("+1234.",default_float_regexp));
    }

    BOOST_AUTO_TEST_CASE(test_with_exponent)
    {
        BOOST_CHECK(boost::regex_match("1.23e+3",default_float_regexp));
        BOOST_CHECK(boost::regex_match("12.342e-34",default_float_regexp));
        BOOST_CHECK(boost::regex_match("1232.e+23",default_float_regexp));
        BOOST_CHECK(boost::regex_match("09384.e-12",default_float_regexp));
    }

    BOOST_AUTO_TEST_CASE(test_with_invalid_exponent)
    {
        BOOST_CHECK(!boost::regex_match("1.2a+2",default_float_regexp));
        BOOST_CHECK(!boost::regex_match("-14.B-3",default_float_regexp));
        BOOST_CHECK(!boost::regex_match("1.234e+-3",default_float_regexp));
        BOOST_CHECK(!boost::regex_match("+23435.21324e-3a",default_float_regexp));
    }

    BOOST_AUTO_TEST_CASE(test_invalid_sign)
    {
        BOOST_CHECK(!boost::regex_match("+-1234.",default_float_regexp));
        BOOST_CHECK(!boost::regex_match("-+1290984.234",default_float_regexp));
    }

BOOST_AUTO_TEST_SUITE_END()

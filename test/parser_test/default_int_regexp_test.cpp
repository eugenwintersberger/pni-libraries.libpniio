//
// (c) Copyright 2017 DESY
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Jun 7, 2017
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#include <boost/test/unit_test.hpp>
#include <pni/parsers/parser.hpp>

using namespace pni;

BOOST_AUTO_TEST_SUITE(default_int_regexp_test)

    BOOST_AUTO_TEST_CASE(test_with_leading_sign)
    {
        BOOST_CHECK(boost::regex_match("+123",default_int_regexp));
        BOOST_CHECK(boost::regex_match("-3243",default_int_regexp));
    }

    BOOST_AUTO_TEST_CASE(test_without_leading_sign)
    {
        BOOST_CHECK(boost::regex_match("124",default_int_regexp));
        BOOST_CHECK(boost::regex_match("2345562",default_int_regexp));
    }

    BOOST_AUTO_TEST_CASE(test_float)
    {
        BOOST_CHECK(!boost::regex_match("12343.",default_int_regexp));
        BOOST_CHECK(!boost::regex_match("-1234.23",default_int_regexp));
    }

    BOOST_AUTO_TEST_CASE(test_invalid_sign)
    {
        BOOST_CHECK(!boost::regex_match("+-1234",default_int_regexp));
    }

BOOST_AUTO_TEST_SUITE_END()

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
//  Created on: Jan 28, 2015
//      Author: Eugen Wintersberger
//
#include <boost/test/unit_test.hpp>
#include <pni/parsers.hpp>
#include <pni/exceptions.hpp>
#include <pni/core/types.hpp>
#include "parser_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io;

struct float128_parser_test_fixture : parser_test_fixture<float128>
{};

BOOST_FIXTURE_TEST_SUITE(float128_parser_test,float128_parser_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_regular_value)
    {
        BOOST_CHECK_CLOSE_FRACTION(12,p("12"),1.e-8);
        BOOST_CHECK_CLOSE_FRACTION(-1.234e+4,p("-1.234e+4"),1.e-8);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_invalid_input)
    {
        BOOST_CHECK_THROW(p("1.ab"),parser_error);
        BOOST_CHECK_THROW(p(" 1."),parser_error);
        BOOST_CHECK_THROW(p("1. "),parser_error);
        BOOST_CHECK_THROW(p("x1."),parser_error);
        BOOST_CHECK_THROW(p("-1x."),parser_error);
        BOOST_CHECK_THROW(p("1.ex"),parser_error);
        BOOST_CHECK_THROW(p("1.e-1x"),parser_error);
    }

BOOST_AUTO_TEST_SUITE_END()

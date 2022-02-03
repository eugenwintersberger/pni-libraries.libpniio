//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jan 21, 2015
//      Author: Eugen Wintersberger
//

#include "../../boost_unit_test.hpp"
#include <pni/parsers.hpp>
#include <pni/types.hpp>
#include "parser_test_fixture.hpp"

using namespace pni;

struct uint16_parser_test_fixture : parser_test_fixture<uint16>
{};

BOOST_FIXTURE_TEST_SUITE(uint16_parser_test,uint16_parser_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_regular_value)
    {
        BOOST_CHECK(p("12") == 12);
        BOOST_CHECK(p("0") ==  0);
        BOOST_CHECK(p("04") == 4);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_invalid_input)
    {
        BOOST_CHECK_THROW(p("x10"),parser_error);
        BOOST_CHECK_THROW(p("0z10"),parser_error);
        BOOST_CHECK_THROW(p("10l"),parser_error);
    }

BOOST_AUTO_TEST_SUITE_END()

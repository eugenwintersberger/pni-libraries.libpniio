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
//  Created on: Jan 20, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/included/unit_test.hpp>
#include "../primitive_parsers/parser_test_fixture.hpp"
#include <pni/parsers.hpp>
#include <pni/types.hpp>
#include <pni/container_io_config.hpp>

using namespace pni;

struct vector_parser_test_fixture : parser_test_fixture<std::vector<uint8>>
{};

BOOST_FIXTURE_TEST_SUITE(vector_parser_test,vector_parser_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_default)
    {
        auto result = p("1 2 3 4 5");

        BOOST_CHECK(result.size() == 5);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_simple)
    {
        p = parser_type(container_io_config('[',']',','));
        auto result = p("[1,2,3,4,5]");
        BOOST_CHECK(result.size() == 5);
    }

    //--------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_overflow)
    {
        p=parser_type(container_io_config('[',']',','));
        BOOST_CHECK_THROW(p("[10,-20,10]"),parser_error);
    }

BOOST_AUTO_TEST_SUITE_END()

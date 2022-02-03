//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: May 06, 2013
//      Author: Eugen Wintersberger
//

#include <boost/test/included/unit_test.hpp>
#include "../primitive_parsers/parser_test_fixture.hpp"
#include <pni/types.hpp>
#include <pni/arrays/slice.hpp>

using namespace pni;

struct slice_parser_test_fixture : parser_test_fixture<slice>
{
};

BOOST_FIXTURE_TEST_SUITE(slice_parser_test,slice_parser_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_full_parser)
    {
        string s1 = "1:10";
        string s2 = "10:100:2";
        string s3 = "5";

        slice s = p(s1);
        BOOST_CHECK(s.first() == 1);
        BOOST_CHECK(s.last() == 10);
        BOOST_CHECK(s.stride() == 1);

        s = p(s2);
        BOOST_CHECK(s.first() == 10);
        BOOST_CHECK(s.last()  == 100);
        BOOST_CHECK(s.stride() == 2);
        
        s = p(s3);
        BOOST_CHECK(s.first() == 5);
        BOOST_CHECK(s.last()  == 6);
        BOOST_CHECK(s.stride() == 1);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_half_parser)
    {
        string s1 = ":100";
        string s2 = ":200:3";
        
        slice s = p(s1);
        BOOST_CHECK(s.first() == 0);
        BOOST_CHECK(s.last()  == 100);
        BOOST_CHECK(s.stride() == 1);

        s = p(s2);
        BOOST_CHECK(s.first() == 0);
        BOOST_CHECK(s.last()  == 200);
        BOOST_CHECK(s.stride() == 3);
    }

BOOST_AUTO_TEST_SUITE_END()

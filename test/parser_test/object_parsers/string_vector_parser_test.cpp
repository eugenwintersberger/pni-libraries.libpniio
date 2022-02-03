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
//  Created on: Feb 2, 2015
//      Author: Eugen Wintersberger
//
#include "../../boost_unit_test.hpp"
#include <vector>
#include <pni/types.hpp>
#include <pni/container_io_config.hpp>
#include "../primitive_parsers/parser_test_fixture.hpp"

using namespace pni;

struct string_vector_parser_test_fixture : parser_test_fixture<std::vector<string>>
{
    result_type ref;
};


BOOST_FIXTURE_TEST_SUITE(string_vector_parser_test,string_vector_parser_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_default)
    {
        auto result = p("hello   this bla test  word");
        BOOST_CHECK(result.size() == 5);
        ref = {"hello","this","bla","test","word"};
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_start_stop)
    {
        p = parser_type(container_io_config('(',')'));
        auto result = p("(true false    false true true)");

        BOOST_CHECK(result.size() == 5);
        ref = {"true","false","false","true","true"};
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_delimiter)
    {
        p = parser_type(container_io_config(';'));
        auto result = p(" true;false ;true; true ; false   ");
        BOOST_CHECK(result.size() == 5);

        ref = {"true","false","true","true","false"};
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_full)
    {
        p = parser_type(container_io_config('[',']',','));
        auto result = p("[ hello world , this  ,is some, stupid  ,  text!  ]");
        BOOST_CHECK(result.size() == 5);

        ref = {"hello world","this","is some","stupid","text!"};
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

BOOST_AUTO_TEST_SUITE_END()


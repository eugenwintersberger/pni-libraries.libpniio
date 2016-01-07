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
//  Created on: Jan 30, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <vector>
#include <pni/core/types.hpp>
#include <pni/io/container_io_config.hpp>
#include "../primitive_parsers/parser_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io;

struct int8_vector_parser_test_fixture : parser_test_fixture<std::vector<int8>>
{
    static const result_type ref;
};

const int8_vector_parser_test_fixture::result_type 
      int8_vector_parser_test_fixture::ref = {1,2,-3,4,-5};

BOOST_FIXTURE_TEST_SUITE(int8_vector_parser_test,int8_vector_parser_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_default)
    {
        auto result = p("1 2 -3 4 -5");

        BOOST_CHECK_EQUAL(result.size(),5);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());

        result = p("  1  2    -3  4   -5   ");
        BOOST_CHECK_EQUAL(result.size(),5);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_start_stop)
    {
        p = parser_type(container_io_config('(',')'));
        auto result = p("( 1 2 -3 4  -5   )");
        BOOST_CHECK_EQUAL(result.size(),5);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());

        result = p("(1 2 -3 4 -5)");
        BOOST_CHECK_EQUAL(result.size(),5);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_delimiter)
    {
        p = parser_type(container_io_config(';'));
        auto result = p("1;2;-3;4;-5");
        BOOST_CHECK_EQUAL(result.size(),5);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
        
        result = p("  1; 2 ;-3   ;  4; -5  ");
        BOOST_CHECK_EQUAL(result.size(),5);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_full)
    {
        p = parser_type(container_io_config('[',']',','));
        auto result = p("[1,2,-3,4,-5]");
        BOOST_CHECK_EQUAL(result.size(),5);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());

        result = p("[  1, 2,  -3  , 4,  -5  ]");
        BOOST_CHECK_EQUAL(result.size(),5);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

BOOST_AUTO_TEST_SUITE_END()


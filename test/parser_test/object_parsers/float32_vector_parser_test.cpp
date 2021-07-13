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
//  Created on: Feb 4, 2015
//      Author: Eugen Wintersberger
//
#include <boost/test/unit_test.hpp>
#include <vector>
#include <pni/core/types.hpp>
#include <pni/container_io_config.hpp>
#include "../primitive_parsers/parser_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io;

struct float32_vector_parser_test_fixture : parser_test_fixture<std::vector<float32>>
{
    static const result_type ref;
};

const float32_vector_parser_test_fixture::result_type
      float32_vector_parser_test_fixture::ref = {1.2f,3e+3f,-3.4f,4.429f,
                                                 -5.34e-3f};


BOOST_FIXTURE_TEST_SUITE(float32_vector_parser_test,float32_vector_parser_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_default)
    {
        auto result = p("1.2 3.e+3 -3.4 4.429 -5.34e-3");

        BOOST_CHECK(result.size() == 5);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());

        result = p("  1.2  3.e+3    -3.4  4.429   -5.34e-3   ");
        BOOST_CHECK(result.size() == 5);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_start_stop)
    {
        p = parser_type(container_io_config('(',')'));
        auto result = p("( 1.2 3.e3 -3.4 4.429  -5.34e-3   )");
        BOOST_CHECK(result.size() == 5);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());

        result = p("(1.2 3e+3 -3.4 4.429 -5.34e-3)");
        BOOST_CHECK(result.size() == 5);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_delimiter)
    {
        p = parser_type(container_io_config(';'));
        auto result = p("1.2;3.e3;-3.4;4.429;-5.34e-3");
        BOOST_CHECK(result.size() == 5);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());

        result = p("  1.2; 3.e+3 ;-3.4   ;  4.429; -5.34e-3  ");
        BOOST_CHECK(result.size() == 5);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_full)
    {
        p = parser_type(container_io_config('[',']',','));
        auto result = p("[1.2,3.e+3,-3.4,4.429,-5.34e-3]");
        BOOST_CHECK(result.size() == 5);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());

        result = p("[  1.2, 3.e+3,  -3.4  , 4.429,  -5.34e-3  ]");
        BOOST_CHECK(result.size() == 5);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

BOOST_AUTO_TEST_SUITE_END()

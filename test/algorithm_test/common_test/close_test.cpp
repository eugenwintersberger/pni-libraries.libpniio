//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jun 03, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/algorithms/close.hpp>
#include <pni/io/nx/algorithms/is_valid.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include "../algorithm_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct close_test_fixture : algorithm_test_fixture
{
    close_test_fixture():
        algorithm_test_fixture("close_test.nx")
    {}
};


BOOST_FIXTURE_TEST_SUITE(close_test,close_test_fixture)


    BOOST_AUTO_TEST_CASE(test_group)
    {
        BOOST_CHECK(is_valid(group));
        close(group);
        BOOST_CHECK(!is_valid(group));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {
        BOOST_CHECK(is_valid(field));
        close(field);
        BOOST_CHECK(!is_valid(field));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        BOOST_CHECK(is_valid(attribute));
        close(attribute);
        BOOST_CHECK(!is_valid(attribute));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_visitor_group)
    {
        BOOST_CHECK(is_valid(o_group));
        close(o_group);
        BOOST_CHECK(!is_valid(o_group));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_visitor_field)
    {
        BOOST_CHECK(is_valid(o_field));
        close(o_field);
        BOOST_CHECK(!is_valid(o_field)); 
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_visitor_attribute)
    {
        BOOST_CHECK(is_valid(o_attribute));
        close(o_attribute);
        BOOST_CHECK(!is_valid(o_attribute));
    }

BOOST_AUTO_TEST_SUITE_END()


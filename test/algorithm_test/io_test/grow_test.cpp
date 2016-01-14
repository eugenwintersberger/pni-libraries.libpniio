//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jul 5, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/algorithms/grow.hpp>
#include <pni/io/nx/algorithms/get_shape.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include "io_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct grow_test_fixture : io_test_fixture
{
    grow_test_fixture():
        io_test_fixture("grow_test.nx")
    {}
};

BOOST_FIXTURE_TEST_SUITE(grow_test,grow_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        BOOST_CHECK_THROW(grow(o_group),type_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {
        auto s = get_shape<shape_t>(o_mdim_field);
        BOOST_CHECK_EQUAL(s[0],3);
        BOOST_CHECK_NO_THROW(grow(o_mdim_field));
        s = get_shape<shape_t>(o_mdim_field);
        BOOST_CHECK_EQUAL(s[0],4);
        BOOST_CHECK_NO_THROW(grow(o_mdim_field,1,10));
        s = get_shape<shape_t>(o_mdim_field);
        BOOST_CHECK_EQUAL(s[1],14);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        BOOST_CHECK_THROW(grow(o_mdim_attribute),type_error);
        BOOST_CHECK_THROW(grow(o_scalar_attribute),type_error);
    }

BOOST_AUTO_TEST_SUITE_END()

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
//  Created on: Jul 3, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <boost/test/unit_test.hpp>
#include <pni/io/nx/algorithms/get_shape.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include "io_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct get_shape_test_fixture : io_test_fixture
{
    get_shape_test_fixture():
        io_test_fixture("get_shape_test.nx")
    {}
};

BOOST_FIXTURE_TEST_SUITE(get_shape_test,get_shape_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        BOOST_CHECK_THROW(get_shape<shape_t>(o_group),type_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_mdim_field)
    {
        auto so = get_shape<shape_t>(o_mdim_field);
        auto s  = get_shape<shape_t>(mdim_field);

        BOOST_CHECK_EQUAL_COLLECTIONS(shape.begin(),shape.end(),
                                      so.begin(),so.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(shape.begin(),shape.end(),
                                      s.begin(),s.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_scalar_field)
    {
        shape_t s_ref{1};

        auto so = get_shape<shape_t>(o_scalar_field);
        auto s  = get_shape<shape_t>(scalar_field);
        BOOST_CHECK_EQUAL_COLLECTIONS(s_ref.begin(),s_ref.end(),
                                      so.begin(),so.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(s_ref.begin(),s_ref.end(),
                                      s.begin(),s.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_mdim_attribute)
    {
        auto so = get_shape<shape_t>(o_mdim_attribute);
        auto s  = get_shape<shape_t>(mdim_attribute);

        BOOST_CHECK_EQUAL_COLLECTIONS(shape.begin(),shape.end(),
                                      so.begin(),so.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(shape.begin(),shape.end(),
                                      s.begin(),s.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_scalar_attribute)
    {
        shape_t s_ref;

        auto so = get_shape<shape_t>(o_scalar_attribute);
        auto s  = get_shape<shape_t>(scalar_attribute);
        BOOST_CHECK_EQUAL_COLLECTIONS(s_ref.begin(),s_ref.end(),
                                      so.begin(),so.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(s_ref.begin(),s_ref.end(),
                                      s.begin(),s.end());
    }

BOOST_AUTO_TEST_SUITE_END()

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
//  Created on: Jun 28, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/algorithms/is_field.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include "inquiry_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct is_field_test_fixture : inquiry_test_fixture
{
    is_field_test_fixture():
        inquiry_test_fixture("is_field_test.nxs")
    {}
};

BOOST_FIXTURE_TEST_SUITE(is_field_test,is_field_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        BOOST_CHECK(!is_field(group));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {
        BOOST_CHECK(is_field(field)); 
    }

    //------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        BOOST_CHECK(!is_field(attribute));
    }

BOOST_AUTO_TEST_SUITE_END()


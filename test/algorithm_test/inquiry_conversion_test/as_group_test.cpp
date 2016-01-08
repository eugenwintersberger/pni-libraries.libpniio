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
#include <pni/io/nx/algorithms/as_group.hpp>
#include "../algorithm_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct as_group_test_fixture : algorithm_test_fixture
{
    as_group_test_fixture():
        algorithm_test_fixture("as_group_test.nx")
    {}
};

BOOST_FIXTURE_TEST_SUITE(as_group_test,as_group_test_fixture)


    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        h5::nxgroup g;
        //must work - the stored object is an instance of nxgroup
        BOOST_CHECK_NO_THROW(g = as_group(o_group));
        BOOST_CHECK(g.is_valid());
        BOOST_CHECK_EQUAL(g.name(),"/");
        string c;
        g.attributes["NX_class"].read(c);
        BOOST_CHECK_EQUAL(c,"NXroot");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {
        BOOST_CHECK_THROW(as_group(o_field),type_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        BOOST_CHECK_THROW(as_group(o_attribute),type_error);
    }

BOOST_AUTO_TEST_SUITE_END()

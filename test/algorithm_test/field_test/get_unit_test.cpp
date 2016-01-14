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
#include <pni/io/nx/algorithms/get_unit.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include "../algorithm_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;
using pni::io::invalid_object_error;

struct get_unit_test_fixture : algorithm_test_fixture
{
    get_unit_test_fixture():
        algorithm_test_fixture("get_unit_test.nx")
    {
        h5::nxattribute a = field.attributes.create<string>("units");
        a.write("nm");
    }
};


BOOST_FIXTURE_TEST_SUITE(get_unit_test,get_unit_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        BOOST_CHECK_THROW(get_unit(o_group),type_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {
        BOOST_CHECK_EQUAL(get_unit(field),"nm");
        BOOST_CHECK_EQUAL(get_unit(o_field),"nm");

        BOOST_CHECK_THROW(get_unit(h5::nxfield()),invalid_object_error);
        BOOST_CHECK_THROW(get_unit(h5::nxobject(h5::nxfield())),
                             invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        BOOST_CHECK_THROW(get_unit(o_attribute),type_error);
    }

BOOST_AUTO_TEST_SUITE_END()

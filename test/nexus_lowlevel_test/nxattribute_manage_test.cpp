//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include "test_types.hpp"
#include "nxattribute_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct nxattribute_manage_test_fixture : nxattribute_test_fixture
{
    nxattribute_manage_test_fixture():
        nxattribute_test_fixture("nxattribute_manage_test.nxs")
    {}
};

BOOST_FIXTURE_TEST_SUITE(nxattribute_manage_test,nxattribute_manage_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_exists)
    {
        BOOST_CHECK(!group.attributes.exists("bla"));
        BOOST_CHECK_NO_THROW(group.attributes.create<string>("bla"));
        BOOST_CHECK(group.attributes.exists("bla"));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_remove)
    {
        BOOST_CHECK_NO_THROW(group.attributes.create<string>("bla"));
        BOOST_CHECK(group.attributes.exists("bla"));
        BOOST_CHECK_NO_THROW(group.attributes.remove("bla"));
        BOOST_CHECK(!group.attributes.exists("bla"));
        BOOST_CHECK_THROW(root.attributes.remove("bla"),key_error);

    }

BOOST_AUTO_TEST_SUITE_END()



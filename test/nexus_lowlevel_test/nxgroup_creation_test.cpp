//
// Declaration of Nexus object template.
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
//  Created on: Aug 4, 2011
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxobject_type.hpp>
#include <pni/io/nx/algorithms.hpp>
#include <pni/io/exceptions.hpp>
#include "base_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;
using pni::io::invalid_object_error;
using pni::io::object_error;

struct nxgroup_creation_test_fixture : base_fixture
{
    nxgroup_creation_test_fixture():
        base_fixture("nxgroup_creation_test.nxs")
    {}
};

BOOST_FIXTURE_TEST_SUITE(nxgroup_creation_test,nxgroup_creation_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_simple)
    {
        h5::nxgroup g;

        BOOST_CHECK_NO_THROW( g = root.create_group("test"));
        BOOST_CHECK(g.is_valid());
        BOOST_CHECK_EQUAL(g.name(),"test");

        //throw an exception if the group already exists
        BOOST_CHECK_THROW(root.create_group("test"),object_error);
        BOOST_CHECK_THROW(root.create_group("test2/data"),object_error);

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_with_class)
    {
        h5::nxgroup g;
        BOOST_CHECK_NO_THROW(g = root.create_group("test","NXentry"));
        BOOST_CHECK(g.is_valid());
        BOOST_CHECK_EQUAL(g.name(),"test");
        BOOST_CHECK_EQUAL(get_class(g),"NXentry");
       
        BOOST_CHECK_THROW(root.create_group("test","NXinstrument"),object_error);
        BOOST_CHECK_THROW(root.create_group("test2/data","NXdata"),object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_copy_construction)
    {
        h5::nxgroup g;
        g = root.create_group("test");
        h5::nxgroup g2 = g;
        BOOST_CHECK(g.is_valid());
        BOOST_CHECK(g2.is_valid());

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_move_construction)
    {
        h5::nxgroup g;
        g = root.create_group("test");
        h5::nxgroup g2 = std::move(g);
        BOOST_CHECK(!g.is_valid());
        BOOST_CHECK(g2.is_valid());
    }

BOOST_AUTO_TEST_SUITE_END()



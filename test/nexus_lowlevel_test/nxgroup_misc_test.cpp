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
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxobject_type.hpp>
#include <pni/io/nx/algorithms.hpp>
#include <pni/io/exceptions.hpp>
#include "../base_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

using pni::io::invalid_object_error;

struct nxgroup_misc_test_fixture : base_fixture
{
    h5::nxgroup child;
    h5::nxgroup child2;

    nxgroup_misc_test_fixture():
	    base_fixture("nxgroupmisctest.nxs"),
        child(root.create_group("entry","NXentry")),
        child2(child.create_group("instrument","NXinstrument"))
    {}

    ~nxgroup_misc_test_fixture()
    {
        child.close();
        child2.close();
    }
};

BOOST_FIXTURE_TEST_SUITE(nxgroup_misc_test,nxgroup_misc_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_size)
    {
        BOOST_CHECK_EQUAL(root.size(),1);
        BOOST_CHECK_EQUAL(child.size(),1);
        BOOST_CHECK_EQUAL(child2.size(),0);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_name)
    {
        BOOST_CHECK_EQUAL(root.name(),"/");
        BOOST_CHECK_EQUAL(child.name(),"entry");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_filename)
    {
        BOOST_CHECK_EQUAL(root.filename(),filename);
        BOOST_CHECK_EQUAL(child.filename(),filename);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_parent)
    {
        BOOST_CHECK_EQUAL(h5::nxgroup(root.parent()).name(),"/");
        BOOST_CHECK_EQUAL(h5::nxgroup(child.parent()).name(),"/");
        BOOST_CHECK_EQUAL(h5::nxgroup(child2.parent()).name(),"entry");
    }

BOOST_AUTO_TEST_SUITE_END()

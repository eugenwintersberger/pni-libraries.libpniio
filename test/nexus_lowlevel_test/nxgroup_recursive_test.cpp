//
// Declaration of Nexus object template.
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
//  Created on: Sep 10, 2014
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/flat_group.hpp>
#include <pni/io/nx/nxobject_type.hpp>
#include <pni/io/nx/algorithms.hpp>
#include <pni/io/exceptions.hpp>

#include "../base_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

using pni::io::invalid_object_error;

struct nxgroup_recursive_test_fixture : base_fixture
{
    nxgroup_recursive_test_fixture():
        base_fixture("nxgroup_recursive_test.nxs")
    {
        h5::nxgroup g=root;
        g = g.create_group("entry","NXentry");
        g.create_group("sample","NXsample");
        g.create_group("control","NXmonitor");
        g = g.create_group("instrument","NXinstrument");
        g.create_group("detector","NXdetector");
        g.create_group("machine","NXsource");
        g.create_group("unudlator","NXinsertion_device");
        g.create_group("monochromator","NXmonochromator");
    }
};

BOOST_FIXTURE_TEST_SUITE(nxgroup_recursive_test,nxgroup_recursive_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_creation)
    {
        //construct from a group type
        auto fgroup = make_flat(root);
        BOOST_CHECK_EQUAL(fgroup.size(),8);
        BOOST_CHECK_THROW(make_flat(h5::nxgroup()),invalid_object_error);

        //construct from an object 
        fgroup = make_flat(get_object(root,"entry:NXentry"));
        BOOST_CHECK_EQUAL(fgroup.size(),7);

        BOOST_CHECK_THROW(make_flat(h5::nxobject(h5::nxgroup())),
                           invalid_object_error);
    }

BOOST_AUTO_TEST_SUITE_END()


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
#include "../base_fixture.hpp"
#include <pni/io/nx/nxlink.hpp>

using namespace pni::core;
using namespace pni::io::nx;
using pni::io::invalid_object_error;


struct nxgroup_access_test_fixture : base_fixture
{
    h5::nxgroup child;
    nxgroup_access_test_fixture():
	    base_fixture("nxgroup_access_test.nxs"),
        child(root.create_group("entry","NXentry"))
    {
        child.create_group("instrument","NXinstrument");
        child.create_group("data","NXdata");
        link("/entry/data/data",child,"data_link");
        
    }

    ~nxgroup_access_test_fixture()
    {
        child.close();
    }

};

BOOST_FIXTURE_TEST_SUITE(nxgroup_access_test,nxgroup_access_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_operator_index)
    {
        BOOST_CHECK_EQUAL(root.size(),1);

        h5::nxgroup g = root[0];
        BOOST_CHECK_EQUAL(g.name(),"entry");
        BOOST_CHECK_THROW(root[1],index_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_operator_name)
    {
        BOOST_CHECK_EQUAL(root.size(),1);

        h5::nxgroup g = root["entry"];
        BOOST_CHECK_EQUAL(g.name(),"entry");
        BOOST_CHECK_THROW(root["nothing"],key_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_at_index)
    {
        h5::nxgroup g = root.at(0);
        BOOST_CHECK_EQUAL(g.name(),"entry");
        BOOST_CHECK_THROW(root.at(1),index_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_at_name)
    {
        h5::nxgroup g = root.at("entry");
        BOOST_CHECK_EQUAL(g.name(),"entry");
        
        BOOST_CHECK_THROW(root.at("nothing"),key_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_link)
    {
        auto l = child["data_link"];
        BOOST_CHECK(is_link(l));
        h5::nxlink li = as_link(l);
        BOOST_CHECK_EQUAL(li.name(),"data_link");
        BOOST_CHECK_EQUAL(li.status(),nxlink_status::INVALID);
    }

BOOST_AUTO_TEST_SUITE_END()

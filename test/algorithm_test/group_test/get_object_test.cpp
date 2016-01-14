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
#include <pni/io/nx/algorithms/get_object.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include "../algorithm_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct get_object_test_fixture : algorithm_test_fixture
{
    
    get_object_test_fixture():
        algorithm_test_fixture("get_object_test.nx")
    {
        h5::nxgroup g = group.create_group("group","NXentry");
        g = g.create_group("instrument","NXinstrument");
        g.create_group("source","NXsource");
        g.create_group("with.dot");
        g.create_group("without_dot");

        g = g.create_group("detector","NXdetector");
        g.create_field<uint32>("data",shape_t{0,1024,1024});
    }
};

BOOST_FIXTURE_TEST_SUITE(get_object_test,get_object_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_absolute)
    {
        h5::nxobject root_group = group;
        nxpath p = nxpath::from_string("/group/instrument/detector");

        auto o= get_object(root_group,p);
        BOOST_CHECK(is_valid(o));
        BOOST_CHECK(is_group(o));
        BOOST_CHECK_EQUAL(get_name(o),"detector");

        p = nxpath::from_string("/:NXentry/instrument/:NXdetector");
        BOOST_CHECK(is_valid(get_object(root_group,p)));
        BOOST_CHECK(is_group(get_object(root_group,p)));
        BOOST_CHECK_EQUAL(get_name(get_object(root_group,p)),"detector");

        p = nxpath::from_string("/:NXentry/instrument/:NXdetector@NX_class");
        BOOST_CHECK_EQUAL(get_name(get_object(root_group,p)),"NX_class");
        p = nxpath::from_string("/@NX_class");
        BOOST_CHECK_EQUAL(get_name(get_object(root_group,p)),"NX_class");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_relative_only)
    {
        auto o = get_object(group,"../");
        BOOST_CHECK(is_valid(o));
        BOOST_CHECK_EQUAL(get_name(o),"/");
        BOOST_CHECK_EQUAL(get_class(o),"NXroot");

        o = get_object(root,"/:NXentry/:NXinstrument/:NXdetector");
        o = get_object(o,"../../");
        BOOST_CHECK_EQUAL(get_name(o),"group");
        BOOST_CHECK_EQUAL(get_class(o),"NXentry");

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_relative)
    {
        nxpath p = nxpath::from_string("../instrument/detector");

        h5::nxobject ig = get_object(group,nxpath::from_string("group/instrument"));
        BOOST_CHECK_EQUAL(get_name(ig),"instrument");
        h5::nxobject d  = get_object(ig,p);
        BOOST_CHECK_EQUAL(get_name(d),"detector");

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_errors)
    {
        nxpath p = nxpath::from_string(":NXinstrument/:NXdetector/data");
        BOOST_CHECK_THROW(get_object(group,p),key_error);

        p = nxpath::from_string(":NXinstrument@hello");
        BOOST_CHECK_THROW(get_object(group,p),key_error);

        BOOST_CHECK_THROW(get_object(root,":NXentry/:NXinstrument/with.dot"),
                pni::io::parser_error);
        BOOST_CHECK_NO_THROW(get_object(group,":NXentry/:NXinstrument/without_dot"));
    }

BOOST_AUTO_TEST_SUITE_END()

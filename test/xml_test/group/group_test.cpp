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
//  Created on: Nov 26, 2014
//      Author: Eugen Wintersberger
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test XML group creation 

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml/group.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/algorithms/close.hpp>
#include <pni/io/nx/algorithms/is_valid.hpp>
#include <pni/io/nx/algorithms/get_name.hpp>
#include <pni/io/nx/algorithms/get_class.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "../../base_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct group_test_fixture :  base_fixture
{
    group_test_fixture():
        base_fixture("xml_group_test.nxs")
    {}
};

BOOST_FIXTURE_TEST_SUITE(group_test,group_test_fixture)


    //-------------------------------------------------------------------------
    xml::node get_xml_group(const string &fname)
    {
        xml::node root_node = xml::create_from_file(fname);
        return root_node.get_child("group");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_1)
    {
        xml::node child = get_xml_group("group1.xml");

        h5::nxobject g = xml::group::object_from_xml(h5::nxobject(root),child);
        BOOST_CHECK(is_valid(g));
        BOOST_CHECK_EQUAL(get_name(g),"hello");
        BOOST_CHECK_EQUAL(get_class(g),"NXentry");
        
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_2)
    {
        xml::node child = get_xml_group("group2.xml");

        h5::nxobject g = xml::group::object_from_xml(h5::nxobject(root),child);
        BOOST_CHECK(is_valid(g));
        BOOST_CHECK_EQUAL(get_name(g),"hello");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_3)
    {
        xml::node child = get_xml_group("group3.xml");

        h5::nxobject g;
        BOOST_CHECK_THROW(g = xml::group::object_from_xml(h5::nxobject(root),child),
                          pni::core::value_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_write_1)
    {
        h5::nxobject g = create_group(h5::nxobject(root),"hello");

        xml::node root_node;
        xml::node gnode = xml::group::object_to_xml(g);
        root_node.add_child("group",gnode);
        write_xml("test.xml",root_node);

        xml::node readback = xml::create_from_file("test.xml");
        BOOST_CHECK(readback == root_node);
    }

BOOST_AUTO_TEST_SUITE_END()

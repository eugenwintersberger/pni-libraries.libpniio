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
//  Created on: Apr 15, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <boost/current_function.hpp>
#include <pni/io/nx/xml/data_node.hpp>
#include <pni/core/types.hpp>

#include "data_node_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

static const string attr_scalar_xml = "<group attr1=\"12\" attr2=\" -12    \""
                                   "attr3=\"bla    \""
                                   "attr4=\"   12.3\""
                                   "attr5=\" 100000 \""
                                   "attr6=\"-1000000\"></group>";
static const string attr_array_xml = "<group attr1=\"12 23 34.2  34 23\""
                                         "attr2=\"       12 23 34.2  34 23 \">"
                                         "</group>";

struct attribute_node_fixture : data_node_fixture
{
    attribute_node_fixture():
        data_node_fixture(attr_scalar_xml,attr_array_xml)
    {}
        
}; 

BOOST_FIXTURE_TEST_SUITE(attribute_node_io_test,attribute_node_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_scalar)
    {
        xml::node root = scalar.get_child("group");
        xml::node attr;
        BOOST_CHECK_NO_THROW(attr = xml::get_attribute(root,"attr1"));
        BOOST_CHECK_EQUAL(xml::data_node::read(attr),"12");

        BOOST_CHECK_NO_THROW(attr = xml::get_attribute(root,"attr2"));
        BOOST_CHECK_EQUAL(xml::data_node::read(attr),"-12");

        BOOST_CHECK_NO_THROW(attr = xml::get_attribute(root,"attr3"));
        BOOST_CHECK_EQUAL(xml::data_node::read(attr),"bla");

        BOOST_CHECK_NO_THROW(attr = xml::get_attribute(root,"attr4"));
        BOOST_CHECK_EQUAL(xml::data_node::read(attr),"12.3");

        BOOST_CHECK_NO_THROW(attr = xml::get_attribute(root,"attr5"));
        BOOST_CHECK_EQUAL(xml::data_node::read(attr),"100000");

        BOOST_CHECK_NO_THROW(attr = xml::get_attribute(root,"attr6"));
        BOOST_CHECK_EQUAL(xml::data_node::read(attr),"-1000000");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_array)
    {
        xml::node root = array.get_child("group");
        xml::node attr;
        BOOST_CHECK_NO_THROW(attr = xml::get_attribute(root,"attr1"));
        BOOST_CHECK_EQUAL(xml::data_node::read(attr),"12 23 34.2  34 23");

        BOOST_CHECK_NO_THROW(attr = xml::get_attribute(root,"attr2"));
        BOOST_CHECK_EQUAL(xml::data_node::read(attr),"12 23 34.2  34 23");
    }


BOOST_AUTO_TEST_SUITE_END()

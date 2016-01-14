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
#include <pni/io/nx/xml/data_node.hpp>
#include <pni/core/types.hpp>

#include "data_node_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

static const string scalar_xml = "<group1>12</group1>"
                                 "<group2> -12    </group2>"
                                 "<group3>bla    </group3>"
                                 "<group4>   12.3</group4>"
                                 "<group5> 100000 </group5>"
                                 "<group6>-1000000</group6>";

static const string array_xml = "<group1> 12 23 34.2  34 23 </group1>"
                                "<group2> "
                                "       12 23 34.2  34 23  "
                                "</group2>";

struct child_node_fixture : data_node_fixture
{
    child_node_fixture():
        data_node_fixture(scalar_xml,array_xml)
    {}
};

BOOST_FIXTURE_TEST_SUITE(child_node_io_test,child_node_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_scalar)
    {
        using namespace pni::io::nx::xml;
        
        BOOST_CHECK_EQUAL(data_node::read(scalar.get_child("group1")),"12");
        BOOST_CHECK_EQUAL(data_node::read(scalar.get_child("group2")),"-12");
        BOOST_CHECK_EQUAL(data_node::read(scalar.get_child("group3")),"bla");
        BOOST_CHECK_EQUAL(data_node::read(scalar.get_child("group4")),"12.3");
        BOOST_CHECK_EQUAL(data_node::read(scalar.get_child("group5")),"100000");
        BOOST_CHECK_EQUAL(data_node::read(scalar.get_child("group6")),"-1000000");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_array)
    {
        using namespace pni::io::nx::xml;

        BOOST_CHECK_EQUAL(data_node::read(array.get_child("group1")),
                          "12 23 34.2  34 23");

        BOOST_CHECK_EQUAL(data_node::read(array.get_child("group2")),
                          "12 23 34.2  34 23");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_write_scalar)
    {
        using namespace pni::io::nx::xml;

        xml::node child;
        data_node::write(child,"1234");
        BOOST_CHECK_EQUAL(data_node::read(child),"1234");

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_write_array)
    {
        using namespace pni::io::nx::xml;

        xml::node child;
        data_node::write(child," 1 2    4 5 5  ");
        BOOST_CHECK_EQUAL(data_node::read(child),"1 2    4 5 5");

    }

BOOST_AUTO_TEST_SUITE_END()

//
// (c) Copyright 2017 DESY
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Dec 11, 2017
//
#include <boost/test/unit_test.hpp>

#include "data_node_fixture.hpp"

static const std::string scalar_xml = "<group1>12</group1>"
                                 "<group2> -12    </group2>"
                                 "<group3>bla    </group3>"
                                 "<group4>   12.3</group4>"
                                 "<group5> 100000 </group5>"
                                 "<group6>-1000000</group6>";

static const std::string array_xml = "<group1> 12 23 34.2  34 23 </group1>"
                                "<group2> "
                                "       12 23 34.2  34 23  "
                                "</group2>";

struct ChildNodeFixture : DataNodeFixture
{
    ChildNodeFixture():
        DataNodeFixture(scalar_xml,array_xml)
    {}
};

static const std::string attr_scalar_xml = "<group attr1=\"12\" attr2=\" -12    \""
                                   "attr3=\"bla    \""
                                   "attr4=\"   12.3\""
                                   "attr5=\" 100000 \""
                                   "attr6=\"-1000000\"></group>";
static const std::string attr_array_xml = "<group attr1=\"12 23 34.2  34 23\""
                                         "attr2=\"       12 23 34.2  34 23 \">"
                                         "</group>";

struct AttributeNodeFixture : DataNodeFixture
{
    AttributeNodeFixture():
        DataNodeFixture(attr_scalar_xml,attr_array_xml)
    {}

};


BOOST_AUTO_TEST_SUITE(NexusXMLTest)

BOOST_AUTO_TEST_SUITE(DataNodeTest)

BOOST_FIXTURE_TEST_SUITE(ChildNodeTest,ChildNodeFixture)

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_read_scalar)
{
  using namespace pni::io::nexus::xml;

  BOOST_CHECK_EQUAL(DataNode::read(scalar.get_child("group1")),"12");
  BOOST_CHECK_EQUAL(DataNode::read(scalar.get_child("group2")),"-12");
  BOOST_CHECK_EQUAL(DataNode::read(scalar.get_child("group3")),"bla");
  BOOST_CHECK_EQUAL(DataNode::read(scalar.get_child("group4")),"12.3");
  BOOST_CHECK_EQUAL(DataNode::read(scalar.get_child("group5")),"100000");
  BOOST_CHECK_EQUAL(DataNode::read(scalar.get_child("group6")),"-1000000");
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_read_array)
{
  using namespace pni::io::nexus::xml;

  BOOST_CHECK_EQUAL(DataNode::read(array.get_child("group1")),
                    "12 23 34.2  34 23");

  BOOST_CHECK_EQUAL(DataNode::read(array.get_child("group2")),
                    "12 23 34.2  34 23");
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_write_scalar)
{
  using namespace pni::io::nexus::xml;

  Node child;
  DataNode::write(child,"1234");
  BOOST_CHECK_EQUAL(DataNode::read(child),"1234");

}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_write_array)
{
  using namespace pni::io::nexus::xml;

  Node child;
  DataNode::write(child," 1 2    4 5 5  ");
  BOOST_CHECK_EQUAL(DataNode::read(child),"1 2    4 5 5");

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(AttributeNodeTest,AttributeNodeFixture)

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_read_scalar)
{
  using namespace pni::io::nexus;
  xml::Node root = scalar.get_child("group");
  xml::Node attr;
  BOOST_CHECK_NO_THROW(attr = root.attribute("attr1"));
  BOOST_CHECK_EQUAL(attr.str_data(),"12");

  BOOST_CHECK_NO_THROW(attr = root.attribute("attr2"));
  BOOST_CHECK_EQUAL(attr.str_data(),"-12");

  BOOST_CHECK_NO_THROW(attr = root.attribute("attr3"));
  BOOST_CHECK_EQUAL(attr.str_data(),"bla");

  BOOST_CHECK_NO_THROW(attr = root.attribute("attr4"));
  BOOST_CHECK_EQUAL(attr.str_data(),"12.3");

  BOOST_CHECK_NO_THROW(attr = root.attribute("attr5"));
  BOOST_CHECK_EQUAL(attr.str_data(),"100000");

  BOOST_CHECK_NO_THROW(attr = root.attribute("attr6"));
  BOOST_CHECK_EQUAL(attr.str_data(),"-1000000");
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_read_array)
{
  using namespace pni::io::nexus;
  xml::Node root = array.get_child("group");
  xml::Node attr;
  BOOST_CHECK_NO_THROW(attr = root.attribute("attr1"));
  BOOST_CHECK_EQUAL(attr.str_data(),"12 23 34.2  34 23");

  BOOST_CHECK_NO_THROW(attr = root.attribute("attr2"));
  BOOST_CHECK_EQUAL(attr.str_data(),"12 23 34.2  34 23");
}


BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

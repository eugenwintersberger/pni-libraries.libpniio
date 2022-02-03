//
// (c) Copyright 2017 DESY
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Dec 11, 2017
//
#include <boost/test/included/unit_test.hpp>
#include <pni/nexus/xml/node.hpp>
#include <pni/exceptions.hpp>
#include <pni/types.hpp>
#include <pni/error.hpp>

using namespace pni;
using namespace pni::nexus;

static const string node_from_string_str =
                                    "<node>\n<group> </group>\n<group>"
                                    " </group>\n<group> </group>\n </node>";
static const string node_from_bad_str = "this has to fail";

struct InqueryFixture
{
    xml::Node group;

    InqueryFixture():
        group(xml::Node::from_file("node/inquery.xml").get_child("group"))
    {}

};

BOOST_AUTO_TEST_SUITE(NexusXMLTest)
BOOST_AUTO_TEST_SUITE(XMLNodeTest)

BOOST_AUTO_TEST_SUITE(CreationTest)

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_from_file)
{
  xml::Node n = xml::Node::from_file("node/node_from_str.xml");
  BOOST_CHECK(!n.empty());
  BOOST_CHECK(n.size() == 1);

  //has to fail because file does not exist
  BOOST_CHECK_THROW(xml::Node::from_file("bla.xml"), pni::file_error);

  //not a well formed XML file
  BOOST_CHECK_THROW(xml::Node::from_file("node/node_from_bad_file.xml"),
                    pni::parser_error);


}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_from_string)
{
  xml::Node n = xml::Node::from_string(node_from_string_str);

  BOOST_CHECK(!n.empty());
  BOOST_CHECK(n.size() == 1);

  BOOST_CHECK_THROW(xml::Node::from_string(node_from_bad_str),
                    pni::parser_error);
}


BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(InqueryTest,InqueryFixture)


//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_get_attribute)
{

  BOOST_CHECK_NO_THROW(group.attribute("name"));

  //not a well formed XML file
  BOOST_CHECK_THROW(group.attribute("type"), key_error);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_has_attribute)
{

  BOOST_CHECK(group.has_attribute("name"));
  BOOST_CHECK(!group.has_attribute("type"));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

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
#include <boost/test/unit_test.hpp>
#include <pni/nexus/xml/node.hpp>
#include <pni/nexus/xml/group_builder.hpp>
#include <pni/nexus/xml/object_builder.hpp>
#include <pni/nexus/predicates.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;
using namespace pni;

struct GroupBuilderFixture
{
    file::File nexus_file;
    node::Group root_group;
    nexus::xml::Node xml_node;
    nexus::xml::ObjectBuilder builder;

    GroupBuilderFixture()
    {
      nexus_file = file::create("GroupBuilderTest.nxs",file::AccessFlags::TRUNCATE);
      root_group = nexus_file.root();
    }
};


BOOST_AUTO_TEST_SUITE(NexusXMLTest)

BOOST_FIXTURE_TEST_SUITE(GroupBuilder,GroupBuilderFixture)

BOOST_AUTO_TEST_CASE(linear_groups)
{
  std::string xml_input =
      "<group name=\"entry_1\" type=\"NXentry\"/>"
      "<group name=\"entry_2\" type=\"NXentry\"/>"
      "<group name=\"log\"/>";

  BOOST_CHECK_NO_THROW(xml_node = nexus::xml::Node::from_string(xml_input));
  BOOST_CHECK_NO_THROW(builder = nexus::xml::ObjectBuilder(xml_node));
  BOOST_CHECK_NO_THROW(builder.build(root_group));

  BOOST_CHECK(root_group.nodes.size() == 3);
  BOOST_CHECK(root_group.nodes[0].link().path().name() == "entry_1");
  BOOST_CHECK(root_group.nodes[1].link().path().name() == "entry_2");
  BOOST_CHECK(root_group.nodes[2].link().path().name() == "log");
}

BOOST_AUTO_TEST_CASE(recursive_groups)
{
  BOOST_CHECK_NO_THROW(xml_node = nexus::xml::Node::from_file("group_builder.xml"));
  BOOST_CHECK_NO_THROW(builder = nexus::xml::ObjectBuilder(xml_node));
  BOOST_CHECK_NO_THROW(builder.build(root_group));

  BOOST_CHECK(root_group.nodes.size() == 2);
  node::Group entry = root_group.nodes["entry_1"];
  BOOST_CHECK(nexus::IsEntry()(entry));
  BOOST_CHECK(entry.nodes.size() == 3);
  BOOST_CHECK(entry.nodes.exists("instrument"));
  BOOST_CHECK(entry.nodes.exists("data"));
  BOOST_CHECK(entry.nodes.exists("sample"));
  BOOST_CHECK(nexus::IsInstrument()(entry.nodes["instrument"]));
  BOOST_CHECK(nexus::IsSample()(entry.nodes["sample"]));
  BOOST_CHECK(nexus::IsData()(entry.nodes["data"]));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

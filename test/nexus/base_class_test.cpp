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
// Created on: Dec 7, 2017
//
#include <boost/test/unit_test.hpp>
#include <pni/io/nexus/base_class.hpp>
#include <pni/io/nexus/file.hpp>

using namespace pni::io;

struct BaseClassTestFixture
{
    hdf5::file::File nexus_file;
    hdf5::node::Group root_group;

    BaseClassTestFixture()
    {
      using hdf5::file::AccessFlags;
      nexus_file = nexus::create_file("base_class_test.nxs",AccessFlags::TRUNCATE);
      root_group = nexus_file.root();
    }
};

BOOST_FIXTURE_TEST_SUITE(BaseClassTest,BaseClassTestFixture)

BOOST_AUTO_TEST_SUITE(ConstructionTest)

BOOST_AUTO_TEST_CASE(default_construction)
{
  nexus::BaseClass c;
  BOOST_CHECK(!c.is_valid());
}

BOOST_AUTO_TEST_CASE(using_constructor)
{
  nexus::BaseClass c(root_group,"entry","NXentry");
  BOOST_CHECK(c.is_valid());
  BOOST_CHECK_EQUAL(c.get_class(),"NXentry");
}

BOOST_AUTO_TEST_CASE(invalid_name)
{
  BOOST_CHECK_THROW((nexus::BaseClass(root_group,"Entry","NXentry")),std::runtime_error);
  BOOST_CHECK(!root_group.nodes.exists("Entry"));
}

BOOST_AUTO_TEST_CASE(construct_from_group_or_node)
{
  hdf5::node::Node n = nexus::BaseClass(root_group,"entry","NXentry");
  nexus::BaseClass c(n);
  BOOST_CHECK_EQUAL(c.get_class(),"NXentry");

  hdf5::node::Group g(root_group,"entry_2");
  BOOST_CHECK_THROW((nexus::BaseClass(g)),std::runtime_error);

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(AssignmentTest)

BOOST_AUTO_TEST_CASE(assignment_from_base_class)
{
  nexus::BaseClass entry_1(root_group,"entry_1","NXentry");
  nexus::BaseClass entry_2;
  BOOST_CHECK_NO_THROW((entry_2=entry_1));

  BOOST_CHECK_EQUAL(entry_1.get_class(),entry_2.get_class());
}

BOOST_AUTO_TEST_CASE(assignment_from_node)
{
  hdf5::node::Node n = nexus::BaseClass(root_group,"entry","NXentry");
  nexus::BaseClass c;
  BOOST_CHECK_NO_THROW((c = n));
  BOOST_CHECK_EQUAL(c.get_class(),"NXentry");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

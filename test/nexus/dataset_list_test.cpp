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
// Created on: Dec 19, 2017
//
#include <boost/test/included/unit_test.hpp>
#include <pni/nexus.hpp>
#include "container_test_fixture.hpp"

using namespace pni;

BOOST_AUTO_TEST_SUITE(ContainerTest)
BOOST_FIXTURE_TEST_SUITE(DatasetListTest,ContainerTestFixture)

BOOST_AUTO_TEST_CASE(default_construction)
{
  nexus::DatasetList list;
  BOOST_CHECK(list.size() == 0);
}

BOOST_AUTO_TEST_CASE(mixed_construction)
{
  hdf5::node::Group base = root_group.nodes["scan_1"];
  BOOST_CHECK_THROW((nexus::DatasetList(base.nodes.begin(),base.nodes.end())),std::runtime_error);

  //but

}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

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
// Created on: Dec 19, 2017
//
#include <boost/test/unit_test.hpp>
#include <pni/io/nexus.hpp>
#include "container_test_fixture.hpp"

using namespace pni::io;



BOOST_AUTO_TEST_SUITE(ContainerTest)
BOOST_FIXTURE_TEST_SUITE(AttributeListTest,ContainerTestFixture)

BOOST_AUTO_TEST_CASE(default_construction)
{
  nexus::AttributeList list;
  BOOST_CHECK(list.size() == 0);
}

BOOST_AUTO_TEST_CASE(test_from_iterator)
{
  nexus::AttributeList list(root_group.attributes.begin(),root_group.attributes.end());
  BOOST_CHECK(list.size() == 5);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

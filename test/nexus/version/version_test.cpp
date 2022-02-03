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
// Created on: Dec 6, 2017
//

#include "../../boost_unit_test.hpp"
#include <pni/nexus/version.hpp>

using namespace pni;

BOOST_AUTO_TEST_SUITE(VersionTest)

BOOST_AUTO_TEST_SUITE(CreateVersion)

BOOST_AUTO_TEST_CASE(test_default_construction)
{
  nexus::Version v;
  BOOST_CHECK(v.major() == nexus::Version::NumberType(0));
  BOOST_CHECK(v.minor() == nexus::Version::NumberType(0));
  BOOST_CHECK(v.patch() == nexus::Version::NumberType(0));
}

BOOST_AUTO_TEST_CASE(test_construction)
{
  nexus::Version v(10,0,2);
  BOOST_CHECK(v.major() == nexus::Version::NumberType(10));
  BOOST_CHECK(v.minor() == nexus::Version::NumberType(0));
  BOOST_CHECK(v.patch() == nexus::Version::NumberType(2));
}

BOOST_AUTO_TEST_CASE(test_copy_construction)
{
  nexus::Version v1(3,0,12);
  nexus::Version v2(v1);
  BOOST_CHECK(v1.major() == v2.major());
  BOOST_CHECK(v1.minor() == v2.minor());
  BOOST_CHECK(v1.patch() == v2.patch());
}

BOOST_AUTO_TEST_CASE(test_copy_assignment)
{
  nexus::Version v1(5,23,12);
  nexus::Version v2;
  v2 = v1;

  BOOST_CHECK(v1.major() == v2.major());
  BOOST_CHECK(v1.minor() == v2.minor());
  BOOST_CHECK(v1.patch() == v2.patch());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

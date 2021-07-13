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
// Created on: Dec 6, 2017
//

#include <boost/test/unit_test.hpp>
#include <pni/nexus/version.hpp>

using namespace pni::io;

BOOST_AUTO_TEST_SUITE(VersionTest)

BOOST_AUTO_TEST_SUITE(StringConversion)

BOOST_AUTO_TEST_CASE(test_from_string)
{
  nexus::Version v = nexus::Version::from_string("0.10.23");
  BOOST_CHECK(v.major() == nexus::Version::NumberType(0));
  BOOST_CHECK(v.minor() == nexus::Version::NumberType(10));
  BOOST_CHECK(v.patch() == nexus::Version::NumberType(23));
}

BOOST_AUTO_TEST_CASE(test_partial_only_major)
{
  nexus::Version v;;
  BOOST_CHECK_NO_THROW(v = nexus::Version::from_string("10"));
  BOOST_CHECK(v.major() == nexus::Version::NumberType(10));
  BOOST_CHECK(v.minor() == nexus::Version::NumberType(0));
  BOOST_CHECK(v.patch() == nexus::Version::NumberType(0));
}

BOOST_AUTO_TEST_CASE(test_partial_major_and_minor)
{
  nexus::Version v;
  BOOST_CHECK_NO_THROW(v = nexus::Version::from_string("10.3"));
  BOOST_CHECK(v.major() == nexus::Version::NumberType(10));
  BOOST_CHECK(v.minor() == nexus::Version::NumberType(3));
  BOOST_CHECK(v.patch() == nexus::Version::NumberType(0));
}

BOOST_AUTO_TEST_CASE(test_to_string)
{
  nexus::Version v(21,0,2);
  BOOST_CHECK(nexus::Version::to_string(v) == "21.0.2");
}


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

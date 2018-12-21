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
#include <pni/io/nexus/version.hpp>

using namespace pni::io;

BOOST_AUTO_TEST_SUITE(VersionTest)

BOOST_AUTO_TEST_SUITE(Comparison)

BOOST_AUTO_TEST_CASE(test_equality)
{
  BOOST_CHECK(nexus::Version(10,23,3) == nexus::Version(10,23,3));
}

BOOST_AUTO_TEST_CASE(test_inequality)
{
  BOOST_CHECK(nexus::Version(10,23,0) != nexus::Version(10,23,1));
  BOOST_CHECK(nexus::Version(10,0,1) != nexus::Version(10,1,1));
  BOOST_CHECK(nexus::Version(0,10,1) != nexus::Version(1,10,1));
}

BOOST_AUTO_TEST_CASE(test_greater_equal_than)
{
  BOOST_CHECK_GE(nexus::Version(10,12,1),nexus::Version(10,12,1));
  BOOST_CHECK_GE(nexus::Version(10,12,1),nexus::Version(10,12,0));
  BOOST_CHECK_GE(nexus::Version(10,12,1),nexus::Version(10,11,0));
  BOOST_CHECK_GE(nexus::Version(10,12,1),nexus::Version(9,111,2));
}

BOOST_AUTO_TEST_CASE(test_greater_than)
{
  BOOST_CHECK_GT(nexus::Version(10,12,1),nexus::Version(10,12,0));
  BOOST_CHECK_GT(nexus::Version(10,12,1),nexus::Version(10,11,0));
  BOOST_CHECK_GT(nexus::Version(10,12,1),nexus::Version(9,111,2));
}

BOOST_AUTO_TEST_CASE(test_less_equal_than)
{
  BOOST_CHECK_LE(nexus::Version(10,12,1),nexus::Version(10,12,1));
  BOOST_CHECK_LE(nexus::Version(10,12,0),nexus::Version(10,12,1));
  BOOST_CHECK_LE(nexus::Version(10,11,0),nexus::Version(10,12,1));
  BOOST_CHECK_LE(nexus::Version(9,111,2),nexus::Version(10,12,1));
}

BOOST_AUTO_TEST_CASE(test_less_than)
{
  BOOST_CHECK_LT(nexus::Version(10,12,0),nexus::Version(10,12,1));
  BOOST_CHECK_LT(nexus::Version(10,11,0),nexus::Version(10,12,1));
  BOOST_CHECK_LT(nexus::Version(9,111,2),nexus::Version(10,12,1));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()

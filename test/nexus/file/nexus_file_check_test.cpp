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
// Created on: Dec 7, 2017
//
#include <boost/test/unit_test.hpp>
#include <pni/nexus/file.hpp>

using namespace pni;
using namespace hdf5;

struct CheckTestsFixture
{
    CheckTestsFixture()
    {
      nexus::create_file("check_tests.nxs",file::AccessFlags::Truncate);
      file::create("check_tests.h5",file::AccessFlags::Truncate);
    }
};


BOOST_AUTO_TEST_SUITE(NexusFileTest)

BOOST_FIXTURE_TEST_SUITE(CheckTests,CheckTestsFixture)

BOOST_AUTO_TEST_CASE(test_check_file)
{
  BOOST_CHECK(nexus::is_nexus_file("check_tests.nxs"));
  BOOST_CHECK(!nexus::is_nexus_file("check_tests.h5"));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

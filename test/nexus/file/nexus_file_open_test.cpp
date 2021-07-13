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
#include <pni/nexus/file.hpp>

using namespace pni::io;
using namespace boost;

struct OpenTestsFixture
{
    OpenTestsFixture()
    {
       nexus::create_file("open_test.nxs",hdf5::file::AccessFlags::TRUNCATE);
    }
};

BOOST_AUTO_TEST_SUITE(NexusFileTest)

BOOST_FIXTURE_TEST_SUITE(OpenTests,OpenTestsFixture)

BOOST_AUTO_TEST_CASE(test_open)
{
  hdf5::file::File nx_file;
  BOOST_CHECK_NO_THROW(nx_file = nexus::open_file("open_test.nxs"));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()

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
// Created on: Dec 8, 2017
//
#include <boost/test/unit_test.hpp>
#include <pni/io/nexus.hpp>

using namespace hdf5;
using namespace pni::io;

struct SearchTestFixture
{
    file::File nexus_file;
    node::Group root_group;
    node::Group entry;
    SearchTestFixture()
    {
      nexus_file = nexus::create_file("SearchTest.nxs",file::AccessFlags::TRUNCATE);
      root_group = nexus_file.root();

      entry = nexus::BaseClass(root_group,"entry_01","NXentry");

      nexus::BaseClass instrument(entry,"instrument","NXinstrument");
      nexus::BaseClass(instrument,"detector_1","NXdetector");
      nexus::BaseClass(instrument,"detector_2","NXdetector");

      nexus::BaseClass(root_group,"entry_02","NXentry");
      nexus::BaseClass(root_group,"entry_03","NXentry");
    }
};

BOOST_FIXTURE_TEST_SUITE(SearchTest,SearchTestFixture)

BOOST_AUTO_TEST_CASE(test_get_entries)
{
  nexus::GroupList entries = nexus::search(root_group,nexus::IsEntry());
  BOOST_CHECK_EQUAL(entries.size(),3);
  BOOST_CHECK_EQUAL(entries[0].link().path().name(),"entry_01");
  BOOST_CHECK_EQUAL(entries[1].link().path().name(),"entry_02");
  BOOST_CHECK_EQUAL(entries[2].link().path().name(),"entry_03");
}

BOOST_AUTO_TEST_CASE(test_get_detectors_recursive)
{
  nexus::GroupList detectors = nexus::search(entry,nexus::IsDetector(),true);
  BOOST_CHECK_EQUAL(detectors.size(),2);
  BOOST_CHECK_EQUAL(detectors[0].link().path().name(),"detector_1");
  BOOST_CHECK_EQUAL(detectors[1].link().path().name(),"detector_2");
}

BOOST_AUTO_TEST_SUITE_END()

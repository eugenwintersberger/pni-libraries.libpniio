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
// Created on: Dec 18, 2017
//
#include <boost/test/unit_test.hpp>
#include <pni/nexus.hpp>
#include <h5cpp/hdf5.hpp>

using namespace pni;

struct GetObjectFixture
{
    hdf5::file::File multi_entry;
    hdf5::file::File multi_detector;
    hdf5::node::Group base;

    GetObjectFixture()
    {
      multi_entry = nexus::create_file("multi_entry.nxs",hdf5::file::AccessFlags::Truncate);
      base = multi_entry.root();
      nexus::xml::create_from_file(base,"multi_entry.xml");

      multi_detector = nexus::create_file("multi_detector.nxs",hdf5::file::AccessFlags::Truncate);
      nexus::xml::create_from_file(multi_detector.root(),"multi_detector.xml");
    }
};


BOOST_AUTO_TEST_SUITE(PathTest)
BOOST_FIXTURE_TEST_SUITE(GetObjectTest,GetObjectFixture)

BOOST_AUTO_TEST_CASE(search_for_entries)
{
  base = multi_entry.root();
  nexus::PathObjectList result = nexus::get_objects(base,nexus::Path("/:NXentry"));
  BOOST_CHECK(result.size() == 3);
  nexus::GroupList entries = result;
  BOOST_CHECK(entries[0].link().path().name() == "scan_1");
  BOOST_CHECK(entries[1].link().path().name() == "scan_2");
  BOOST_CHECK(entries[2].link().path().name() == "scan_3");
}

BOOST_AUTO_TEST_CASE(search_for_entries_string)
{
  base = multi_entry.root();
  nexus::PathObjectList result =
    nexus::get_objects(base, std::string("/:NXentry"));
  BOOST_CHECK(result.size() == 3);
  nexus::GroupList entries = result;
  BOOST_CHECK(entries[0].link().path().name() == "scan_1");
  BOOST_CHECK(entries[1].link().path().name() == "scan_2");
  BOOST_CHECK(entries[2].link().path().name() == "scan_3");
}

BOOST_AUTO_TEST_CASE(search_for_entries_char)
{
  base = multi_entry.root();
  nexus::PathObjectList result = nexus::get_objects(base,"/:NXentry");
  BOOST_CHECK(result.size() == 3);
  nexus::GroupList entries = result;
  BOOST_CHECK(entries[0].link().path().name() == "scan_1");
  BOOST_CHECK(entries[1].link().path().name() == "scan_2");
  BOOST_CHECK(entries[2].link().path().name() == "scan_3");
}

BOOST_AUTO_TEST_CASE(get_unresolvable_link)
{
  base = multi_entry.root();
  nexus::PathObjectList result = nexus::get_objects(base,nexus::Path("/:NXentry/:NXdata/data"));
  BOOST_CHECK(result.size() == 1);
  nexus::PathObject object = result.front();
  BOOST_CHECK(nexus::is_link(object));

  hdf5::node::Link link = static_cast<hdf5::node::Link>(object);
  BOOST_CHECK(!link.is_resolvable());
  BOOST_CHECK(link.type() == hdf5::node::LinkType::External);
}

BOOST_AUTO_TEST_CASE(search_detectors)
{
  base = multi_detector.root();
  nexus::DatasetList result = nexus::get_objects(base,nexus::Path("/scan_1:NXentry/:NXinstrument/:NXdetector/data"));
  BOOST_CHECK(result.size() == 3);
  BOOST_CHECK(result[0].link().path().parent().name() == "detector_1");
  BOOST_CHECK(result[1].link().path().parent().name() == "detector_2");
  BOOST_CHECK(result[2].link().path().parent().name() == "detector_3");
}

BOOST_AUTO_TEST_CASE(seach_detector_by_name)
{
  base = multi_detector.root();
  nexus::DatasetList result = nexus::get_objects(base,nexus::Path("/scan_1/instrument/detector_1/data"));
  BOOST_CHECK(result.size() == 1);
}

BOOST_AUTO_TEST_CASE(search_entries_relative)
{
  base = multi_entry.root();
  nexus::PathObjectList result = nexus::get_objects(base,nexus::Path(":NXentry"));
  BOOST_CHECK(result.size() == 3);
  nexus::GroupList entries = result;
  BOOST_CHECK(entries[0].link().path().name() == "scan_1");
  BOOST_CHECK(entries[1].link().path().name() == "scan_2");
  BOOST_CHECK(entries[2].link().path().name() == "scan_3");
}

BOOST_AUTO_TEST_CASE(search_detectors_relative)
{
  base = multi_detector.root().nodes["scan_1"];
  nexus::DatasetList result = nexus::get_objects(base,nexus::Path(":NXinstrument/:NXdetector/data"));
  BOOST_CHECK(result.size() == 3);
  BOOST_CHECK(result[0].link().path().parent().name() == "detector_1");
  BOOST_CHECK(result[1].link().path().parent().name() == "detector_2");
  BOOST_CHECK(result[2].link().path().parent().name() == "detector_3");

}

BOOST_AUTO_TEST_CASE(search_detector_attributes_absolute)
{
  base = multi_detector.root();
  nexus::AttributeList result = nexus::get_objects(base,nexus::Path("/scan_1:NXentry/:NXinstrument/:NXdetector/data@units"));
  BOOST_CHECK(result.size() == 3);
  BOOST_CHECK(result[0].parent_link().path().parent().name() == "detector_1");
  BOOST_CHECK(result[1].parent_link().path().parent().name() == "detector_2");
  BOOST_CHECK(result[2].parent_link().path().parent().name() == "detector_3");

}

BOOST_AUTO_TEST_CASE(search_single_detector_by_name)
{
  base = multi_detector.root();
  nexus::DatasetList result = nexus::get_objects(base,nexus::Path("/scan_1:NXentry/:NXinstrument/detector_1:NXdetector/data"));
  BOOST_CHECK(result.size() == 1);
  BOOST_CHECK(result[0].link().path().parent().name() == "detector_1");
}

BOOST_AUTO_TEST_CASE(search_detector_attributes_relative)
{
  base = multi_detector.root().nodes["scan_1"];
  nexus::AttributeList result = nexus::get_objects(base,nexus::Path(":NXinstrument/:NXdetector/data@units"));
  BOOST_CHECK(result.size() == 3);
  BOOST_CHECK(result[0].parent_link().path().parent().name() == "detector_1");
  BOOST_CHECK(result[1].parent_link().path().parent().name() == "detector_2");
  BOOST_CHECK(result[2].parent_link().path().parent().name() == "detector_3");

}

BOOST_AUTO_TEST_CASE(search_single_attribute)
{
  base = multi_detector.root();
  nexus::AttributeList result = nexus::get_objects(base,nexus::Path("@NX_class"));
  BOOST_CHECK(result.size() == 1);
}

BOOST_AUTO_TEST_CASE(search_single_attribute_with_dot)
{
  base = multi_detector.root();
  nexus::AttributeList result = nexus::get_objects(base,nexus::Path(".@NX_class"));
  BOOST_CHECK(result.size() == 1);
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

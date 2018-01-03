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
// Created on: Dec 18, 2017
//
#include <boost/test/unit_test.hpp>
#include <pni/io/nexus.hpp>
#include <h5cpp/hdf5.hpp>

using namespace pni::io;

struct GetPathFixture
{
    hdf5::file::File file1;
    hdf5::file::File file2;
    GetPathFixture()
    {
      file1=nexus::create_file("GetPathFixture1.nxs",hdf5::file::AccessFlags::TRUNCATE);
      nexus::xml::create_from_file(file1.root(),"simple_structure.xml");
      file2=nexus::create_file("GetPathFixture2.nxs",hdf5::file::AccessFlags::TRUNCATE);
      nexus::xml::create_from_file(file2.root(),"detector_with_transformation.xml");
    }
};

BOOST_AUTO_TEST_SUITE(PathTest)
BOOST_FIXTURE_TEST_SUITE(GetPathTest,GetPathFixture)

BOOST_AUTO_TEST_CASE(test_file1)
{
  hdf5::node::Group g = hdf5::node::get_node(file1.root(),"/scan_1/instrument/storage_ring");
  nexus::Path nxp = nexus::get_path(g);
  BOOST_CHECK_EQUAL(nexus::Path::to_string(nxp),"/scan_1:NXentry/instrument:NXinstrument/storage_ring:NXsource");

  hdf5::node::Dataset d = hdf5::node::get_node(file1.root(),"/scan_1/instrument/storage_ring/distance");
  nxp = nexus::get_path(d);
  BOOST_CHECK_EQUAL(nexus::Path::to_string(nxp),
                    "/scan_1:NXentry/instrument:NXinstrument/storage_ring:NXsource/distance");

}

BOOST_AUTO_TEST_CASE(test_file2)
{
  hdf5::node::Dataset d = hdf5::node::get_node(file2.root(),"/scan_1/instrument/detector/transformation/gamma");
  hdf5::attribute::Attribute attr = d.attributes["depends_on"];
  nexus::Path nxp = nexus::get_path(attr);
  BOOST_CHECK_EQUAL(nexus::Path::to_string(nxp),
                    "/scan_1:NXentry/instrument:NXinstrument/detector:NXdetector/transformation:NXtransformations/gamma@depends_on"
                    );
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

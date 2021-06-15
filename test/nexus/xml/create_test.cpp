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
// Created on: Dec 14, 2017
//
#include <boost/test/unit_test.hpp>
#include <pni/io/nexus/xml/create.hpp>

using namespace pni::io::nexus;

struct CreateTestFixture
{
    hdf5::file::File file;
    hdf5::node::Group root_group;
    hdf5::node::Dataset dataset;

    CreateTestFixture()
    {
      file = hdf5::file::create("CreateTest.nxs",hdf5::file::AccessFlags::TRUNCATE);
      root_group = file.root();
    }
};

BOOST_FIXTURE_TEST_SUITE(CreateTest,CreateTestFixture)

BOOST_AUTO_TEST_CASE(from_simple_structure)
{
  using hdf5::node::get_node;
  using hdf5::node::Type;
  boost::filesystem::path file = "create/simple_structure.xml";
  BOOST_CHECK_NO_THROW(xml::create_from_file(root_group,file));

  BOOST_CHECK(get_node(root_group,"/scan_1").type() == Type::GROUP);
  BOOST_CHECK(get_node(root_group,"/scan_1/title").type() == Type::DATASET);
  BOOST_CHECK(get_node(root_group,"/scan_1/experiment_identifier").type() == Type::DATASET);
  BOOST_CHECK(get_node(root_group,"/scan_1/experiment_description").type() == Type::DATASET);
  BOOST_CHECK(get_node(root_group,"/scan_1/instrument/storage_ring").type() == Type::GROUP);
  BOOST_CHECK(get_node(root_group,"/scan_1/instrument/storage_ring/name").type() == Type::DATASET);
}

BOOST_AUTO_TEST_CASE(from_simple_structure_with_data)
{
  using hdf5::node::get_node;
  boost::filesystem::path file = "create/simple_structure_with_data.xml";
  BOOST_CHECK_NO_THROW(xml::create_from_file(root_group,file));

  dataset = get_node(root_group,"/scan_1/experiment_description");
  std::string description;
  dataset.read(description);
  BOOST_CHECK(description == "Beamtime at PETRA III in March");
}

BOOST_AUTO_TEST_CASE(from_detector_with_transformation)
{
  boost::filesystem::path file = "create/detector_with_transformation.xml";
  BOOST_CHECK_NO_THROW(xml::create_from_file(root_group,file));
}

BOOST_AUTO_TEST_CASE(detector_master_data_file)
{
  boost::filesystem::path xml_master_file = "create/detector_master_file.xml";
  boost::filesystem::path xml_data_file = "create/detector_data_file.xml";

  hdf5::file::File master_file = hdf5::file::create("detector_master_file.nxs",
                                                    hdf5::file::AccessFlags::TRUNCATE);
  hdf5::file::File data_file = hdf5::file::create("detector_data_file.nxs",
                                                  hdf5::file::AccessFlags::TRUNCATE);
  BOOST_CHECK_NO_THROW(xml::create_from_file(data_file.root(),xml_data_file));
  BOOST_CHECK_NO_THROW(xml::create_from_file(master_file.root(),xml_master_file));

}

BOOST_AUTO_TEST_CASE(from_detector_link)
{
  using hdf5::node::get_node;
  using hdf5::node::Type;
  boost::filesystem::path file = "create/detector_link.xml";
  BOOST_CHECK_NO_THROW(xml::create_from_file(root_group,file));

  BOOST_CHECK(get_node(root_group,"/entry").type() == Type::GROUP);
  BOOST_CHECK(get_node(root_group,"/entry/string").type() == Type::GROUP);
  BOOST_CHECK(get_node(root_group,"/entry/string/value").type() == Type::DATASET);
  BOOST_CHECK(get_node(root_group,"/entry/string/time").type() == Type::DATASET);
  BOOST_CHECK(get_node(root_group,"/entry/double").type() == Type::GROUP);
  BOOST_CHECK(get_node(root_group,"/entry/double/value").type() == Type::DATASET);
  BOOST_CHECK(get_node(root_group,"/entry/double/time").type() == Type::DATASET);
  BOOST_CHECK(get_node(root_group,"/entry/data").type() == Type::GROUP);
  BOOST_CHECK(get_node(root_group,"/entry/data/data").type() == Type::DATASET);
}

BOOST_AUTO_TEST_SUITE_END()

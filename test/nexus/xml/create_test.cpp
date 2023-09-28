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
// Created on: Dec 14, 2017
//
#include <boost/test/unit_test.hpp>
#include <pni/nexus/xml/create.hpp>

using namespace pni::nexus;

struct CreateTestFixture
{
    hdf5::file::File file;
    hdf5::node::Group root_group;
    hdf5::node::Dataset dataset;

    CreateTestFixture()
    {
      file = hdf5::file::create("CreateTest.nxs",hdf5::file::AccessFlags::Truncate);
      root_group = file.root();
    }
};

BOOST_FIXTURE_TEST_SUITE(CreateTest,CreateTestFixture)

BOOST_AUTO_TEST_CASE(from_simple_structure)
{
  using hdf5::node::get_node;
  using hdf5::node::Type;
  fs::path file = "create/simple_structure.xml";
  BOOST_CHECK_NO_THROW(xml::create_from_file(root_group,file));

  BOOST_CHECK(get_node(root_group,"/scan_1").type() == Type::Group);
  BOOST_CHECK(get_node(root_group,"/scan_1/title").type() == Type::Dataset);
  BOOST_CHECK(get_node(root_group,"/scan_1/experiment_identifier").type() == Type::Dataset);
  BOOST_CHECK(get_node(root_group,"/scan_1/experiment_description").type() == Type::Dataset);
  BOOST_CHECK(get_node(root_group,"/scan_1/instrument/storage_ring").type() == Type::Group);
  BOOST_CHECK(get_node(root_group,"/scan_1/instrument/storage_ring/name").type() == Type::Dataset);
}

BOOST_AUTO_TEST_CASE(from_simple_structure_with_data)
{
  using hdf5::node::get_node;
  fs::path file = "create/simple_structure_with_data.xml";
  BOOST_CHECK_NO_THROW(xml::create_from_file(root_group,file));

  dataset = get_node(root_group,"/scan_1/experiment_description");
  std::string description;
  dataset.read(description);
  BOOST_CHECK(description == "Beamtime at PETRA III in March");
}

BOOST_AUTO_TEST_CASE(from_detector_with_transformation)
{
  fs::path file = "create/detector_with_transformation.xml";
  BOOST_CHECK_NO_THROW(xml::create_from_file(root_group,file));
}

BOOST_AUTO_TEST_CASE(detector_master_data_file)
{
  fs::path xml_master_file = "create/detector_master_file.xml";
  fs::path xml_data_file = "create/detector_data_file.xml";

  hdf5::file::File master_file = hdf5::file::create("detector_master_file.nxs",
                                                    hdf5::file::AccessFlags::Truncate);
  hdf5::file::File data_file = hdf5::file::create("detector_data_file.nxs",
                                                  hdf5::file::AccessFlags::Truncate);
  BOOST_CHECK_NO_THROW(xml::create_from_file(data_file.root(),xml_data_file));
  BOOST_CHECK_NO_THROW(xml::create_from_file(master_file.root(),xml_master_file));

}

BOOST_AUTO_TEST_CASE(from_detector_link)
{
  using hdf5::node::get_node;
  using hdf5::node::Type;
  fs::path file = "create/detector_link.xml";
  BOOST_CHECK_NO_THROW(xml::create_from_file(root_group,file));

  BOOST_CHECK(get_node(root_group,"/entry").type() == Type::Group);
  BOOST_CHECK(get_node(root_group,"/entry/string").type() == Type::Group);
  BOOST_CHECK(get_node(root_group,"/entry/string/value").type() == Type::Dataset);
  BOOST_CHECK(get_node(root_group,"/entry/string/time").type() == Type::Dataset);
  BOOST_CHECK(get_node(root_group,"/entry/double").type() == Type::Group);
  BOOST_CHECK(get_node(root_group,"/entry/double/value").type() == Type::Dataset);
  BOOST_CHECK(get_node(root_group,"/entry/double/time").type() == Type::Dataset);
  BOOST_CHECK(get_node(root_group,"/entry/data").type() == Type::Group);
  BOOST_CHECK(get_node(root_group,"/entry/data/data").type() == Type::Dataset);
}

BOOST_AUTO_TEST_CASE(from_duplicate_field)
{
  using hdf5::node::get_node;
  using hdf5::node::Type;
  fs::path file = "create/duplicated_field.xml";
  BOOST_CHECK_THROW(xml::create_from_file(root_group,file), std::runtime_error);

}

BOOST_AUTO_TEST_CASE(from_duplicate_group)
{
  using hdf5::node::get_node;
  using hdf5::node::Type;
  fs::path file = "create/duplicated_group.xml";
  BOOST_CHECK_THROW(xml::create_from_file(root_group,file), std::runtime_error);

}

BOOST_AUTO_TEST_CASE(add_filters)
{
  using hdf5::node::get_node;
  using hdf5::node::Type;
  fs::path file = "create/filters.xml";
  BOOST_CHECK_NO_THROW(xml::create_from_file(root_group,file));

  BOOST_CHECK(get_node(root_group,"/scan").type() == Type::Group);
  BOOST_CHECK(get_node(root_group,"/scan/data").type() == Type::Group);
  BOOST_CHECK(get_node(root_group,"/scan/data/pilatus").type() == Type::Dataset);
  hdf5::node::Dataset dataset = root_group.get_dataset("/scan/data/pilatus");
  auto dcpl = dataset.creation_list();

  hdf5::filter::ExternalFilters filters;
  auto flags = filters.fill(dcpl);
  BOOST_CHECK(dcpl.nfilters() == 6);
  BOOST_CHECK(flags.size() == 6);
  BOOST_CHECK(filters.size() == 6);

  BOOST_CHECK(filters[0].id() == H5Z_FILTER_SHUFFLE);

  BOOST_CHECK(filters[0].cd_values().size() == 1ul);  // ??
  BOOST_CHECK(filters[0].cd_values()[0] == 2ul);      // ??
  BOOST_CHECK(flags[0] == hdf5::filter::Availability::Optional);

  BOOST_CHECK(filters[1].id() == H5Z_FILTER_DEFLATE);

  std::vector<unsigned int> rate {4u};
  BOOST_REQUIRE_EQUAL(filters[1].cd_values().size(), rate.size());
  for(size_t i = 0; i < rate.size(); ++i){
    BOOST_CHECK_EQUAL(filters[1].cd_values()[i], rate[i]);
  }
  BOOST_CHECK(flags[1] == hdf5::filter::Availability::Optional);

  BOOST_CHECK(filters[2].id() == H5Z_FILTER_NBIT);

  std::vector<unsigned int> nbit_opts {8u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};
  BOOST_REQUIRE_EQUAL(filters[2].cd_values().size(), nbit_opts.size());
  for(size_t i = 0; i < nbit_opts.size(); ++i){
    BOOST_CHECK_EQUAL(filters[2].cd_values()[i], nbit_opts[i]);
  }
  BOOST_CHECK(flags[2] == hdf5::filter::Availability::Optional);

  BOOST_CHECK(filters[3].id() == H5Z_FILTER_SZIP);

  std::vector<unsigned int> szip_opts {137u, 16u, 16u, 512u}; // ??
  BOOST_REQUIRE_EQUAL(filters[3].cd_values().size(), szip_opts.size());
  for(size_t i = 0; i < szip_opts.size(); ++i){
    BOOST_CHECK_EQUAL(filters[3].cd_values()[i], szip_opts[i]);
  }
  BOOST_CHECK(flags[3] == hdf5::filter::Availability::Optional);

  BOOST_CHECK(filters[4].id() == 32008);

  std::vector<unsigned int> bs_opts {0u, 3u, 2u, 0u, 0u};    // ??
  BOOST_REQUIRE_EQUAL(filters[4].cd_values().size(), bs_opts.size());
  for(size_t i = 0; i < bs_opts.size(); ++i){
    BOOST_CHECK_EQUAL(filters[4].cd_values()[i], bs_opts[i]);
  }
  BOOST_CHECK(flags[4] == hdf5::filter::Availability::Mandatory);

  BOOST_CHECK(filters[5].id() == 32001);

  std::vector<unsigned int> bl_opts {2u, 2u, 2u, 1048576u, 4u, 0u, 0u}; // ??
  BOOST_REQUIRE_EQUAL(filters[5].cd_values().size(), bl_opts.size());
  for(size_t i = 0; i < bl_opts.size(); ++i){
    BOOST_CHECK_EQUAL(filters[5].cd_values()[i], bl_opts[i]);
  }
  BOOST_CHECK(flags[5] == hdf5::filter::Availability::Mandatory);

}

BOOST_AUTO_TEST_SUITE_END()

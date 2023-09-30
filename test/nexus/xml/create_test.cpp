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
#include <pni/error.hpp>

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

boost::test_tools::assertion_result are_filters_installed(boost::unit_test::test_unit_id)
{
  return hdf5::filter::is_filter_available(32008) && hdf5::filter::is_filter_available(32001);
}

boost::test_tools::assertion_result are_filters_not_installed(boost::unit_test::test_unit_id)
{
  return !(hdf5::filter::is_filter_available(32008) && hdf5::filter::is_filter_available(32001));
}



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

BOOST_AUTO_TEST_CASE(from_nxsdesigner_slit)
{
  using hdf5::node::get_node;
  using hdf5::node::Type;
  fs::path file = "create/slit.xml";
  BOOST_CHECK_NO_THROW(xml::create_from_file(root_group,file));

  BOOST_CHECK(get_node(root_group,"/scan").type() == Type::Group);
  BOOST_CHECK(get_node(root_group,"/scan/instrument").type() == Type::Group);
  BOOST_CHECK(get_node(root_group,"/scan/instrument/slit1").type() == Type::Group);

  std::string sbuffer;
  auto slit_group = get_node(root_group,"/scan/instrument/slit1");
  BOOST_CHECK(slit_group.attributes.size() == 1ul);
  auto as = slit_group.attributes["NX_class"];
  BOOST_CHECK(as.dataspace().type() == hdf5::dataspace::Type::Scalar);
  BOOST_CHECK(as.datatype().get_class() == hdf5::datatype::Class::String);
  as.read(sbuffer);
  BOOST_CHECK(sbuffer == std::string("NXslit"));

  BOOST_CHECK(get_node(root_group,"/scan/instrument/slit1/transformations/right").type() == Type::Dataset);
  BOOST_CHECK(get_node(root_group,"/scan/data/slit1_right").type() == Type::Dataset);
  BOOST_CHECK(root_group.get_dataset(
				     "/scan/instrument/slit1/transformations/right"
				     ).datatype().get_class() == hdf5::datatype::Class::Float);
  BOOST_CHECK(root_group.get_dataset(
				      "/scan/instrument/slit1/transformations/right"
				      ).attributes.size() == 4ul);

  auto av = root_group.get_dataset(
			     "/scan/instrument/slit1/transformations/right"
			      ).attributes["vector"];
  BOOST_CHECK(av.dataspace().type() == hdf5::dataspace::Type::Simple);
  BOOST_CHECK(av.datatype().get_class() == hdf5::datatype::Class::Float);
  hdf5::dataspace::Simple space(av.dataspace());
  BOOST_CHECK(space.rank() == 1u);
  BOOST_CHECK(space.current_dimensions()[0] == 3ul);
  using AttributeData = std::vector<double>;
  AttributeData buffer(3);
  av.read(buffer);
  AttributeData data = {1,0,0};
  BOOST_CHECK(buffer == data);

  auto au = root_group.get_dataset(
			      "/scan/instrument/slit1/transformations/right"
			      ).attributes["units"];
  BOOST_CHECK(au.dataspace().type() == hdf5::dataspace::Type::Scalar);
  BOOST_CHECK(au.datatype().get_class() == hdf5::datatype::Class::String);
  au.read(sbuffer);
  BOOST_CHECK(sbuffer == std::string("mm"));

  auto at = root_group.get_dataset(
			      "/scan/instrument/slit1/transformations/right"
			      ).attributes["transformation_type"];
  BOOST_CHECK(at.dataspace().type() == hdf5::dataspace::Type::Scalar);
  BOOST_CHECK(at.datatype().get_class() == hdf5::datatype::Class::String);
  at.read(sbuffer);
  BOOST_CHECK(sbuffer == std::string("translation"));

  auto ac = root_group.get_dataset(
			      "/scan/instrument/slit1/transformations/right"
			      ).attributes["type"];
  BOOST_CHECK(ac.dataspace().type() == hdf5::dataspace::Type::Scalar);
  BOOST_CHECK(ac.datatype().get_class() == hdf5::datatype::Class::String);
  ac.read(sbuffer);
  BOOST_CHECK(sbuffer == std::string("NX_FLOAT"));
}

BOOST_AUTO_TEST_CASE(add_filters)
{
  using hdf5::node::get_node;
  using hdf5::node::Type;

  bool blosc_av = hdf5::filter::is_filter_available(32001);
  bool bshuff_av = hdf5::filter::is_filter_available(32008);
  fs::path file = "create/filters.xml";
  std::cout << "AF0" << std::endl;
  BOOST_CHECK_NO_THROW(xml::create_from_file(root_group,file));
  std::cout << "AF1" << std::endl;

  // BOOST_CHECK(get_node(root_group,"/scan").type() == Type::Group);
  // BOOST_CHECK(get_node(root_group,"/scan/data").type() == Type::Group);
  // BOOST_CHECK(get_node(root_group,"/scan/data/pilatus").type() == Type::Dataset);
  // hdf5::node::Dataset dataset = root_group.get_dataset("/scan/data/pilatus");
  // std::cout << "AF2" << std::endl;
  // auto dcpl = dataset.creation_list();
  // std::cout << "AF3" << std::endl;

  // hdf5::filter::ExternalFilters filters;
  // auto flags = filters.fill(dcpl);
  // std::cout << "AF4: " << dcpl.nfilters() << " " << filters.size() << std::endl;
  // BOOST_CHECK(dcpl.nfilters() == (3u + unsigned(blosc_av) + unsigned(bshuff_av)));
  // BOOST_CHECK(flags.size() == (3u + unsigned(blosc_av) + unsigned(bshuff_av)));
  // BOOST_CHECK(filters.size() == (3u + unsigned(blosc_av) + unsigned(bshuff_av)));

  // BOOST_CHECK(filters[0].id() == H5Z_FILTER_SHUFFLE);

  // for(auto a: filters[0].cd_values()){
  //   std::cout <<"SHo: "<< a << std::endl;
  // }
  // BOOST_CHECK(filters[0].cd_values().size() == 1ul);  // ??
  // BOOST_CHECK(filters[0].cd_values()[0] == 2ul);      // ??
  // BOOST_CHECK(flags[0] == hdf5::filter::Availability::Optional);

  // BOOST_CHECK(filters[1].id() == H5Z_FILTER_DEFLATE);

  // std::vector<unsigned int> rate {4u};
  // BOOST_REQUIRE_EQUAL(filters[1].cd_values().size(), rate.size());
  // for(auto a: filters[1].cd_values()){
  //   std::cout <<"DEo: "<< a << std::endl;
  // }
  // for(size_t i = 0; i < rate.size(); ++i){
  //   BOOST_CHECK_EQUAL(filters[1].cd_values()[i], rate[i]);
  // }
  // BOOST_CHECK(flags[1] == hdf5::filter::Availability::Optional);

  // BOOST_CHECK(filters[2].id() == H5Z_FILTER_NBIT);

  // std::vector<unsigned int> nbit_opts {8u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};
  // BOOST_REQUIRE_EQUAL(filters[2].cd_values().size(), nbit_opts.size());
  // for(auto a: filters[2].cd_values()){
  //   std::cout <<"NBo: "<< a << std::endl;
  // }
  // for(size_t i = 0; i < nbit_opts.size(); ++i){
  //   BOOST_CHECK_EQUAL(filters[2].cd_values()[i], nbit_opts[i]);
  // }
  // BOOST_CHECK(flags[2] == hdf5::filter::Availability::Optional);

  // if(blosc_av){
  //   std::cout << "AF5 F4 : " << filters[3].id() << std::endl;
  //   BOOST_CHECK(filters[3].id() == 32001);

  //   std::vector<unsigned int> bl_opts {2u, 2u, 2u, 1048576u, 4u, 0u, 0u}; // ??
  //   BOOST_REQUIRE_EQUAL(filters[3].cd_values().size(), bl_opts.size());
  //   // for(size_t i = 4; i < bl_opts.size(); ++i){
  //   //   BOOST_CHECK_EQUAL(filters[3].cd_values()[i], bl_opts[i]);
  //   // }
  //   for(auto a: filters[3].cd_values()){
  //     std::cout <<"BLo: "<< a << std::endl;
  //   }
  //   BOOST_CHECK(flags[3] == hdf5::filter::Availability::Optional);
  // }
  // BOOST_CHECK(filters[4].id() == H5Z_FILTER_SZIP);
  // std::vector<unsigned int> szip_opts {137u, 16u, 16u, 512u}; // ??
  // BOOST_REQUIRE_EQUAL(filters[4].cd_values().size(), szip_opts.size());
  // for(auto a: filters[4].cd_values()){
  //   std::cout <<"SZo: "<< a << std::endl;
  // }
  // for(size_t i = 0; i < szip_opts.size(); ++i){
  //   BOOST_CHECK_EQUAL(filters[4].cd_values()[i], szip_opts[i]);
  // }
  // BOOST_CHECK(flags[4] == hdf5::filter::Availability::Optional);

  // if(bshuff_av){
  //   std::cout << "AF5 F5 : " << filters[4].id() << std::endl;
  //   BOOST_CHECK(filters[4].id() == 32008);

  //   std::vector<unsigned int> bs_opts {0u, 3u, 2u, 0u, 0u};    // ??
  //   BOOST_REQUIRE_EQUAL(filters[4].cd_values().size(), bs_opts.size());
  //   for(auto a: filters[4].cd_values()){
  //     std::cout <<"BSo: "<< a << std::endl;
  //   }
  //   // for(size_t i = 1; i < 3; ++i){
  //   //   BOOST_CHECK_EQUAL(filters[4].cd_values()[i], bs_opts[i]);
  //   // }
  //   BOOST_CHECK(flags[4] == hdf5::filter::Availability::Optional);
  // }


  std::cout << "AF6 " << std::endl;

}

BOOST_AUTO_TEST_CASE(add_filters_mandatory, * boost::unit_test::precondition(are_filters_installed))
{
  using hdf5::node::get_node;
  using hdf5::node::Type;
  fs::path file = "create/filters_mandatory.xml";
  // std::cout << "MF0" << std::endl;
  // BOOST_CHECK_NO_THROW(xml::create_from_file(root_group,file));
  // std::cout << "MF1" << std::endl;

  // BOOST_CHECK(get_node(root_group,"/scan").type() == Type::Group);
  // BOOST_CHECK(get_node(root_group,"/scan/data").type() == Type::Group);
  // BOOST_CHECK(get_node(root_group,"/scan/data/lambda").type() == Type::Dataset);
  // hdf5::node::Dataset dataset = root_group.get_dataset("/scan/data/lambda");
  // std::cout << "MF2" << std::endl;
  // auto dcpl = dataset.creation_list();
  // std::cout << "MF3" << std::endl;

  // hdf5::filter::ExternalFilters filters;
  // auto flags = filters.fill(dcpl);
  // std::cout << "MF4: " << dcpl.nfilters() << " " << filters.size() << std::endl;
  // BOOST_CHECK(dcpl.nfilters() == 2);
  // BOOST_CHECK(flags.size() == 2);
  // BOOST_CHECK(filters.size() == 2);


  // std::cout << "MF5 F0 : " << filters[0].id() << std::endl;
  // BOOST_CHECK(filters[0].id() == 32008);

  // std::vector<unsigned int> bs_opts {0u, 3u, 2u, 0u, 2u};    // ??
  // for(auto a: filters[0].cd_values()){
  //   std::cout <<"BSm: "<< a << std::endl;
  // }
  // BOOST_REQUIRE_EQUAL(filters[0].cd_values().size(), bs_opts.size());
  // for(size_t i = 1; i < 3; ++i){
  //   BOOST_CHECK_EQUAL(filters[0].cd_values()[i], bs_opts[i]);
  // }
  // BOOST_CHECK(flags[0] == hdf5::filter::Availability::Mandatory);

  // std::cout << "MF5 F1 : " << filters[1].id() << std::endl;
  // BOOST_CHECK(filters[1].id() == 32001);

  // std::vector<unsigned int> bl_opts {2u, 2u, 2u, 1048576u, 4u, 0u, 0u}; // ??
  // BOOST_REQUIRE_EQUAL(filters[1].cd_values().size(), bl_opts.size());
  // for(auto a: filters[1].cd_values()){
  //   std::cout <<"BLm: "<< a << std::endl;
  // }
  // for(size_t i = 4; i < bl_opts.size(); ++i){
  //   BOOST_CHECK_EQUAL(filters[1].cd_values()[i], bl_opts[i]);
  // }
  // BOOST_CHECK(flags[0] == hdf5::filter::Availability::Mandatory);
  std::cout << "MF6" << std::endl;

}

BOOST_AUTO_TEST_CASE(no_filters_mandatory, * boost::unit_test::precondition(are_filters_not_installed))
{
  using hdf5::node::get_node;
  using hdf5::node::Type;
  fs::path file = "create/filters_mandatory.xml";
  BOOST_CHECK_THROW(xml::create_from_file(root_group,file), pni::filter_not_available);
}
BOOST_AUTO_TEST_SUITE_END()

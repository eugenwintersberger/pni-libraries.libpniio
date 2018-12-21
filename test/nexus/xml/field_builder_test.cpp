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
// Created on: Dec 11, 2017
//
#include <boost/test/unit_test.hpp>
#include <h5cpp/hdf5.hpp>
#include <pni/io/nexus/xml/field_builder.hpp>
#include <pni/io/nexus/xml/node.hpp>
#include <pni/io/nexus/xml/object_builder.hpp>
#include <pni/io/nexus/algorithms.hpp>

using namespace pni::io::nexus;

struct FieldBuilderFixture
{
    hdf5::file::File file;
    hdf5::node::Group root_group;
    hdf5::node::Dataset dataset;
    hdf5::dataspace::Dataspace dataspace;
    hdf5::datatype::Datatype datatype;
    hdf5::property::DatasetCreationList dcpl;

    FieldBuilderFixture()
    {
      using namespace pni::io;
      using pni::core::type_id_t;
      file = hdf5::file::create("field_builder_test.nxs",
                                hdf5::file::AccessFlags::TRUNCATE);
      root_group = file.root();

      nexus::xml::Node n = nexus::xml::Node::from_file("field/input.xml");
      nexus::xml::ObjectBuilder builder(n);
      builder.build(root_group);


    }
};

BOOST_AUTO_TEST_SUITE(NexusXMLTest)
BOOST_AUTO_TEST_SUITE(FieldBuilderTest)

// simple structure creation without data

BOOST_FIXTURE_TEST_SUITE(TestConstructionWithoutData,FieldBuilderFixture)

BOOST_AUTO_TEST_CASE(test_scalar_fields)
{
  using namespace pni::io;
  using pni::core::type_id_t;

  dataset = hdf5::node::get_node(root_group,"/scalar_fields/uint8_field");
  BOOST_CHECK(nexus::get_type_id(dataset) == type_id_t::UINT8);

  dataset = hdf5::node::get_node(root_group,"/scalar_fields/uint16_field");
  BOOST_CHECK(nexus::get_type_id(dataset) == type_id_t::UINT16);

  dataset = hdf5::node::get_node(root_group,"/scalar_fields/uint32_field");
  BOOST_CHECK(nexus::get_type_id(dataset) == type_id_t::UINT32);

  dataset = hdf5::node::get_node(root_group,"/scalar_fields/uint64_field");
  BOOST_CHECK(nexus::get_type_id(dataset) == type_id_t::UINT64);

  dataset = hdf5::node::get_node(root_group,"/scalar_fields/int8_field");
  BOOST_CHECK(nexus::get_type_id(dataset) == type_id_t::INT8);

  dataset = hdf5::node::get_node(root_group,"/scalar_fields/int16_field");
  BOOST_CHECK(nexus::get_type_id(dataset) == type_id_t::INT16);

  dataset = hdf5::node::get_node(root_group,"/scalar_fields/int32_field");
  BOOST_CHECK(nexus::get_type_id(dataset) == type_id_t::INT32);

  dataset = hdf5::node::get_node(root_group,"/scalar_fields/int64_field");
  BOOST_CHECK(nexus::get_type_id(dataset) == type_id_t::INT64);

  dataset = hdf5::node::get_node(root_group,"/scalar_fields/float32_field");
  BOOST_CHECK(nexus::get_type_id(dataset) == type_id_t::FLOAT32);

  dataset = hdf5::node::get_node(root_group,"/scalar_fields/float64_field");
  BOOST_CHECK(nexus::get_type_id(dataset) == type_id_t::FLOAT64);

  dataset = hdf5::node::get_node(root_group,"/scalar_fields/float64_field");
  BOOST_CHECK(nexus::get_type_id(dataset) == type_id_t::FLOAT64);

  dataset = hdf5::node::get_node(root_group,"/scalar_fields/string_field");
  BOOST_CHECK(nexus::get_type_id(dataset) == type_id_t::STRING);
}

BOOST_AUTO_TEST_CASE(test_multidim_fields)
{
  using namespace pni::io;
  using pni::core::type_id_t;

  dataset = hdf5::node::get_node(root_group,"/multidim_field/data");
  dataspace = dataset.dataspace();
  BOOST_CHECK(dataspace.size() == 0);
  BOOST_CHECK(dataspace.type() == hdf5::dataspace::Type::SIMPLE);
  BOOST_CHECK(dataset.creation_list().layout() == hdf5::property::DatasetLayout::CHUNKED);
}



BOOST_AUTO_TEST_SUITE_END()

// now we have to test creation with data

BOOST_AUTO_TEST_SUITE(TestConstructionWithData)

BOOST_AUTO_TEST_SUITE_END()




BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

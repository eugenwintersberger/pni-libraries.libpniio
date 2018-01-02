//
// (c) Copyright 2018 DESY
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
// Created on: Jan 2, 2018
//
#include <boost/test/unit_test.hpp>
#include <pni/io/nexus.hpp>
#include <pni/core/types.hpp>

using namespace pni::io;
using namespace pni::core;

struct FieldTestFixture
{
  hdf5::file::File file;
  hdf5::node::Group root_group;
  hdf5::datatype::Datatype type;
  hdf5::dataspace::Simple simple_space;
  hdf5::dataspace::Scalar scalar_space;

  FieldTestFixture()
  {
    file = hdf5::file::create("FieldTest.nxs",hdf5::file::AccessFlags::TRUNCATE);
    root_group = file.root();

    type = hdf5::datatype::create<uint16>();
    simple_space = hdf5::dataspace::Simple({0,1024,1024},
                                           {hdf5::dataspace::Simple::UNLIMITED,1024,1024});
  }
};

//
// We only have to test field construction
// everything else should be already tested for datasets in h5pp
//

BOOST_FIXTURE_TEST_SUITE(FieldTests,FieldTestFixture)

//
// Testing simple fields
//
BOOST_AUTO_TEST_SUITE(FieldTest)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  nexus::Field field;
  BOOST_CHECK(!field.is_valid());
}

BOOST_AUTO_TEST_CASE(standard_constructor)
{
  nexus::Field field(root_group,"data",hdf5::datatype::create<uint16>(),
                     hdf5::dataspace::Scalar());
  BOOST_CHECK(field.is_valid());
  BOOST_CHECK(root_group.nodes.exists("data"));
}

BOOST_AUTO_TEST_CASE(test_with_invalid_name)
{
  BOOST_CHECK_THROW((nexus::Field(root_group,"Data",type,scalar_space)),std::runtime_error);
  BOOST_CHECK_THROW((nexus::Field(root_group,"sample data",type,scalar_space)),std::runtime_error);
}

BOOST_AUTO_TEST_CASE(copy_constructor)
{
  nexus::Field field(root_group,"data",type,scalar_space);
  nexus::Field field2(field);
  BOOST_CHECK(field2.is_valid());
  BOOST_CHECK_EQUAL(field2.link().path().name(),"data");

}

BOOST_AUTO_TEST_CASE(construct_from_node)
{
  nexus::Field field(root_group,"data",type,scalar_space);
  hdf5::node::Node &n = field;
  nexus::Field field2(n);
  BOOST_CHECK(field2.is_valid());
  BOOST_CHECK_EQUAL(field2.link().path().name(),"data");
}

BOOST_AUTO_TEST_CASE(convert_to_dataset)
{
  nexus::Field field(root_group,"data",type,scalar_space);
  hdf5::node::Dataset dataset(field);
}

BOOST_AUTO_TEST_SUITE_END()

//
// Testing chunked fields
//
BOOST_AUTO_TEST_SUITE(ChunkedFieldTest)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  nexus::ChunkedField field;
  BOOST_CHECK(!field.is_valid());
}

BOOST_AUTO_TEST_CASE(standard_constructor_auto_chunk)
{
  nexus::ChunkedField field(root_group,"data",type,simple_space);
  BOOST_CHECK(field.is_valid());
  BOOST_CHECK(root_group.nodes.exists("data"));
  hdf5::Dimensions chunk_dimensions = field.creation_list().chunk();
  BOOST_CHECK_EQUAL(chunk_dimensions[0],1);
  BOOST_CHECK_EQUAL(chunk_dimensions[1],1024);
  BOOST_CHECK_EQUAL(chunk_dimensions[2],1024);
}

BOOST_AUTO_TEST_CASE(test_with_invalid_name)
{
  BOOST_CHECK_THROW((nexus::ChunkedField(root_group,"Data",type,scalar_space)),std::runtime_error);
  BOOST_CHECK_THROW((nexus::ChunkedField(root_group,"sample data",type,scalar_space)),std::runtime_error);
}

BOOST_AUTO_TEST_CASE(copy_constructor)
{
  nexus::ChunkedField field(root_group,"data",type,simple_space);
  nexus::ChunkedField field2(field);
  BOOST_CHECK(field2.is_valid());
  BOOST_CHECK_EQUAL(field2.link().path().name(),"data");

}

BOOST_AUTO_TEST_CASE(construct_from_node)
{
  nexus::ChunkedField field(root_group,"data",type,simple_space);
  hdf5::node::Node &n = field;
  nexus::ChunkedField field2(n);
  BOOST_CHECK(field2.is_valid());
  BOOST_CHECK_EQUAL(field2.link().path().name(),"data");
}

BOOST_AUTO_TEST_CASE(convert_to_dataset)
{
  nexus::ChunkedField field(root_group,"data",type,simple_space);
  hdf5::node::Dataset dataset(field);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

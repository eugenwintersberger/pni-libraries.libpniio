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

struct FieldFactoryTestFixture
{
  hdf5::file::File file;
  hdf5::node::Group root_group;
  hdf5::datatype::Datatype type;
  hdf5::dataspace::Simple simple_space;
  hdf5::dataspace::Scalar scalar_space;

  FieldFactoryTestFixture()
  {
    file = nexus::create_file("FieldTest.nxs",hdf5::file::AccessFlags::TRUNCATE);
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

BOOST_FIXTURE_TEST_SUITE(FieldFactoryTests,FieldFactoryTestFixture)


BOOST_AUTO_TEST_CASE(standard_field_construction)
{
  hdf5::node::Dataset field = nexus::FieldFactory::create(root_group,"data",
                                                          type,scalar_space);
  BOOST_CHECK(field.is_valid());
  BOOST_CHECK(root_group.nodes.exists("data"));
}

BOOST_AUTO_TEST_CASE(standard_field_invalid_name)
{
  BOOST_CHECK_THROW((nexus::FieldFactory::create(root_group,"Data",type,scalar_space)),std::runtime_error);
  BOOST_CHECK_THROW((nexus::FieldFactory::create(root_group,"sample data",type,scalar_space)),std::runtime_error);
}


BOOST_AUTO_TEST_CASE(chunked_field_construction)
{
  hdf5::node::Dataset field = nexus::FieldFactory::create(root_group,"data",type,simple_space,{1,1024,1024});
  BOOST_CHECK(field.is_valid());
  BOOST_CHECK(root_group.nodes.exists("data"));
  hdf5::Dimensions chunk_dimensions = field.creation_list().chunk();
  BOOST_CHECK_EQUAL(chunk_dimensions[0],1);
  BOOST_CHECK_EQUAL(chunk_dimensions[1],1024);
  BOOST_CHECK_EQUAL(chunk_dimensions[2],1024);
}

BOOST_AUTO_TEST_CASE(chunked_field_invalid_name)
{
  BOOST_CHECK_THROW((nexus::FieldFactory::create(root_group,"Data",type,simple_space,{1,1024,1024})),std::runtime_error);
  BOOST_CHECK_THROW((nexus::FieldFactory::create(root_group,"sample data",type,simple_space,{1,1024,1024})),std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()

//
// (c) Copyright 2018 DESY
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
// Created on: Mar 5, 2018
//

#include <boost/test/unit_test.hpp>
#include <pni/nexus.hpp>

using namespace hdf5;
using namespace pni;

struct GetTypeIdFixture
{
    GetTypeIdFixture()
    {
      h5file = nexus::create_file("GetTypeId.nxs",hdf5::file::AccessFlags::Truncate);
      root_group = h5file.root();

    }

    hdf5::file::File h5file;
    hdf5::node::Group root_group;

    hdf5::attribute::Attribute attribute;
    hdf5::node::Dataset dataset;
    hdf5::datatype::Datatype dtype;

    hdf5::attribute::Attribute create_attribute(const hdf5::datatype::Datatype &type)
    {
      return root_group.attributes.create("test_attribute",type,hdf5::dataspace::Scalar());
    }

    hdf5::node::Dataset create_dataset(const hdf5::datatype::Datatype &type)
    {
      return hdf5::node::Dataset(root_group,"test_dataset",type,hdf5::dataspace::Scalar());
    }

};


BOOST_FIXTURE_TEST_SUITE(GetTypeIdTest,GetTypeIdFixture)

BOOST_AUTO_TEST_CASE(test_uint8)
{
  dtype = hdf5::datatype::create<pni::uint8>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK(nexus::get_type_id(attribute) == pni::type_id_t::UInt8);
  BOOST_CHECK(nexus::get_type_id(dataset) == pni::type_id_t::UInt8);
}

BOOST_AUTO_TEST_CASE(test_int8)
{
  dtype = hdf5::datatype::create<pni::int8>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK(nexus::get_type_id(attribute) == pni::type_id_t::Int8);
  BOOST_CHECK(nexus::get_type_id(dataset) == pni::type_id_t::Int8);
}

BOOST_AUTO_TEST_CASE(test_uint16)
{
  dtype = hdf5::datatype::create<pni::uint16>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK(nexus::get_type_id(attribute) == pni::type_id_t::UInt16);
  BOOST_CHECK(nexus::get_type_id(dataset) == pni::type_id_t::UInt16);
}

BOOST_AUTO_TEST_CASE(test_int16)
{
  dtype = hdf5::datatype::create<pni::int16>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK(nexus::get_type_id(attribute) == pni::type_id_t::Int16);
  BOOST_CHECK(nexus::get_type_id(dataset) == pni::type_id_t::Int16);
}

BOOST_AUTO_TEST_CASE(test_uint32)
{
  dtype = hdf5::datatype::create<pni::uint32>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK(nexus::get_type_id(attribute) == pni::type_id_t::UInt32);
  BOOST_CHECK(nexus::get_type_id(dataset) == pni::type_id_t::UInt32);
}

BOOST_AUTO_TEST_CASE(test_int32)
{
  dtype = hdf5::datatype::create<pni::int32>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK(nexus::get_type_id(attribute) == pni::type_id_t::Int32);
  BOOST_CHECK(nexus::get_type_id(dataset) == pni::type_id_t::Int32);
}

BOOST_AUTO_TEST_CASE(test_uint64)
{
  dtype = hdf5::datatype::create<pni::uint64>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK(nexus::get_type_id(attribute) == pni::type_id_t::UInt64);
  BOOST_CHECK(nexus::get_type_id(dataset) == pni::type_id_t::UInt64);
}

BOOST_AUTO_TEST_CASE(test_int64)
{
  dtype = hdf5::datatype::create<pni::int64>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK(nexus::get_type_id(attribute) == pni::type_id_t::Int64);
  BOOST_CHECK(nexus::get_type_id(dataset) == pni::type_id_t::Int64);
}

BOOST_AUTO_TEST_CASE(test_float32)
{
  dtype = hdf5::datatype::create<pni::float32>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK(nexus::get_type_id(attribute) == pni::type_id_t::Float32);
  BOOST_CHECK(nexus::get_type_id(dataset) == pni::type_id_t::Float32);
}

BOOST_AUTO_TEST_CASE(test_float64)
{
  dtype = hdf5::datatype::create<pni::float64>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK(nexus::get_type_id(attribute) == pni::type_id_t::Float64);
  BOOST_CHECK(nexus::get_type_id(dataset) == pni::type_id_t::Float64);
}

#if defined(__GNUG__)  && !defined(__arm__)
BOOST_AUTO_TEST_CASE(test_float128)
{
  dtype = hdf5::datatype::create<pni::float128>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK(nexus::get_type_id(attribute) == pni::type_id_t::Float128);
  BOOST_CHECK(nexus::get_type_id(dataset) == pni::type_id_t::Float128);
}
#endif

BOOST_AUTO_TEST_CASE(test_static_string)
{
  dtype = hdf5::datatype::String::fixed(10);
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK(nexus::get_type_id(attribute) == pni::type_id_t::String);
  BOOST_CHECK(nexus::get_type_id(dataset) == pni::type_id_t::String);
}

BOOST_AUTO_TEST_CASE(test_variable_string)
{
  dtype = hdf5::datatype::String::variable();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK(nexus::get_type_id(attribute) == pni::type_id_t::String);
  BOOST_CHECK(nexus::get_type_id(dataset) == pni::type_id_t::String);
}

BOOST_AUTO_TEST_SUITE_END()

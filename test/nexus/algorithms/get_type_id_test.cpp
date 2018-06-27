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
// Created on: Mar 5, 2018
//

#include <boost/test/unit_test.hpp>
#include <pni/io/nexus.hpp>

using namespace hdf5;
using namespace pni::io;

struct GetTypeIdFixture
{
    GetTypeIdFixture()
    {
      h5file = nexus::create_file("GetTypeId.nxs",hdf5::file::AccessFlags::TRUNCATE);
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
  dtype = hdf5::datatype::create<pni::core::uint8>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK_EQUAL(nexus::get_type_id(attribute),pni::core::type_id_t::UINT8);
  BOOST_CHECK_EQUAL(nexus::get_type_id(dataset),pni::core::type_id_t::UINT8);
}

BOOST_AUTO_TEST_CASE(test_int8)
{
  dtype = hdf5::datatype::create<pni::core::int8>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK_EQUAL(nexus::get_type_id(attribute),pni::core::type_id_t::INT8);
  BOOST_CHECK_EQUAL(nexus::get_type_id(dataset),pni::core::type_id_t::INT8);
}

BOOST_AUTO_TEST_CASE(test_uint16)
{
  dtype = hdf5::datatype::create<pni::core::uint16>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK_EQUAL(nexus::get_type_id(attribute),pni::core::type_id_t::UINT16);
  BOOST_CHECK_EQUAL(nexus::get_type_id(dataset),pni::core::type_id_t::UINT16);
}

BOOST_AUTO_TEST_CASE(test_int16)
{
  dtype = hdf5::datatype::create<pni::core::int16>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK_EQUAL(nexus::get_type_id(attribute),pni::core::type_id_t::INT16);
  BOOST_CHECK_EQUAL(nexus::get_type_id(dataset),pni::core::type_id_t::INT16);
}

BOOST_AUTO_TEST_CASE(test_uint32)
{
  dtype = hdf5::datatype::create<pni::core::uint32>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK_EQUAL(nexus::get_type_id(attribute),pni::core::type_id_t::UINT32);
  BOOST_CHECK_EQUAL(nexus::get_type_id(dataset),pni::core::type_id_t::UINT32);
}

BOOST_AUTO_TEST_CASE(test_int32)
{
  dtype = hdf5::datatype::create<pni::core::int32>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK_EQUAL(nexus::get_type_id(attribute),pni::core::type_id_t::INT32);
  BOOST_CHECK_EQUAL(nexus::get_type_id(dataset),pni::core::type_id_t::INT32);
}

BOOST_AUTO_TEST_CASE(test_uint64)
{
  dtype = hdf5::datatype::create<pni::core::uint64>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK_EQUAL(nexus::get_type_id(attribute),pni::core::type_id_t::UINT64);
  BOOST_CHECK_EQUAL(nexus::get_type_id(dataset),pni::core::type_id_t::UINT64);
}

BOOST_AUTO_TEST_CASE(test_int64)
{
  dtype = hdf5::datatype::create<pni::core::int64>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK_EQUAL(nexus::get_type_id(attribute),pni::core::type_id_t::INT64);
  BOOST_CHECK_EQUAL(nexus::get_type_id(dataset),pni::core::type_id_t::INT64);
}

BOOST_AUTO_TEST_CASE(test_float32)
{
  dtype = hdf5::datatype::create<pni::core::float32>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK_EQUAL(nexus::get_type_id(attribute),pni::core::type_id_t::FLOAT32);
  BOOST_CHECK_EQUAL(nexus::get_type_id(dataset),pni::core::type_id_t::FLOAT32);
}

BOOST_AUTO_TEST_CASE(test_float64)
{
  dtype = hdf5::datatype::create<pni::core::float64>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK_EQUAL(nexus::get_type_id(attribute),pni::core::type_id_t::FLOAT64);
  BOOST_CHECK_EQUAL(nexus::get_type_id(dataset),pni::core::type_id_t::FLOAT64);
}

#if !defined(_MSC_VER) && !defined(__arm__)
BOOST_AUTO_TEST_CASE(test_float128)
{
  dtype = hdf5::datatype::create<pni::core::float128>();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK_EQUAL(nexus::get_type_id(attribute),pni::core::type_id_t::FLOAT128);
  BOOST_CHECK_EQUAL(nexus::get_type_id(dataset),pni::core::type_id_t::FLOAT128);
}
#endif

BOOST_AUTO_TEST_CASE(test_static_string)
{
  dtype = hdf5::datatype::String::fixed(10);
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK_EQUAL(nexus::get_type_id(attribute),pni::core::type_id_t::STRING);
  BOOST_CHECK_EQUAL(nexus::get_type_id(dataset),pni::core::type_id_t::STRING);
}

BOOST_AUTO_TEST_CASE(test_variable_string)
{
  dtype = hdf5::datatype::String::variable();
  attribute = create_attribute(dtype);
  dataset = create_dataset(dtype);
  BOOST_CHECK_EQUAL(nexus::get_type_id(attribute),pni::core::type_id_t::STRING);
  BOOST_CHECK_EQUAL(nexus::get_type_id(dataset),pni::core::type_id_t::STRING);
}

BOOST_AUTO_TEST_SUITE_END()

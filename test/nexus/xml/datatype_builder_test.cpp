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
// Created on: Dec 13, 2017
//
#include <boost/test/unit_test.hpp>
#include <pni/nexus/xml/datatype_builder.hpp>
#include <pni/core/types.hpp>
#include <h5cpp/hdf5.hpp>

using namespace pni::io::nexus;
using namespace pni::core;

BOOST_AUTO_TEST_SUITE(DatatypeBuilderTest)

xml::Node create_field_node(const std::string &s)
{
  return xml::Node::from_string(s).get_child("field");
}

BOOST_AUTO_TEST_CASE(default_constructed)
{
  xml::DatatypeBuilder builder;
  BOOST_CHECK_THROW(builder.build(),std::runtime_error);
}

BOOST_AUTO_TEST_CASE(construct_uint8)
{
  xml::DatatypeBuilder builder(create_field_node("<field type=\"uint8\"/>"));
  BOOST_CHECK(builder.build() == hdf5::datatype::create<uint8>());
}

BOOST_AUTO_TEST_CASE(construct_int8)
{
  xml::DatatypeBuilder builder(create_field_node("<field type=\"int8\"/>"));
  BOOST_CHECK(builder.build() == hdf5::datatype::create<int8>());
}

BOOST_AUTO_TEST_CASE(construct_uint16)
{
  xml::DatatypeBuilder builder(create_field_node("<field type=\"uint16\"/>"));
  BOOST_CHECK(builder.build() == hdf5::datatype::create<uint16>());
}

BOOST_AUTO_TEST_CASE(construct_int16)
{
  xml::DatatypeBuilder builder(create_field_node("<field type=\"int16\"/>"));
  BOOST_CHECK(builder.build() == hdf5::datatype::create<int16>());
}

BOOST_AUTO_TEST_CASE(construct_uint32)
{
  xml::DatatypeBuilder builder(create_field_node("<field type=\"uint32\"/>"));
  BOOST_CHECK(builder.build() == hdf5::datatype::create<uint32>());
}

BOOST_AUTO_TEST_CASE(construct_int32)
{
  xml::DatatypeBuilder builder(create_field_node("<field type=\"int32\"/>"));
  BOOST_CHECK(builder.build() == hdf5::datatype::create<int32>());
}

BOOST_AUTO_TEST_CASE(construct_uint64)
{
  xml::DatatypeBuilder builder(create_field_node("<field type=\"uint64\"/>"));
  BOOST_CHECK(builder.build() == hdf5::datatype::create<uint64>());
}

BOOST_AUTO_TEST_CASE(construct_int64)
{
  xml::DatatypeBuilder builder(create_field_node("<field type=\"int64\"/>"));
  BOOST_CHECK(builder.build() == hdf5::datatype::create<int64>());
}

BOOST_AUTO_TEST_CASE(construct_float32)
{
  xml::DatatypeBuilder builder(create_field_node("<field type=\"float32\"/>"));
  BOOST_CHECK(builder.build() == hdf5::datatype::create<float32>());
}

BOOST_AUTO_TEST_CASE(construct_float64)
{
  xml::DatatypeBuilder builder(create_field_node("<field type=\"float64\"/>"));
  BOOST_CHECK(builder.build() == hdf5::datatype::create<float64>());
}

BOOST_AUTO_TEST_CASE(construct_float128)
{
  xml::DatatypeBuilder builder(create_field_node("<field type=\"float128\"/>"));
  BOOST_CHECK(builder.build() == hdf5::datatype::create<float128>());
}

BOOST_AUTO_TEST_CASE(construct_string)
{
  xml::DatatypeBuilder builder(create_field_node("<field type=\"string\"/>"));
  BOOST_CHECK(builder.build() == hdf5::datatype::create<std::string>());
}

BOOST_AUTO_TEST_CASE(construct_complex_fail)
{
  xml::DatatypeBuilder builder(create_field_node("<field type=\"complex32\"/>"));
  BOOST_CHECK_THROW(builder.build(),std::runtime_error);
}


BOOST_AUTO_TEST_SUITE_END()

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
#include <pni/nexus/xml/attribute_builder.hpp>
#include <pni/nexus/hdf5_support.hpp>

#include "builder_fixture.hpp"
using namespace pni::core;

struct ArrayAttributeFixture : public BuilderFixture
{
    hdf5::attribute::Attribute attribute;
    hdf5::dataspace::Simple dataspace;

    ArrayAttributeFixture():
      BuilderFixture("ArrayAttributesTest.nxs","array_attribute_test.xml")
    {}
};


BOOST_AUTO_TEST_SUITE(AttributeBuilderTest)

BOOST_FIXTURE_TEST_SUITE(ArrayAttributesTest,ArrayAttributeFixture)

BOOST_AUTO_TEST_CASE(test_uint8_attribute)
{
  using array_type = dynamic_array<uint8>;
  BOOST_CHECK(root_group.attributes.exists("uint8_attribute"));
  BOOST_CHECK_NO_THROW(attribute = root_group.attributes["uint8_attribute"]);
  BOOST_CHECK_NO_THROW(dataspace = attribute.dataspace());
  BOOST_CHECK(attribute.datatype()==hdf5::datatype::create<uint8>());
  auto data = array_type::create(dataspace.current_dimensions());
  attribute.read(data);
  BOOST_CHECK(data.size() == 3);
  BOOST_CHECK(data.rank() == 1);
  auto ref_data = array_type::create({3},{1,2,3});
  BOOST_CHECK_EQUAL_COLLECTIONS(data.begin(),data.end(),
                                ref_data.begin(),ref_data.end());


}

BOOST_AUTO_TEST_CASE(test_int8_attribute)
{
  using array_type = dynamic_array<int8>;
  BOOST_CHECK(root_group.attributes.exists("int8_attribute"));
  BOOST_CHECK_NO_THROW(attribute = root_group.attributes["int8_attribute"]);
  BOOST_CHECK(attribute.datatype()==hdf5::datatype::create<int8>());
  BOOST_CHECK_NO_THROW(dataspace = attribute.dataspace());
  auto ref_data = array_type::create({3},{-1,-2,-3});
  auto data = array_type::create(dataspace.current_dimensions());
  attribute.read(data);
  BOOST_CHECK(data.size() == 3);
  BOOST_CHECK_EQUAL_COLLECTIONS(data.begin(),data.end(),
                                ref_data.begin(),ref_data.end());

}

BOOST_AUTO_TEST_CASE(test_string_attribute)
{
  using array_type = dynamic_array<float32>;
  BOOST_CHECK(root_group.attributes.exists("float32_attribute"));
  BOOST_CHECK_NO_THROW(attribute = root_group.attributes["float32_attribute"]);
  BOOST_CHECK(attribute.datatype()==hdf5::datatype::create<float32>());
  BOOST_CHECK_NO_THROW(dataspace = attribute.dataspace());
  auto ref_data = array_type::create({3},{-1.2,-2.4,3.8});
  auto data = array_type::create(dataspace.current_dimensions());
  attribute.read(data);

  //I wonder how long this will work with floats
  BOOST_CHECK_EQUAL_COLLECTIONS(data.begin(),data.end(),
                                ref_data.begin(),ref_data.end());

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()


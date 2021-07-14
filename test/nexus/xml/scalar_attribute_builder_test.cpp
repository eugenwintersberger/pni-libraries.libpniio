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
#include <pni/nexus/xml/attribute_builder.hpp>

#include "builder_fixture.hpp"
using namespace pni;

struct ScalarAttributeFixture : public BuilderFixture
{
    hdf5::attribute::Attribute attribute;

    ScalarAttributeFixture():
      BuilderFixture("ScalarAttributesTest.nxs","scalar_attribute_test.xml")
    {}
};


BOOST_AUTO_TEST_SUITE(AttributeBuilderTest)

BOOST_FIXTURE_TEST_SUITE(ScalarAttributesTest,ScalarAttributeFixture)

BOOST_AUTO_TEST_CASE(test_uint8_attribute)
{
  BOOST_CHECK(root_group.attributes.exists("uint8_attribute"));
  BOOST_CHECK_NO_THROW(attribute = root_group.attributes["uint8_attribute"]);
  BOOST_CHECK(attribute.datatype()==hdf5::datatype::create<uint8>());
  uint8 data;
  attribute.read(data);
  BOOST_CHECK(data == 12);
  auto dataspace = attribute.dataspace();
  BOOST_CHECK(dataspace.type() == hdf5::dataspace::Type::SIMPLE);
  BOOST_CHECK(dataspace.size() == 1);

}

BOOST_AUTO_TEST_CASE(test_int32_attribute)
{
  BOOST_CHECK(root_group.attributes.exists("int32_attribute"));
  BOOST_CHECK_NO_THROW(attribute = root_group.attributes["int32_attribute"]);
  BOOST_CHECK(attribute.datatype()==hdf5::datatype::create<int32>());
  int32 data;
  attribute.read(data);
  BOOST_CHECK(data == -12);
  auto dataspace = attribute.dataspace();
  BOOST_CHECK(dataspace.type() == hdf5::dataspace::Type::SIMPLE);
  BOOST_CHECK(dataspace.size() == 1);
}

BOOST_AUTO_TEST_CASE(test_string_attribute)
{
  BOOST_CHECK(root_group.attributes.exists("string_attribute"));
  BOOST_CHECK_NO_THROW(attribute = root_group.attributes["string_attribute"]);
  BOOST_CHECK(attribute.datatype()==hdf5::datatype::create<std::string>());
  std::string data;
  attribute.read(data);
  BOOST_CHECK(data == "hello");
  auto dataspace = attribute.dataspace();
  BOOST_CHECK(dataspace.type() == hdf5::dataspace::Type::SCALAR);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()


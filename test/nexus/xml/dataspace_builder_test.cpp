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
#include <pni/nexus/xml/dataspace_builder.hpp>

using namespace pni::io::nexus;
using hdf5::dataspace::Simple;


BOOST_AUTO_TEST_SUITE(DataspaceBuilderTest)

BOOST_AUTO_TEST_CASE(default_constructed)
{
  xml::DataspaceBuilder builder;
  Simple space = builder.build();
  BOOST_CHECK(space.size() == 1);
}

BOOST_AUTO_TEST_CASE(test_case_1)
{
  xml::DataspaceBuilder builder(xml::Node::from_file("dimensions/dim1.xml"));
  Simple space = builder.build();
  BOOST_CHECK(space.size() == 55*100);
  hdf5::Dimensions current = space.current_dimensions();
  BOOST_CHECK(current.size() == 2);
}

BOOST_AUTO_TEST_CASE(test_case_2)
{
  xml::DataspaceBuilder builder(xml::Node::from_file("dimensions/dim2.xml"));
  BOOST_CHECK_THROW(builder.build(),std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_case_3)
{
  xml::DataspaceBuilder builder(xml::Node::from_file("dimensions/dim3.xml"));
  BOOST_CHECK_THROW(builder.build(),pni::core::key_error);
}

BOOST_AUTO_TEST_CASE(test_case_4)
{
  xml::DataspaceBuilder builder(xml::Node::from_file("dimensions/dim4.xml"));
  BOOST_CHECK_THROW(builder.build(),pni::core::key_error);
}

BOOST_AUTO_TEST_CASE(test_case_5)
{
  xml::DataspaceBuilder builder(xml::Node::from_file("dimensions/dim5.xml"));
  BOOST_CHECK_THROW(builder.build(),pni::core::key_error);
}

BOOST_AUTO_TEST_CASE(test_case_6)
{
  xml::DataspaceBuilder builder(xml::Node::from_file("dimensions/dim6.xml"));
  BOOST_CHECK_THROW(builder.build(),std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()

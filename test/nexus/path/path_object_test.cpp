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
// Created on: Dec 18, 2017
//
#include <boost/test/unit_test.hpp>
#include <pni/io/nexus.hpp>
#include <pni/io/nexus/path.hpp>
#include <h5cpp/hdf5.hpp>

using namespace pni::io;

struct PathObjectFixture
{
    hdf5::file::File file;
    hdf5::node::Group group;
    hdf5::node::Dataset dataset;
    hdf5::attribute::Attribute attribute;

    PathObjectFixture()
    {
      file = nexus::create_file("PathObjectTest.nxs",hdf5::file::AccessFlags::TRUNCATE);
      group = file.root();
      dataset = hdf5::node::Dataset(group,"data",hdf5::datatype::create<int>(),
                                                 hdf5::dataspace::Scalar());

    }
};


BOOST_AUTO_TEST_SUITE(PathTest)
BOOST_FIXTURE_TEST_SUITE(PathObjectTest,PathObjectFixture)
BOOST_AUTO_TEST_CASE(default_construction)
{
  nexus::PathObject object;
  BOOST_TEST(object.type() == nexus::PathObject::Type::NONE);
}

BOOST_AUTO_TEST_CASE(attribute_construction)
{
  nexus::PathObject object = group.attributes["NX_class"];
  BOOST_TEST(object.type() == nexus::PathObject::Type::ATTRIBUTE);
  BOOST_CHECK(nexus::is_attribute(object));

  hdf5::attribute::Attribute attr = object;
  BOOST_TEST(attr.name() == "NX_class");
}

BOOST_AUTO_TEST_CASE(group_construction)
{
  nexus::PathObject object = group;
  BOOST_TEST(object.type() == nexus::PathObject::Type::GROUP);
  BOOST_CHECK(nexus::is_group(object));

  hdf5::node::Group g = object;
  BOOST_TEST(g.link().path() == "/");

  BOOST_CHECK_THROW(attribute = object,std::runtime_error);
}

BOOST_AUTO_TEST_CASE(dataset_construction)
{
  nexus::PathObject object = dataset;
  BOOST_TEST(object.type() == nexus::PathObject::Type::DATASET);
  BOOST_CHECK(nexus::is_dataset(object));

  hdf5::node::Dataset d = object;
  BOOST_TEST(d.link().path() == "/data");
}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

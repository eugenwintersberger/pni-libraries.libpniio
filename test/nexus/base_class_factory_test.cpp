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
// Created on: Dec 7, 2017
//
#include <boost/test/unit_test.hpp>
#include <pni/io/nexus/base_class_factory.hpp>
#include <pni/io/nexus/file.hpp>

using namespace pni::io;

struct BaseClassFactoryTestFixture
{
    hdf5::file::File nexus_file;
    hdf5::node::Group root_group;
    hdf5::node::Dataset dataset;
    hdf5::node::Group invalid_group;

    BaseClassFactoryTestFixture()
    {
      using hdf5::file::AccessFlags;
      nexus_file = nexus::create_file("base_class_factory_test.nxs",AccessFlags::TRUNCATE);
      root_group = nexus_file.root();
    }
};

BOOST_FIXTURE_TEST_SUITE(BaseClassFactoryTest,BaseClassFactoryTestFixture)

BOOST_AUTO_TEST_CASE(base_class_construction)
{
  hdf5::node::Group entry = nexus::BaseClassFactory::create(root_group,"run_01","NXentry");
  BOOST_CHECK(entry.attributes.exists("NX_class"));
  std::string class_name;
  entry.attributes["NX_class"].read(class_name);
  BOOST_CHECK(class_name == "NXentry");
}

BOOST_AUTO_TEST_CASE(base_class_with_invalid_name)
{
}

BOOST_AUTO_TEST_SUITE_END()

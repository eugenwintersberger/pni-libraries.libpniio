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
// Created on: Dec 7, 2017
//
#include <boost/test/unit_test.hpp>
#include <pni/nexus/file.hpp>

using namespace hdf5;
using namespace pni;


BOOST_AUTO_TEST_SUITE(NexusFileTest)

//
// we only need to check the appropriate attribute settings
// the funcitionality of hdf5::file::create function has already been
// tested in the h5cpp library
//

BOOST_AUTO_TEST_SUITE(CreationTests)

BOOST_AUTO_TEST_CASE(test_creation)
{
  file::File f = nexus::create_file("test_creation.nxs",file::AccessFlags::TRUNCATE);
  node::Group root_group = f.root();

  //check if all attributes are available
  BOOST_CHECK(root_group.attributes.exists("NX_class"));
  BOOST_CHECK(root_group.attributes.exists("file_time"));
  BOOST_CHECK(root_group.attributes.exists("file_update_time"));
  BOOST_CHECK(root_group.attributes.exists("file_name"));

  //check the content of some of the attributes
  std::string attribute_content;
  BOOST_CHECK_NO_THROW(root_group.attributes["NX_class"].read(attribute_content));
  BOOST_CHECK(attribute_content == "NXroot");
  BOOST_CHECK_NO_THROW(root_group.attributes["file_name"].read(attribute_content));
  BOOST_CHECK(attribute_content == "test_creation.nxs");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

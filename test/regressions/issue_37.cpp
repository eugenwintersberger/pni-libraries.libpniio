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
// Created on: Mar 19, 2018
//
#include <boost/test/unit_test.hpp>
#include <h5cpp/hdf5.hpp>
#include <pni/nexus.hpp>
#include <algorithm>

using namespace pni;

class RegressionIssue37
{
  protected:
    hdf5::file::File nxfile;
    hdf5::node::Group root_group;
    hdf5::node::Group detector_group;



  public:
    RegressionIssue37();

};

RegressionIssue37::RegressionIssue37()
{

  nxfile = hdf5::file::open("eiger_master_stripped.h5",
                            hdf5::file::AccessFlags::READONLY);
  root_group = nxfile.root();
  nexus::GroupList groups = nexus::get_objects(root_group,nexus::Path::from_string("/:NXentry/:NXinstrument/:NXdetector"));
  if(groups.size() == 1)
    detector_group = groups.front();

}

BOOST_FIXTURE_TEST_SUITE(RegressionIssue37Test,RegressionIssue37)

BOOST_AUTO_TEST_CASE(test_read_detector_description)
{
  hdf5::node::Dataset description = detector_group.nodes["description"];
  //
  // we need to read with the appropriate datatype
  //
  std::string description_value;
  hdf5::dataspace::Scalar mem_space = description.dataspace();
  hdf5::datatype::String  mem_type  = description.datatype();
  BOOST_CHECK_NO_THROW(description.read(description_value,mem_type,mem_space));

  //
  // we need to trim the string here - it is stored as a fixed size string with
  // a size of 17 and \0 padding. This is obviously longer than the expected
  // string. Thus the comparison would fail if we do not remove the trailing
  // \0.
  //
  description_value.erase(std::find(description_value.begin(),description_value.end(),'\0'));
  std::string expected = "Dectris Eiger 4M";
  BOOST_CHECK(description_value.size() == expected.size());
  BOOST_CHECK(description_value == expected);
}

BOOST_AUTO_TEST_SUITE_END()

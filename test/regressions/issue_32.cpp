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
// Created on: Mar 19, 2018
//
#include <boost/test/unit_test.hpp>
#include <h5cpp/hdf5.hpp>
#include <pni/io/nexus.hpp>

using namespace pni::io;

class RegressionIssue32
{
  protected:
    hdf5::file::File nxfile;
    hdf5::node::Group root_group;
    hdf5::Dimensions stack_dimensions;
    hdf5::node::Dataset image_stack;
  public:
    RegressionIssue32();

};

RegressionIssue32::RegressionIssue32()
{
  nxfile = nexus::create_file("RegressionIssue32.nxs",hdf5::file::AccessFlags::TRUNCATE);
  root_group = nxfile.root();

  //
  // create the image stack
  //
  stack_dimensions = hdf5::Dimensions{0,1556,516};

  hdf5::property::LinkCreationList lcpl;
  hdf5::property::DatasetCreationList dcpl;
  dcpl.layout(hdf5::property::DatasetLayout::CHUNKED);
  dcpl.chunk(hdf5::Dimensions{1,1556,516});

  hdf5::datatype::Datatype dtype = hdf5::datatype::create<unsigned short>();
  hdf5::dataspace::Simple dspace(stack_dimensions,hdf5::Dimensions{hdf5::dataspace::Simple::UNLIMITED,1556,516});
  image_stack = hdf5::node::Dataset(root_group,hdf5::Path("data"),dtype,dspace,lcpl,dcpl);
}

BOOST_FIXTURE_TEST_SUITE(RegressionIssue32Test,RegressionIssue32)

BOOST_AUTO_TEST_CASE(test_growth)
{

  for(size_t image_index = 0; image_index < 3000; image_index++)
  {
    image_stack.extent(0,1); // grow by one
    BOOST_TEST(image_stack.dataspace().size() == ((image_index+1)*(1556*516)));
  }
}

BOOST_AUTO_TEST_SUITE_END()

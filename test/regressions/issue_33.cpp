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

class RegressionIssue33
{
  protected:
    hdf5::file::File nxfile;
    hdf5::node::Group root_group;
    hdf5::Dimensions stack_dimensions;
    hdf5::node::Dataset image_stack;

    static void create_external_file();
  public:
    RegressionIssue33();

};

void RegressionIssue33::create_external_file()
{
  hdf5::file::File f = nexus::create_file("RegressionIssue33_data.nxs",
                                          hdf5::file::AccessFlags::TRUNCATE);
  hdf5::node::Group r = f.root();

  hdf5::dataspace::Simple dspace = hdf5::dataspace::Simple(hdf5::Dimensions{1024,1024});
  hdf5::datatype::Datatype dtype = hdf5::datatype::create<unsigned short>();

  hdf5::node::Dataset(r,hdf5::Path("data"),dtype,dspace);

}

RegressionIssue33::RegressionIssue33()
{
  create_external_file();

  nxfile = nexus::create_file("RegressionIssue33.nxs",hdf5::file::AccessFlags::TRUNCATE);
  root_group = nxfile.root();

  boost::filesystem::path ext_file("RegressionIssue33_data.nxs");
  hdf5::Path target_path("/data");
  hdf5::node::link(ext_file,target_path,root_group,hdf5::Path("external_data"));
}

BOOST_FIXTURE_TEST_SUITE(RegressionIssue33Test,RegressionIssue33)

BOOST_AUTO_TEST_CASE(test_get_parent)
{
  hdf5::node::Dataset dataset = root_group.nodes["external_data"];
  BOOST_CHECK(dataset.link().path() == hdf5::Path("/external_data"));
  hdf5::node::LinkTarget target = dataset.link().target();
  BOOST_CHECK(target.file_path() == boost::filesystem::path("RegressionIssue33_data.nxs"));
  BOOST_CHECK(target.object_path() == hdf5::Path("/data"));
  BOOST_CHECK(dataset.link().parent().link().path() == hdf5::Path("/"));
}

BOOST_AUTO_TEST_SUITE_END()

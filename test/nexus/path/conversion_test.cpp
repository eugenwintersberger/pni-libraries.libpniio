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
#include <h5cpp/hdf5.hpp>

using namespace pni::io;

BOOST_AUTO_TEST_SUITE(PathTest)

BOOST_AUTO_TEST_SUITE(ConversionTest)

BOOST_AUTO_TEST_CASE(from_hdf5_to_nexus_1)
{
  hdf5::Path h5p = "/entry/instrument/detector/data";
  nexus::Path nxp = h5p;
  BOOST_CHECK_EQUAL(nexus::Path::to_string(nxp),"/entry/instrument/detector/data");
  BOOST_CHECK(nexus::is_absolute(nxp));
  BOOST_CHECK_EQUAL(nxp.size(),5);
}

BOOST_AUTO_TEST_CASE(from_hdf5_to_nexus_2)
{
  hdf5::Path h5p = "entry/instrument";
  nexus::Path nxp = h5p;
  BOOST_CHECK_EQUAL(nexus::Path::to_string(nxp),"entry/instrument");
  BOOST_CHECK_EQUAL(nxp.size(),2);
}

BOOST_AUTO_TEST_CASE(from_hdf5_to_nexus_3)
{
  hdf5::Path h5p = "/";
  nexus::Path nxp = h5p;
  BOOST_CHECK_EQUAL(nexus::Path::to_string(nxp),"/");
  BOOST_CHECK(nexus::is_absolute(nxp));
  BOOST_CHECK_EQUAL(nxp.size(),1);
}

//=============================================================================

BOOST_AUTO_TEST_CASE(from_nexus_to_hdf5_1)
{
  nexus::Path nxp = nexus::Path::from_string("/entry:NXentry/instrument:NXinstrument");
  hdf5::Path h5p = nxp;
  BOOST_CHECK_EQUAL(h5p,"/entry/instrument");
  BOOST_CHECK_EQUAL(h5p.size(),2);
  BOOST_CHECK(h5p.absolute());
}

BOOST_AUTO_TEST_CASE(from_nexus_to_hdf5_2)
{
  nexus::Path nxp = nexus::Path::from_string("entry:NXentry/instrument:NXinstrument/detector:NXdetector");
  hdf5::Path h5p = nxp;
  BOOST_CHECK_EQUAL(h5p,"entry/instrument/detector");
  BOOST_CHECK_EQUAL(h5p.size(),3);
  BOOST_CHECK(!h5p.absolute());
}

BOOST_AUTO_TEST_CASE(from_nexus_to_hdf5_3)
{
  nexus::Path nxp = nexus::Path::from_string("entry:NXentry/:NXinstrument/detector:NXdetector");
  BOOST_CHECK_THROW((hdf5::Path(nxp)),std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Mar 11, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/io/nexus/path.hpp>

using namespace pni::core;
using namespace pni::io::nexus;

BOOST_AUTO_TEST_SUITE(PathTest)
BOOST_AUTO_TEST_SUITE(PathUtilitiesTest)
BOOST_AUTO_TEST_SUITE(JoinTest)

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_both_empty)
{
  BOOST_CHECK(is_empty(join(Path(),Path())));
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_a_empty)
{
  string b_str = "/entry:NXentry/:NXinstrument";
  Path j;

  BOOST_CHECK_NO_THROW(j = join(Path(),Path::from_string(b_str)));
  BOOST_TEST(Path::to_string(j) == b_str);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_b_empty)
{
  string a_str = "filename.nxs://scan_1/:NXinstrument";
  Path j;
  BOOST_CHECK_NO_THROW(j = join(Path::from_string(a_str), Path()));
  BOOST_TEST(Path::to_string(j) == a_str);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_a_attribute)
{
  Path b = Path::from_string(":NXinstrument/:NXdetector");
  Path a = Path::from_string("data@units");
  BOOST_CHECK_THROW(join(a,b),value_error);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_b_absolute)
{
  Path a = Path::from_string("filename.nxs://:NXentry");
  Path b = Path::from_string("/entry/instrument");
  BOOST_CHECK_THROW(join(a,b),value_error);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_b_filename)
{
  Path a = Path::from_string("filename.nxs://:NXentry");
  Path b = Path::from_string("filename.nxs://entry/instrument");
  BOOST_CHECK_THROW(join(a,b),value_error);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_join_simple)
{
  Path a = Path::from_string("filename.nxs://:NXentry");
  Path b = Path::from_string("instrument/:NXdetector");
  Path j;
  string expect = "filename.nxs://:NXentry/instrument/:NXdetector";
  BOOST_CHECK_NO_THROW(j = join(a,b));
  BOOST_TEST(Path::to_string(j) == expect);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_join_with_attribute)
{
  Path a = Path::from_string("filename.nxs://:NXentry");
  Path b = Path::from_string("instrument/:NXdetector/data@units");
  Path j;
  string expect = "filename.nxs://:NXentry/instrument/:NXdetector/data@units";
  BOOST_CHECK_NO_THROW(j = join(a,b));
  BOOST_TEST(Path::to_string(j) == expect);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

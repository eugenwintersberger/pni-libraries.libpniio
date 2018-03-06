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
//  Created on: Sep 11, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/io/nexus/path.hpp>

using namespace pni::core;
using namespace pni::io::nexus;

BOOST_AUTO_TEST_SUITE(PathTest)
BOOST_AUTO_TEST_SUITE(PathUtilitiesTest)
BOOST_AUTO_TEST_SUITE(MakeRelativeTest)

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_1)
{
  Path p1 = Path::from_string("/:NXentry");
  Path p2 = Path::from_string("/:NXentry/instrument:NXinstrument");

  Path p2r = make_relative(p1,p2);
  BOOST_CHECK_EQUAL(p2r,Path::from_string("instrument:NXinstrument"));
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_2)
{
  Path parent = Path::from_string("/:NXentry");
  Path orig = Path::from_string("/");

  BOOST_CHECK_THROW(make_relative(parent,orig),std::runtime_error);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_3)
{
  Path parent = Path::from_string("/:NXentry");
  Path orig   = Path::from_string("/:NXentry");

  BOOST_CHECK_EQUAL(Path::to_string(make_relative(parent,orig)),"");
}

BOOST_AUTO_TEST_CASE(test_4)
{
  Path parent = Path::from_string("/");
  Path orig = Path::from_string("/@NX_class");

  BOOST_CHECK_EQUAL(Path::to_string(make_relative(parent,orig)),"@NX_class");

}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

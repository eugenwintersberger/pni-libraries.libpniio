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
BOOST_AUTO_TEST_SUITE(IsUniqueTest)

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_yes)
{
  BOOST_CHECK(is_unique(Path::from_string("/entry/instrument:NXinstrument/detector")));
  BOOST_CHECK(is_unique(Path::from_string("entry/instrument:NXinstrument/detector")));
  BOOST_CHECK(is_unique(Path::from_string("entry/instrument:NXinstrument/detector:NXdetector")));
  BOOST_CHECK(is_unique(Path::from_string("/")));
  BOOST_CHECK(is_unique(Path::from_string("/:NXroot")));
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_no)
{
  BOOST_CHECK(!is_unique(Path::from_string("/entry/:NXinstrument/detector")));
  BOOST_CHECK(!is_unique(Path::from_string("entry:NXentry/instrument:NXinstrument/:NXdetector")));
  BOOST_CHECK(!is_unique(Path::from_string("/:NXentry/instrument:NXinstrument/detector:NXdetector")));
  BOOST_CHECK(!is_unique(Path::from_string(":NXroot")));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()


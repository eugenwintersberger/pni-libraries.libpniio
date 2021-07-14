//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Feb 27, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/nexus/path.hpp>

using namespace pni;
using namespace pni::nexus;

BOOST_AUTO_TEST_SUITE(PathTest)
BOOST_AUTO_TEST_SUITE(PathUtilitiesTest)
BOOST_AUTO_TEST_SUITE(HasAttributeTest)

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_yes)
{
  BOOST_CHECK(has_attribute_section(Path::from_string("test.nxs://@date")));
  BOOST_CHECK(has_attribute_section(Path::from_string("/@name")));
  BOOST_CHECK(has_attribute_section(Path::from_string("data@name")));
  BOOST_CHECK(has_attribute_section(Path::from_string(":NXinstrument@name")));
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_no)
{
  BOOST_CHECK(!has_attribute_section(Path::from_string("../")));
  BOOST_CHECK(!has_attribute_section(Path::from_string("./")));
  BOOST_CHECK(!has_attribute_section(Path::from_string(":NXinstrument")));
  BOOST_CHECK(!has_attribute_section(Path::from_string("instrument")));
  BOOST_CHECK(!has_attribute_section(Path::from_string("instrument:NXinstrument")));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()


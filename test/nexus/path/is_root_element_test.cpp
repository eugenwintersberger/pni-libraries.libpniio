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
//  Created on: Feb 26, 2015
//      Author: Eugen Wintersberger
//

#include "../../boost_unit_test.hpp"
#include <pni/nexus/path.hpp>

using namespace pni;
using namespace pni::nexus;

BOOST_AUTO_TEST_SUITE(PathTest)
BOOST_AUTO_TEST_SUITE(PathUtilitiesTest)
BOOST_AUTO_TEST_SUITE(IsRootElementTest)

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_full)
{
  BOOST_CHECK(is_root_element(object_element("/","NXroot")));
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_only_name)
{
  BOOST_CHECK(!is_root_element(object_element("/","")));
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_only_type)
{
  BOOST_CHECK(!is_root_element(object_element("","NXroot")));
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_not_root)
{
  BOOST_CHECK(!is_root_element(object_element("detector","NXdetector")));

}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_error)
{
  BOOST_CHECK_THROW(is_root_element(Path::Element{"",""}),
                    value_error);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

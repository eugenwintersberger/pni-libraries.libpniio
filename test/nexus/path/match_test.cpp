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
//  Created on: Mar 26, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/included/unit_test.hpp>
#include <pni/types.hpp>
#include <pni/nexus/path.hpp>

using namespace pni;
using namespace pni::nexus;

BOOST_AUTO_TEST_SUITE(PathTest)
BOOST_AUTO_TEST_SUITE(MatchTest)

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_1)
{
  Path p1 = Path::from_string(":NXentry/:NXinstrument/:NXdetector");
  Path p2 = Path::from_string("entry:NXentry/instrument:NXinstrument/detector:NXdetector");
  BOOST_CHECK(match(p1,p2));

  p2 = Path::from_string("scan_1:NXentry/instrument/detector:NXdetector");
  BOOST_CHECK(!match(p1,p2));
}

//------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_11)
{
  Path p1 = Path::from_string("entry:NXentry/instrument:NXinstrument/detector:NXdetector/data");
  Path p2 = Path::from_string("entry/instrument/detector/data");
  BOOST_CHECK(match(p1,p2));
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_2)
{
  Path p1 = Path::from_string("entry/:NXinstrument/detector_1");
  Path p2 = Path::from_string("entry/beamline:NXinstrument/detector_1");
  BOOST_CHECK(match(p1,p2));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

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

#include <boost/test/included/unit_test.hpp>
#include <pni/nexus/path.hpp>

using namespace pni;
using namespace pni::nexus;

struct SplitPathFixture
{
    Path p,p1,p2;

    SplitPathFixture():
        p(Path::from_string("test.nxs://:NXentry/:NXinstrument/detector@NX_class")),
        p1(),
        p2()
    {}
};

BOOST_AUTO_TEST_SUITE(PathTest)
BOOST_AUTO_TEST_SUITE(PathUtilitiesTest)
BOOST_FIXTURE_TEST_SUITE(SplitPathTest,SplitPathFixture)

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_standard)
{
  BOOST_CHECK_NO_THROW(split_path(p,3,p1,p2));
  BOOST_CHECK(Path::to_string(p1) == "test.nxs://:NXentry/:NXinstrument");
  BOOST_CHECK(Path::to_string(p2) == "detector@NX_class");
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_at_root)
{
  BOOST_CHECK_NO_THROW(split_path(p,0,p1,p2));
  BOOST_CHECK(Path::to_string(p1) == "test.nxs");
  BOOST_CHECK(Path::to_string(p2) == "/:NXentry/:NXinstrument/detector@NX_class");
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_index_error)
{
  BOOST_CHECK_THROW(split_path(p,10,p1,p2),index_error);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

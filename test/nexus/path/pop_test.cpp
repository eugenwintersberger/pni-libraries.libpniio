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
//  Created on: Feb 27, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/types.hpp>
#include <pni/arrays.hpp>
#include <pni/nexus/path.hpp>

using namespace pni::core;
using namespace pni::io::nexus;

struct PopTestFixture
{
    Path p;

    PopTestFixture():
        p(Path::from_string(":NXentry/:NXinstrument/:NXdetector"))
    {}
};

BOOST_AUTO_TEST_SUITE(PathTest)
BOOST_FIXTURE_TEST_SUITE(PopTest,PopTestFixture)

BOOST_AUTO_TEST_CASE(test_front)
{
  Path::Element e = p.front();
  p.pop_front();
  BOOST_CHECK(p.size() == 2);
  BOOST_CHECK(Path::to_string(p) == ":NXinstrument/:NXdetector");
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_back)
{
  Path::Element e = p.back();
  p.pop_back();
  BOOST_CHECK(p.size() == 2);
  BOOST_CHECK(Path::to_string(p) == ":NXentry/:NXinstrument");
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_front_back)
{
  p.pop_front();
  p.pop_back();
  BOOST_CHECK(Path::to_string(p) == ":NXinstrument");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()


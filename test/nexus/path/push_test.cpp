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

struct PushTestFixture
{
    Path p;
    
    PushTestFixture():
        p(Path::from_string(":NXinstrument"))
    {}
};

BOOST_AUTO_TEST_SUITE(PathTest)
BOOST_FIXTURE_TEST_SUITE(PushTest,PushTestFixture)

BOOST_AUTO_TEST_CASE(test_front)
{
  p.push_front(object_element("","NXentry"));
  BOOST_CHECK(Path::to_string(p) == ":NXentry/:NXinstrument");
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_back)
{
  p.push_back(object_element("","NXdetector"));
  BOOST_CHECK(Path::to_string(p) == ":NXinstrument/:NXdetector");
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_front_back)
{
  p.push_front(object_element("","NXentry"));
  p.push_back(object_element("","NXdetector"));
  BOOST_CHECK(Path::to_string(p) == ":NXentry/:NXinstrument/:NXdetector");
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_root_front)
{
  p.push_front(object_element("/","NXroot"));
  BOOST_CHECK(Path::to_string(p) == "/:NXinstrument");
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_root_back)
{
  Path::Element root{"/","NXroot" };
  BOOST_CHECK_THROW(p.push_back(root),value_error);

  p = Path();
  BOOST_CHECK_NO_THROW(p.push_back(root));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

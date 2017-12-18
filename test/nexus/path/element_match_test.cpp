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
//  Created on: Mar 26, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/io/nexus/path.hpp>

using namespace pni::core;
using namespace pni::io::nexus;

BOOST_AUTO_TEST_SUITE(PathTest)
BOOST_AUTO_TEST_SUITE(ElementMatchTest)

using Element = Path::Element;

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_rule_1)
{
  BOOST_CHECK(match(Element("entry","NXentry"),
                    Element("entry","NXentry")));

  BOOST_CHECK(!match(Element("scan_1","NXentry"),
                     Element("entry","NXentry")));

  BOOST_CHECK(!match(Element("entry","NXentry"),
                     Element("entry","NXinstrument")));
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_rule_2)
{
  BOOST_CHECK(match(Element("entry","NXentry"),
                    Element("","NXentry")));
  BOOST_CHECK(match(Element("","NXentry"),
                    Element("entry","NXentry")));

  BOOST_CHECK(!match(Element("","NXinstrument"),
                     Element("control","NXmonitor")));
  BOOST_CHECK(!match(Element("detector","NXdetector"),
                     Element("","NXmonitor")));
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_rule_3)
{
  BOOST_CHECK(match(Element("entry",""),
                    Element("entry","")));
  BOOST_CHECK(match(Element("","NXentry"),
                    Element("","NXentry")));

  BOOST_CHECK(!match(Element("entry",""),
                     Element("scan","")));
  BOOST_CHECK(!match(Element("","NXentry"),
                     Element("","NXinstrument")));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

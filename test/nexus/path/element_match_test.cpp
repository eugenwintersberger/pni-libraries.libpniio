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

#include "../../boost_unit_test.hpp"
#include <pni/nexus/path.hpp>

using namespace pni;
using namespace pni::nexus;

BOOST_AUTO_TEST_SUITE(PathTest)
BOOST_AUTO_TEST_SUITE(ElementMatchTest)

using Element = Path::Element;

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_rule_complete_elements)
{
  BOOST_CHECK(match(Element("entry","NXentry"),
                    Element("entry","NXentry")));

  BOOST_CHECK(!match(Element("scan_1","NXentry"),
                     Element("entry","NXentry")));

  BOOST_CHECK(!match(Element("entry","NXentry"),
                     Element("entry","NXinstrument")));
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_rule_class_set_on_both)
{
  BOOST_CHECK(match(Element("entry","NXentry"),Element("","NXentry")));
  BOOST_CHECK(match(Element("","NXentry"),Element("entry","NXentry")));

  BOOST_CHECK(!match(Element("","NXinstrument"),Element("control","NXmonitor")));
  BOOST_CHECK(!match(Element("detector","NXdetector"),Element("","NXmonitor")));
}

BOOST_AUTO_TEST_CASE(test_rul_name_set_on_both)
{
  BOOST_CHECK(match(Element("entry","NXentry"),Element("entry","")));
  BOOST_CHECK(match(Element("instrument","NXinstrument"),Element("instrument","")));
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_rule_only_names_or_classes)
{
  BOOST_CHECK(match(Element("entry",""),Element("entry","")));
  BOOST_CHECK(match(Element("","NXentry"),Element("","NXentry")));

  BOOST_CHECK(!match(Element("entry",""),Element("scan","")));
  BOOST_CHECK(!match(Element("","NXentry"),Element("","NXinstrument")));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

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
#include <pni/core/types.hpp>
#include <pni/io/nx/nxpath.hpp>

using namespace pni::core;
using namespace pni::io::nx;
    
typedef nxpath::element_type element_type;

BOOST_AUTO_TEST_SUITE(test_element_match)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_rule_1)
    {
        BOOST_CHECK(match(element_type("entry","NXentry"),
                          element_type("entry","NXentry")));

        BOOST_CHECK(!match(element_type("scan_1","NXentry"),
                           element_type("entry","NXentry")));
        
        BOOST_CHECK(!match(element_type("entry","NXentry"),
                           element_type("entry","NXinstrument")));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_rule_2)
    {
        BOOST_CHECK(match(element_type("entry","NXentry"),
                          element_type("","NXentry")));
        BOOST_CHECK(match(element_type("","NXentry"),
                          element_type("entry","NXentry")));

        BOOST_CHECK(!match(element_type("","NXinstrument"),
                           element_type("control","NXmonitor")));
        BOOST_CHECK(!match(element_type("detector","NXdetector"),
                           element_type("","NXmonitor")));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_rule_3)
    {
        BOOST_CHECK(match(element_type("entry",""),
                          element_type("entry","")));
        BOOST_CHECK(match(element_type("","NXentry"),
                          element_type("","NXentry")));

        BOOST_CHECK(!match(element_type("entry",""),
                           element_type("scan","")));
        BOOST_CHECK(!match(element_type("","NXentry"),
                           element_type("","NXinstrument")));
    }

BOOST_AUTO_TEST_SUITE_END()

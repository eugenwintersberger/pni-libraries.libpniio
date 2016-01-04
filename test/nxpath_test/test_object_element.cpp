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
//  Created on: Feb 26, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nxpath.hpp>

using namespace pni::core;
using namespace pni::io::nx;


BOOST_AUTO_TEST_SUITE(test_object_element)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_full)
    {
        nxpath::element_type e = object_element("detector","NXdetector");
        BOOST_CHECK_EQUAL(e.first,"detector");
        BOOST_CHECK_EQUAL(e.second,"NXdetector");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_name_only)
    {
        nxpath::element_type e = object_element("detector","");
        BOOST_CHECK_EQUAL(e.first,"detector");
        BOOST_CHECK(e.second.empty());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_type_only)
    {
        nxpath::element_type e = object_element("","NXdetector");
        BOOST_CHECK(e.first.empty());
        BOOST_CHECK_EQUAL(e.second,"NXdetector");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_error)
    {
        BOOST_CHECK_THROW(object_element("",""),value_error);
    }

BOOST_AUTO_TEST_SUITE_END()

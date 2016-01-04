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

BOOST_AUTO_TEST_SUITE(test_is_complete)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_yes)
    {
        BOOST_CHECK(is_complete(object_element("/","NXroot")));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_no)
    {
        BOOST_CHECK(!is_complete(object_element("/","")));
        BOOST_CHECK(!is_complete(object_element("","NXroot")));
    }

    //------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_error)
    {
        BOOST_CHECK_THROW(is_complete(nxpath::element_type{"",""}),
                          value_error);
    }

BOOST_AUTO_TEST_SUITE_END()

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
//  Created on: Sep 11, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nxpath/nxpath.hpp>
#include <pni/io/nx/nxpath/make_relative.hpp>

using namespace pni::core;
using namespace pni::io::nx;

BOOST_AUTO_TEST_SUITE(test_make_relative)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_1)
    {
        string p1 = "/:NXentry";
        string p2 = "/:NXentry/instrument:NXinstrument";

        string p2r = nxpath::to_string(make_relative(p1,p2));
        BOOST_CHECK_EQUAL(p2r,"instrument:NXinstrument");
    }   

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_2)
    {
        string parent = "/:NXentry";
        string orig = "/";

        BOOST_CHECK_THROW(make_relative(parent,orig),value_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_3)
    {
        string parent = "/:NXentry";
        string orig   = "/:NXentry";

        BOOST_CHECK_EQUAL(nxpath::to_string(make_relative(parent,orig)),".");
    }

BOOST_AUTO_TEST_SUITE_END()

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
#include <pni/core/types.hpp>
#include <pni/io/nx/nxpath.hpp>

using namespace pni::core;
using namespace pni::io::nx;

struct test_split_path_fixture
{
    nxpath p,p1,p2;

    test_split_path_fixture():
        p(nxpath::from_string("test.nxs://:NXentry/:NXinstrument/detector@NX_class")),
        p1(),
        p2()
    {}
};


BOOST_FIXTURE_TEST_SUITE(test_split_path,test_split_path_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_standard)
    {
        BOOST_CHECK_NO_THROW(split_path(p,3,p1,p2)); 
        BOOST_CHECK_EQUAL(nxpath::to_string(p1),"test.nxs://:NXentry/:NXinstrument");
        BOOST_CHECK_EQUAL(nxpath::to_string(p2),"detector@NX_class");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_at_root)
    {
        BOOST_CHECK_NO_THROW(split_path(p,0,p1,p2)); 
        BOOST_CHECK_EQUAL(nxpath::to_string(p1),"test.nxs");
        BOOST_CHECK_EQUAL(nxpath::to_string(p2),"/:NXentry/:NXinstrument/detector@NX_class");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_index_error)
    {
        BOOST_CHECK_THROW(split_path(p,10,p1,p2),index_error); 
    }

BOOST_AUTO_TEST_SUITE_END()

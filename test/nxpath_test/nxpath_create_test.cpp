//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jun 11, 2014
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nxpath.hpp>

using namespace pni::core;
using namespace pni::io::nx;

BOOST_AUTO_TEST_SUITE(nxpath_create_test)

    BOOST_AUTO_TEST_CASE(test_abs_no_file)
    {
        nxpath p = nxpath::from_string("/");
        BOOST_CHECK_EQUAL(p.size(),1);
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.front().first,"/");
        BOOST_CHECK_EQUAL(p.front().second,"NXroot");

        p = nxpath::from_string("/./:NXentry/:NXinstrument/");
        BOOST_CHECK_EQUAL(p.size(),4);
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.front().first,"/");
        BOOST_CHECK_EQUAL(p.front().second,"NXroot");

        p = nxpath::from_string("/../:NXentry/:NXinstrument");
        BOOST_CHECK_EQUAL(p.size(),4);
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.front().first,"/");
        BOOST_CHECK_EQUAL(p.front().second,"NXroot");

        p = nxpath::from_string("/.");
        BOOST_CHECK_EQUAL(p.size() , 2);
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.front().first,"/");
        BOOST_CHECK_EQUAL(p.front().second,"NXroot");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_abs_no_file_with_attribute)
    {
        nxpath p = nxpath::from_string("/@date");
        BOOST_CHECK_EQUAL(p.size(),1);
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.front().first,"/");
        BOOST_CHECK_EQUAL(p.front().second,"NXroot");
        BOOST_CHECK_EQUAL(p.attribute(),"date");

        p = nxpath::from_string("/./:NXentry/:NXinstrument/@date");
        BOOST_CHECK_EQUAL(p.size(),4);
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.front().first,"/");
        BOOST_CHECK_EQUAL(p.front().second,"NXroot");
        BOOST_CHECK_EQUAL(p.attribute(),"date");

        p = nxpath::from_string("/../:NXentry/:NXinstrument@date");
        BOOST_CHECK_EQUAL(p.size(),4);
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.front().first,"/");
        BOOST_CHECK_EQUAL(p.front().second,"NXroot");
        BOOST_CHECK_EQUAL(p.attribute(),"date");

        p = nxpath::from_string("/.@date");
        p = nxpath::from_string("/.");
        BOOST_CHECK_EQUAL(p.size() , 2);
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.front().first,"/");
        BOOST_CHECK_EQUAL(p.front().second,"NXroot");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_abs_with_file)
    {
        nxpath p = nxpath::from_string("test.nxs://");
        BOOST_CHECK_EQUAL(p.size(),1);
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.filename() , "test.nxs");

        p = nxpath::from_string("/data/run/test.nxs://");
        BOOST_CHECK_EQUAL(p.size(),1);
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.filename() , "/data/run/test.nxs");
        
        p= nxpath::from_string("test.nxs://:NXentry/:NXinstrument/pilatus:NXdetector");
        BOOST_CHECK_EQUAL(p.size(),4);
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.filename() , "test.nxs");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_abs_with_file_with_attribute)
    {
        nxpath p = nxpath::from_string("test.nxs://@date");
        BOOST_CHECK_EQUAL(p.size(),1);
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.filename() , "test.nxs");
        BOOST_CHECK_EQUAL(p.attribute() , "date");

        p= nxpath::from_string("/data/run/test.nxs://.@date");
        BOOST_CHECK_EQUAL(p.size(),2);
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.filename() , "/data/run/test.nxs");
        BOOST_CHECK_EQUAL(p.attribute(),"date");
        
        p= nxpath::from_string("test.nxs://:NXentry/:NXinstrument/pilatus:NXdetector@date");
        BOOST_CHECK_EQUAL(p.size(),4);
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.filename() , "test.nxs");
        BOOST_CHECK_EQUAL(p.attribute() , "date");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_rel_no_attribute)
    {
        //get an attribute
        nxpath p = nxpath::from_string("scan_1/:NXinstrument/value");
        BOOST_CHECK(!is_absolute(p));
        BOOST_CHECK_EQUAL(p.size(),3);
       
        //get an attribute from the root group
        p = nxpath::from_string(".");
        BOOST_CHECK(!is_absolute(p));
        BOOST_CHECK_EQUAL(p.size(),1);

        //get an attribute from the current group
        p = nxpath::from_string("..");
        BOOST_CHECK(!is_absolute(p));
        BOOST_CHECK_EQUAL(p.size(),1);

        //get an attribute from the parent group
        p = nxpath::from_string("./:NXdetector");
        BOOST_CHECK(!is_absolute(p));
        BOOST_CHECK_EQUAL(p.size(),2);
    }

BOOST_AUTO_TEST_SUITE_END()

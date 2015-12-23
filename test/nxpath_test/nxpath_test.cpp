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

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nxpath.hpp>
#include <boost/test/unit_test.hpp>

using namespace pni::core;
using namespace pni::io::nx;


BOOST_AUTO_TEST_SUITE(nxpath_test)

    BOOST_AUTO_TEST_CASE(test_from_string_no_file)
    {
        //test for a relative path without attribute
        string str = "../:NXdata/data";
        nxpath p = nxpath::from_string(str);
        BOOST_CHECK(p.filename().empty());
        BOOST_CHECK(p.attribute().empty());
        BOOST_CHECK_EQUAL(p.size(),3);
        BOOST_CHECK(!is_absolute(p));
        BOOST_CHECK_EQUAL(nxpath::to_string(p),str);

        //test for an absolute path without attribute
        str = "/scan_1/:NXinstrument/:NXdetector/";
        p = nxpath::from_string(str);
        BOOST_CHECK(p.filename().empty() && p.attribute().empty());
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.size(),4);
        BOOST_CHECK_EQUAL(nxpath::to_string(p),string(str,0,str.size()-1));

        //test for an absolute path without attribute
        str = "/scan_1/:NXinstrument/:NXdetector";
        p = nxpath::from_string(str);
        BOOST_CHECK(p.filename().empty() && p.attribute().empty());
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.size(),4);
        BOOST_CHECK_EQUAL(nxpath::to_string(p),str);

        str = "/";
        p = nxpath::from_string(str);
        BOOST_CHECK(p.filename().empty() && p.attribute().empty());
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.size(),1);
        BOOST_CHECK_EQUAL(nxpath::to_string(p),str);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_from_string_no_file_attr)
    {
        //get an attribute
        string str = "/scan_1/:NXinstrument/value@test";
        nxpath p = nxpath::from_string(str);
        BOOST_CHECK(p.filename().empty());
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.size(),4);
        BOOST_CHECK_EQUAL(p.attribute(),"test");
        BOOST_CHECK_EQUAL(nxpath::to_string(p),str);
       
        //get an attribute from the root group
        str = "/@date";
        p = nxpath::from_string(str);
        BOOST_CHECK(p.filename().empty());
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.size(),1);
        BOOST_CHECK_EQUAL(p.attribute(),"date");
        BOOST_CHECK_EQUAL(nxpath::to_string(p),str);

        //get an attribute from the current group
        str = ".@date";
        p = nxpath::from_string(str);
        BOOST_CHECK(p.filename().empty());
        BOOST_CHECK(!is_absolute(p));
        BOOST_CHECK_EQUAL(p.size(),1);
        BOOST_CHECK_EQUAL(p.attribute(),"date");
        BOOST_CHECK_EQUAL(nxpath::to_string(p),str);

        //get an attribute from the parent group
        str = "..@date";
        p = nxpath::from_string(str);
        BOOST_CHECK(p.filename().empty());
        BOOST_CHECK(!is_absolute(p));
        BOOST_CHECK_EQUAL(p.size(),1);
        BOOST_CHECK_EQUAL(p.attribute(),"date");
        BOOST_CHECK_EQUAL(nxpath::to_string(p),str);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_from_string_with_file_attr)
    {
        //get an attribute
        string str = "data/test/test.nx://scan_1/:NXinstrument/value@test";
        nxpath p = nxpath::from_string(str);
        BOOST_CHECK_EQUAL(p.filename(),"data/test/test.nx");
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.size(),4);
        BOOST_CHECK_EQUAL(p.attribute(),"test");
        BOOST_CHECK_EQUAL(nxpath::to_string(p),str);
       
        //get an attribute from the root group
        str = "test.nx://@date";
        p = nxpath::from_string(str);
        BOOST_CHECK_EQUAL(p.filename(),"test.nx");
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.size(),1);
        BOOST_CHECK_EQUAL(p.attribute(),"date");
        BOOST_CHECK_EQUAL(nxpath::to_string(p),str);

        //get an attribute from the current group
        str = "test.nx://:NXentry/:NXinstrument/.@date";
        p = nxpath::from_string(str);
        BOOST_CHECK_EQUAL(p.filename(),"test.nx");
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.size(),4);
        BOOST_CHECK_EQUAL(p.attribute(),"date");
        BOOST_CHECK_EQUAL(nxpath::to_string(p),str);

        //get an attribute from the parent group
        str = "test.nx://scan_1:NXentry/..@date";
        p = nxpath::from_string(str);
        BOOST_CHECK_EQUAL(p.filename(),"test.nx");
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.size(),3);
        BOOST_CHECK_EQUAL(p.attribute(),"date");
        BOOST_CHECK_EQUAL(nxpath::to_string(p),str);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_from_string_with_file)
    {
        //test for an absolute path without attribute
        string str = "test.nx://";
        nxpath p = nxpath::from_string(str);
        BOOST_CHECK_EQUAL(p.filename(),"test.nx");
        BOOST_CHECK(p.attribute().empty());
        BOOST_CHECK_EQUAL(p.size(),1);
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(p.front().first,"/");
        BOOST_CHECK_EQUAL(p.front().second,"NXroot");
        BOOST_CHECK_EQUAL(nxpath::to_string(p),str);

        //test for an absolute path without attribute
        str = "test.nx://../:NXdata/data";
        p = nxpath::from_string(str);
        BOOST_CHECK_EQUAL(p.filename(),"test.nx");
        BOOST_CHECK_EQUAL(p.size(),4);
        BOOST_CHECK(is_absolute(p));
        BOOST_CHECK_EQUAL(nxpath::to_string(p),str);

    }

BOOST_AUTO_TEST_SUITE_END()


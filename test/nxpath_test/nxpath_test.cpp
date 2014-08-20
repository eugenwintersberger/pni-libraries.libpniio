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

#include "nxpath_test.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(nxpath_test);


//----------------------------------------------------------------------------
void nxpath_test::setUp() { }

//----------------------------------------------------------------------------
void nxpath_test::tearDown() {}

//----------------------------------------------------------------------------
void nxpath_test::test_from_string_no_file()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    //test for a relative path without attribute
    string str = "../:NXdata/data";
    nxpath p = nxpath::from_string(str);
    CPPUNIT_ASSERT(p.filename().empty());
    CPPUNIT_ASSERT(p.attribute().empty());
    CPPUNIT_ASSERT(p.size()==3);
    CPPUNIT_ASSERT(!is_absolute(p));
    CPPUNIT_ASSERT(nxpath::to_string(p) == str);

    //test for an absolute path without attribute
    str = "/scan_1/:NXinstrument/:NXdetector/";
    p = nxpath::from_string(str);
    CPPUNIT_ASSERT(p.filename().empty() && p.attribute().empty());
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.size()==4);
    CPPUNIT_ASSERT(nxpath::to_string(p) == string(str,0,str.size()-1));

    //test for an absolute path without attribute
    str = "/scan_1/:NXinstrument/:NXdetector";
    p = nxpath::from_string(str);
    CPPUNIT_ASSERT(p.filename().empty() && p.attribute().empty());
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.size()==4);
    CPPUNIT_ASSERT(nxpath::to_string(p)==str);


    str = "/";
    p = nxpath::from_string(str);
    CPPUNIT_ASSERT(p.filename().empty() && p.attribute().empty());
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.size()==1);
    CPPUNIT_ASSERT(nxpath::to_string(p) == str);
}

//----------------------------------------------------------------------------
void nxpath_test::test_from_string_no_file_attr()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    //get an attribute
    string str = "/scan_1/:NXinstrument/value@test";
    nxpath p = nxpath::from_string(str);
    CPPUNIT_ASSERT(p.filename().empty());
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.size()==4);
    CPPUNIT_ASSERT(p.attribute() == "test");
    CPPUNIT_ASSERT(nxpath::to_string(p) == str);
   
    //get an attribute from the root group
    str = "/@date";
    p = nxpath::from_string(str);
    CPPUNIT_ASSERT(p.filename().empty());
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.size()==1);
    CPPUNIT_ASSERT(p.attribute() == "date");
    CPPUNIT_ASSERT(nxpath::to_string(p) == str);

    //get an attribute from the current group
    str = ".@date";
    p = nxpath::from_string(str);
    CPPUNIT_ASSERT(p.filename().empty());
    CPPUNIT_ASSERT(!is_absolute(p));
    CPPUNIT_ASSERT(p.size()==1);
    CPPUNIT_ASSERT(p.attribute() == "date");
    CPPUNIT_ASSERT(nxpath::to_string(p)==str);

    //get an attribute from the parent group
    str = "..@date";
    p = nxpath::from_string(str);
    CPPUNIT_ASSERT(p.filename().empty());
    CPPUNIT_ASSERT(!is_absolute(p));
    CPPUNIT_ASSERT(p.size()==1);
    CPPUNIT_ASSERT(p.attribute() == "date");
    CPPUNIT_ASSERT(nxpath::to_string(p)==str);
}

//----------------------------------------------------------------------------
void nxpath_test::test_from_string_with_file_attr()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    //get an attribute
    string str = "data/test/test.nx://scan_1/:NXinstrument/value@test";
    nxpath p = nxpath::from_string(str);
    CPPUNIT_ASSERT(p.filename() == "data/test/test.nx");
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.size()==4);
    CPPUNIT_ASSERT(p.attribute() == "test");
    CPPUNIT_ASSERT(nxpath::to_string(p)==str);
   
    //get an attribute from the root group
    str = "test.nx://@date";
    p = nxpath::from_string(str);
    CPPUNIT_ASSERT(p.filename() == "test.nx");
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.size()==1);
    CPPUNIT_ASSERT(p.attribute() == "date");
    CPPUNIT_ASSERT(nxpath::to_string(p)==str);

    //get an attribute from the current group
    str = "test.nx://:NXentry/:NXinstrument/.@date";
    p = nxpath::from_string(str);
    CPPUNIT_ASSERT(p.filename() == "test.nx");
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.size()==4);
    CPPUNIT_ASSERT(p.attribute() == "date");
    CPPUNIT_ASSERT(nxpath::to_string(p)==str);

    //get an attribute from the parent group
    str = "test.nx://scan_1:NXentry/..@date";
    p = nxpath::from_string(str);
    CPPUNIT_ASSERT(p.filename() == "test.nx");
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.size()==3);
    CPPUNIT_ASSERT(p.attribute() == "date");
    CPPUNIT_ASSERT(nxpath::to_string(p)==str);
}
//----------------------------------------------------------------------------
void nxpath_test::test_from_string_with_file()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    //test for an absolute path without attribute
    string str = "test.nx://";
    nxpath p = nxpath::from_string(str);
    CPPUNIT_ASSERT(p.filename() == "test.nx");
    CPPUNIT_ASSERT(p.attribute().empty());
    CPPUNIT_ASSERT(p.size() == 1);
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.front().first == "/");
    CPPUNIT_ASSERT(p.front().second == "NXroot");
    CPPUNIT_ASSERT(nxpath::to_string(p) == str);

    //test for an absolute path without attribute
    str = "test.nx://../:NXdata/data";
    p = nxpath::from_string(str);
    CPPUNIT_ASSERT(p.filename() == "test.nx");
    CPPUNIT_ASSERT(p.size() == 4);
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(nxpath::to_string(p) == str);

}



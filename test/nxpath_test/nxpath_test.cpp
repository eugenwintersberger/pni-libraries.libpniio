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
    nxpath p = nxpath::from_string("../:NXdata/data");
    CPPUNIT_ASSERT(p.filename().empty());
    CPPUNIT_ASSERT(p.attribute().empty());
    CPPUNIT_ASSERT(p.size()==3);
    CPPUNIT_ASSERT(!p.is_absolute());

    //test for an absolute path without attribute
    p = nxpath::from_string("/scan_1/:NXinstrument/:NXdetector/");
    CPPUNIT_ASSERT(p.filename().empty() && p.attribute().empty());
    CPPUNIT_ASSERT(p.is_absolute());
    CPPUNIT_ASSERT(p.size()==4);

    //test for an absolute path without attribute
    p = nxpath::from_string("/scan_1/:NXinstrument/:NXdetector");
    CPPUNIT_ASSERT(p.filename().empty() && p.attribute().empty());
    CPPUNIT_ASSERT(p.is_absolute());
    CPPUNIT_ASSERT(p.size()==4);


    p = nxpath::from_string("/");
    CPPUNIT_ASSERT(p.filename().empty() && p.attribute().empty());
    CPPUNIT_ASSERT(p.is_absolute());
    CPPUNIT_ASSERT(p.size()==1);



}

//----------------------------------------------------------------------------
void nxpath_test::test_from_string_no_file_attr()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    //get an attribute
    nxpath p = nxpath::from_string("/scan_1/:NXinstrument/value@test");
    CPPUNIT_ASSERT(p.filename().empty());
    CPPUNIT_ASSERT(p.is_absolute());
    CPPUNIT_ASSERT(p.size()==4);
    CPPUNIT_ASSERT(p.attribute() == "test");
   
    //get an attribute from the root group
    p = nxpath::from_string("/@date");
    CPPUNIT_ASSERT(p.filename().empty());
    CPPUNIT_ASSERT(p.is_absolute());
    CPPUNIT_ASSERT(p.size()==1);
    CPPUNIT_ASSERT(p.attribute() == "date");

    //get an attribute from the current group
    p = nxpath::from_string(".@date");
    CPPUNIT_ASSERT(p.filename().empty());
    CPPUNIT_ASSERT(!p.is_absolute());
    CPPUNIT_ASSERT(p.size()==1);
    CPPUNIT_ASSERT(p.attribute() == "date");

    //get an attribute from the parent group
    p = nxpath::from_string("..@date");
    CPPUNIT_ASSERT(p.filename().empty());
    CPPUNIT_ASSERT(!p.is_absolute());
    CPPUNIT_ASSERT(p.size()==1);
    CPPUNIT_ASSERT(p.attribute() == "date");
}

//----------------------------------------------------------------------------
void nxpath_test::test_from_string_with_file_attr()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    //get an attribute
    nxpath p = nxpath::from_string("data/test/test.nx://scan_1/:NXinstrument/value@test");
    CPPUNIT_ASSERT(p.filename() == "data/test/test.nx");
    CPPUNIT_ASSERT(p.is_absolute());
    CPPUNIT_ASSERT(p.size()==4);
    CPPUNIT_ASSERT(p.attribute() == "test");
   
    //get an attribute from the root group
    p = nxpath::from_string("test.nx://@date");
    CPPUNIT_ASSERT(p.filename() == "test.nx");
    CPPUNIT_ASSERT(p.is_absolute());
    CPPUNIT_ASSERT(p.size()==1);
    CPPUNIT_ASSERT(p.attribute() == "date");

    //get an attribute from the current group
    p = nxpath::from_string("test.nx://:NXentry/:NXinstrument/.@date");
    CPPUNIT_ASSERT(p.filename() == "test.nx");
    CPPUNIT_ASSERT(p.is_absolute());
    CPPUNIT_ASSERT(p.size()==4);
    CPPUNIT_ASSERT(p.attribute() == "date");

    //get an attribute from the parent group
    p = nxpath::from_string("test.nx://scan_1:NXentry/..@date");
    CPPUNIT_ASSERT(p.filename() == "test.nx");
    CPPUNIT_ASSERT(p.is_absolute());
    CPPUNIT_ASSERT(p.size()==3);
    CPPUNIT_ASSERT(p.attribute() == "date");
}
//----------------------------------------------------------------------------
void nxpath_test::test_from_string_with_file()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    //test for an absolute path without attribute
    nxpath p = nxpath::from_string("test.nx://");
    CPPUNIT_ASSERT(p.filename() == "test.nx");
    CPPUNIT_ASSERT(p.attribute().empty());
    CPPUNIT_ASSERT(p.size() == 1);
    CPPUNIT_ASSERT(p.is_absolute());
    CPPUNIT_ASSERT(p.front().first == "/");
    CPPUNIT_ASSERT(p.front().second == "NXroot");

    //test for an absolute path without attribute
    p = nxpath::from_string("test.nx://../:NXdata/data");
    CPPUNIT_ASSERT(p.filename() == "test.nx");
    CPPUNIT_ASSERT(p.size() == 4);
    CPPUNIT_ASSERT(p.is_absolute());

}



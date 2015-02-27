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

#include "nxpath_create_test.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(nxpath_create_test);


//----------------------------------------------------------------------------
void nxpath_create_test::setUp() { }

//----------------------------------------------------------------------------
void nxpath_create_test::tearDown() {}

//----------------------------------------------------------------------------
void nxpath_create_test::test_abs_no_file()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxpath p = nxpath::from_string("/");
    CPPUNIT_ASSERT(p.size()==1);
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.front().first=="/");
    CPPUNIT_ASSERT(p.front().second=="NXroot");

    p = nxpath::from_string("/./:NXentry/:NXinstrument/");
    CPPUNIT_ASSERT(p.size()==4);
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.front().first=="/");
    CPPUNIT_ASSERT(p.front().second=="NXroot");

    p = nxpath::from_string("/../:NXentry/:NXinstrument");
    CPPUNIT_ASSERT(p.size()==4);
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.front().first=="/");
    CPPUNIT_ASSERT(p.front().second=="NXroot");

    p = nxpath::from_string("/.");
    CPPUNIT_ASSERT(p.size() == 2);
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.front().first=="/");
    CPPUNIT_ASSERT(p.front().second=="NXroot");

}

//----------------------------------------------------------------------------
void nxpath_create_test::test_abs_no_file_with_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxpath p = nxpath::from_string("/@date");
    CPPUNIT_ASSERT(p.size()==1);
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.front().first=="/");
    CPPUNIT_ASSERT(p.front().second=="NXroot");
    CPPUNIT_ASSERT(p.attribute()=="date");

    p = nxpath::from_string("/./:NXentry/:NXinstrument/@date");
    CPPUNIT_ASSERT(p.size()==4);
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.front().first=="/");
    CPPUNIT_ASSERT(p.front().second=="NXroot");
    CPPUNIT_ASSERT(p.attribute()=="date");

    p = nxpath::from_string("/../:NXentry/:NXinstrument@date");
    CPPUNIT_ASSERT(p.size()==4);
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.front().first=="/");
    CPPUNIT_ASSERT(p.front().second=="NXroot");
    CPPUNIT_ASSERT(p.attribute()=="date");

    p = nxpath::from_string("/.@date");
    p = nxpath::from_string("/.");
    CPPUNIT_ASSERT(p.size() == 2);
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.front().first=="/");
    CPPUNIT_ASSERT(p.front().second=="NXroot");

}

//----------------------------------------------------------------------------
void nxpath_create_test::test_abs_with_file()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxpath p = nxpath::from_string("test.nxs://");
    CPPUNIT_ASSERT(p.size()==1);
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.filename() == "test.nxs");

    p = nxpath::from_string("/data/run/test.nxs://");
    CPPUNIT_ASSERT(p.size()==1);
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.filename() == "/data/run/test.nxs");
    
    p= nxpath::from_string("test.nxs://:NXentry/:NXinstrument/pilatus:NXdetector");
    CPPUNIT_ASSERT(p.size()==4);
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.filename() == "test.nxs");
}

//----------------------------------------------------------------------------
void nxpath_create_test::test_abs_with_file_with_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxpath p = nxpath::from_string("test.nxs://@date");
    CPPUNIT_ASSERT(p.size()==1);
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.filename() == "test.nxs");
    CPPUNIT_ASSERT(p.attribute() == "date");

    p= nxpath::from_string("/data/run/test.nxs://.@date");
    CPPUNIT_ASSERT(p.size()==2);
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.filename() == "/data/run/test.nxs");
    CPPUNIT_ASSERT(p.attribute()=="date");
    
    p= nxpath::from_string("test.nxs://:NXentry/:NXinstrument/pilatus:NXdetector@date");
    CPPUNIT_ASSERT(p.size()==4);
    CPPUNIT_ASSERT(is_absolute(p));
    CPPUNIT_ASSERT(p.filename() == "test.nxs");
    CPPUNIT_ASSERT(p.attribute() == "date");

}

//----------------------------------------------------------------------------
void nxpath_create_test::test_rel_no_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    //get an attribute
    nxpath p = nxpath::from_string("scan_1/:NXinstrument/value");
    CPPUNIT_ASSERT(!is_absolute(p));
    CPPUNIT_ASSERT(p.size()==3);
   
    //get an attribute from the root group
    p = nxpath::from_string(".");
    CPPUNIT_ASSERT(!is_absolute(p));
    CPPUNIT_ASSERT(p.size()==1);

    //get an attribute from the current group
    p = nxpath::from_string("..");
    CPPUNIT_ASSERT(!is_absolute(p));
    CPPUNIT_ASSERT(p.size()==1);

    //get an attribute from the parent group
    p = nxpath::from_string("./:NXdetector");
    CPPUNIT_ASSERT(!is_absolute(p));
    CPPUNIT_ASSERT(p.size()==2);
}

//----------------------------------------------------------------------------
void nxpath_create_test::test_rel_with_attribute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
}

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
//  Created on: Mar 11, 2015
//      Author: Eugen Wintersberger
//

#include "test_join.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(test_join);


//----------------------------------------------------------------------------
void test_join::setUp() { }

//----------------------------------------------------------------------------
void test_join::tearDown() {}

//----------------------------------------------------------------------------
void test_join::test_both_empty()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(is_empty(join(nxpath(),nxpath())));
}

//----------------------------------------------------------------------------
void test_join::test_a_empty()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    string b_str = "/entry:NXentry/:NXinstrument";
    nxpath j;

    CPPUNIT_ASSERT_NO_THROW(j = join(nxpath(),nxpath::from_string(b_str)));
    CPPUNIT_ASSERT(nxpath::to_string(j)==b_str);
}

//----------------------------------------------------------------------------
void test_join::test_b_empty()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    string a_str = "filename.nxs://scan_1/:NXinstrument";
    nxpath j;
    CPPUNIT_ASSERT_NO_THROW(j = join(nxpath::from_string(a_str),nxpath()));
    CPPUNIT_ASSERT(nxpath::to_string(j)==a_str);
}

//----------------------------------------------------------------------------
void test_join::test_a_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxpath b = nxpath::from_string(":NXinstrument/:NXdetector");
    nxpath a = nxpath::from_string("data@units");
    CPPUNIT_ASSERT_THROW(join(a,b),value_error);
}

//----------------------------------------------------------------------------
void test_join::test_b_absolute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxpath a = nxpath::from_string("filename.nxs://:NXentry");
    nxpath b = nxpath::from_string("/entry/instrument");
    CPPUNIT_ASSERT_THROW(join(a,b),value_error);
}

//----------------------------------------------------------------------------
void test_join::test_b_filename()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    nxpath a = nxpath::from_string("filename.nxs://:NXentry");
    nxpath b = nxpath::from_string("filename.nxs://entry/instrument");
    CPPUNIT_ASSERT_THROW(join(a,b),value_error);
}

//----------------------------------------------------------------------------
void test_join::test_join_simple()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    nxpath a = nxpath::from_string("filename.nxs://:NXentry");
    nxpath b = nxpath::from_string("instrument/:NXdetector");
    nxpath j;
    string expect = "filename.nxs://:NXentry/instrument/:NXdetector";
    CPPUNIT_ASSERT_NO_THROW(j = join(a,b));
    CPPUNIT_ASSERT(nxpath::to_string(j)==expect);

}

//----------------------------------------------------------------------------
void test_join::test_join_with_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    nxpath a = nxpath::from_string("filename.nxs://:NXentry");
    nxpath b = nxpath::from_string("instrument/:NXdetector/data@units");
    nxpath j;
    string expect = "filename.nxs://:NXentry/instrument/:NXdetector/data@units";
    CPPUNIT_ASSERT_NO_THROW(j = join(a,b));
    CPPUNIT_ASSERT(nxpath::to_string(j)==expect);

}

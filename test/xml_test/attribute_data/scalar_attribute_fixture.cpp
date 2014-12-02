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
//  Created on: Dec 2, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <vector>
#include "scalar_attribute_fixture.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(scalar_attribute_fixture);

//-----------------------------------------------------------------------------
void scalar_attribute_fixture::setUp() 
{ }

//-----------------------------------------------------------------------------
void scalar_attribute_fixture::tearDown() { }

//----------------------------------------------------------------------------
xml::node scalar_attribute_fixture::get_first(const string &s)
{
    return xml::create_from_string(s).front().second;
}

//----------------------------------------------------------------------------
void scalar_attribute_fixture::test_uint8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef xml::attribute_data<uint8> attr_data;
    
    xml::node n = get_first("<test number=\"1\" />");
    CPPUNIT_ASSERT(attr_data::read(n,"number")==1);
    
    n = get_first("<test number=\"  2    \" />");
    CPPUNIT_ASSERT(attr_data::read(n,"number")==2);

    //this should overflow
    n = get_first("<test number=\"500\"/>");
    CPPUNIT_ASSERT_THROW(attr_data::read(n,"number"),pni::core::range_error);

    //this should underlfow
    n = get_first("<test number=\"-10\"/>");
    CPPUNIT_ASSERT_THROW(attr_data::read(n,"number"),pni::core::range_error);
}

//----------------------------------------------------------------------------
void scalar_attribute_fixture::test_int8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef xml::attribute_data<int8> attr_data;
    
    xml::node n = get_first("<test number=\"1\" />");
    CPPUNIT_ASSERT(attr_data::read(n,"number")==1);

    //this should overflow
    n = get_first("<test number=\"500\"/>");
    CPPUNIT_ASSERT_THROW(attr_data::read(n,"number"),pni::core::range_error);

    //this should work
    n = get_first("<test number=\"-1\"/>");
    CPPUNIT_ASSERT(attr_data::read(n,"number")==-1);
}

//----------------------------------------------------------------------------
void scalar_attribute_fixture::test_float32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef xml::attribute_data<float32> attr_data;

    xml::node n = get_first("<test number=\"1.23e+4\"/>");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(attr_data::read(n,"number"),1.23e+4,1.e-8);

    //this would be an overflow
    n = get_first("<test number=\"1.23e+40\"/>");
    CPPUNIT_ASSERT_THROW(attr_data::read(n,"number"),pni::core::range_error);

    //this would given an underflow
    n = get_first("<test number=\"-1.23e+40\"/>");
    CPPUNIT_ASSERT_THROW(attr_data::read(n,"number"),pni::core::range_error);

    //need to do something when the resolution of a particular type 
    //does not match

}


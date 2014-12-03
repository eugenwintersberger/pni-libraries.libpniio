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
//  Created on: Dec 3, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <vector>
#include "array_attribute_fixture.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(array_attribute_fixture);

//-----------------------------------------------------------------------------
void array_attribute_fixture::setUp() 
{ }

//-----------------------------------------------------------------------------
void array_attribute_fixture::tearDown() { }

//----------------------------------------------------------------------------
xml::node array_attribute_fixture::get_first(const string &s) const
{
    return xml::create_from_string(s).front().second;
}
//-----------------------------------------------------------------------------
void array_attribute_fixture::test_read_array_float()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    float64_vector ref{1.,2.,3.,3.,4.};
    xml::node n = get_first("<group vector=\"1. 2. 3.  3. 4.\"/>");

    //-------------------------------------------------------------------------
    array a;
    CPPUNIT_ASSERT_NO_THROW(a = attr_data::read(n,"vector",' '));
    CPPUNIT_ASSERT(a.type_id() == type_id_t::FLOAT64);
    CPPUNIT_ASSERT(a.size() == 5);
    auto viter = ref.begin();

    for(auto v: a)
        CPPUNIT_ASSERT_DOUBLES_EQUAL(v.as<float64>(),*(viter++),1.e-8);

}

//-----------------------------------------------------------------------------
void array_attribute_fixture::test_read_array_int_blank()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    int32_vector ref{1,2,3,4,5,6,10};
    xml::node n = get_first("<test vector=\" 1  2 3 4 5 6 10\"/>");

    array v;
    CPPUNIT_ASSERT_NO_THROW(v = attr_data::read(n,"vector",' '));
    CPPUNIT_ASSERT(v.type_id() == type_id_t::INT32);
    CPPUNIT_ASSERT(v.size() == 7);

    auto diter = ref.begin();
    for(auto a: v) CPPUNIT_ASSERT(*(diter++) == a.as<int32>());
}

//-----------------------------------------------------------------------------
void array_attribute_fixture::test_read_array_int_comma()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    int32_vector ref{1,2,3,4,5,6,10};
    xml::node n = get_first("<test vector=\" 1 , 2 ,3  ,4 ,5, 6, 10 \"/>");
    
    array v;
    CPPUNIT_ASSERT_NO_THROW(v = attr_data::read(n,"vector",','));
    CPPUNIT_ASSERT(v.type_id() == type_id_t::INT32);
    CPPUNIT_ASSERT(v.size() == 7);

    auto diter = ref.begin();
    for(auto a: v) CPPUNIT_ASSERT(*(diter++) == a.as<int32>());
}

//-----------------------------------------------------------------------------
void array_attribute_fixture::test_read_array_int_semicolon()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    int32_vector ref{1,2,3,4,5,6,10};
    xml::node n = get_first("<test vector=\" 1 ; 2 ;3  ;4 ;5; 6; 10 \"/>");

    array v;
    CPPUNIT_ASSERT_NO_THROW(v = attr_data::read(n,"vector",';'));
    CPPUNIT_ASSERT(v.type_id() == type_id_t::INT32);
    CPPUNIT_ASSERT(v.size() == 7);

    auto diter = ref.begin();
    for(auto a: v) CPPUNIT_ASSERT(*(diter++) == a.as<int32>());
}

//-----------------------------------------------------------------------------
void array_attribute_fixture::test_read_array_int_fail()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    xml::node n = get_first("<test vector=\"a stupid text \"/>");

    array v;
    CPPUNIT_ASSERT_THROW(v = attr_data::read(n,"vector",' '),
            pni::io::parser_error);
}

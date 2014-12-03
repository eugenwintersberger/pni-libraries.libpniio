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
//      Author: Eugen Wintersberger
//

#include <vector>
#include "node_array_data_fixture.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(node_array_data_fixture);

//-----------------------------------------------------------------------------
void node_array_data_fixture::setUp() 
{ 
    int_vec = std::vector<int32>{1,2,3,4,5,6,10};
}

//-----------------------------------------------------------------------------
void node_array_data_fixture::tearDown() { }

//-----------------------------------------------------------------------------
void node_array_data_fixture::test_read_array_float()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_string("<group1>1. 2. 3.  3. 4.</group1>");
    child = root.get_child("group1");
    std::vector<float64> int_vec{1.,2.,3.,3.,4.};

    //-------------------------------------------------------------------------
    array a;
    CPPUNIT_ASSERT_NO_THROW(a = xml::node_data<array>::read(child,' '));
    CPPUNIT_ASSERT(a.type_id() == type_id_t::FLOAT64);
    CPPUNIT_ASSERT(a.size() == 5);
    auto viter = int_vec.begin();

    for(auto v: a)
        CPPUNIT_ASSERT_DOUBLES_EQUAL(v.as<float64>(),*(viter++),1.e-8);

}

//-----------------------------------------------------------------------------
void node_array_data_fixture::test_read_array_int_blank()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_string("<test> 1  2 3 4 5 6 10</test>");
    child = root.get_child("test");

    array v;
    CPPUNIT_ASSERT_NO_THROW(v = xml::node_data<array>::read(child,' '));
    CPPUNIT_ASSERT(v.type_id() == type_id_t::INT32);
    CPPUNIT_ASSERT(v.size() == 7);

    auto diter = int_vec.begin();
    for(auto a: v)
        CPPUNIT_ASSERT(*(diter++) == a.as<int32>());
}

//-----------------------------------------------------------------------------
void node_array_data_fixture::test_read_array_int_comma()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_string("<test> 1 , 2 ,3  ,4 ,5, 6, 10 </test>");
    child = root.get_child("test");

    array v;
    CPPUNIT_ASSERT_NO_THROW(v = xml::node_data<array>::read(child,','));
    CPPUNIT_ASSERT(v.type_id() == type_id_t::INT32);
    CPPUNIT_ASSERT(v.size() == 7);

    auto diter = int_vec.begin();
    for(auto a: v)
        CPPUNIT_ASSERT(*(diter++) == a.as<int32>());
}

//-----------------------------------------------------------------------------
void node_array_data_fixture::test_read_array_int_semicolon()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_string("<test> 1 ; 2 ;3  ;4 ;5; 6; 10</test>");
    child = root.get_child("test");

    array v;
    CPPUNIT_ASSERT_NO_THROW(v = xml::node_data<array>::read(child,';'));
    CPPUNIT_ASSERT(v.type_id() == type_id_t::INT32);
    CPPUNIT_ASSERT(v.size() == 7);

    auto diter = int_vec.begin();
    for(auto a: v)
        CPPUNIT_ASSERT(*(diter++) == a.as<int32>());
}

//-----------------------------------------------------------------------------
void node_array_data_fixture::test_read_array_int_fail()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_string("<test> a stupid text </test>");
    child = root.get_child("test");

    array v;
    CPPUNIT_ASSERT_THROW(v = xml::node_data<array>::read(child,' '),
            pni::io::parser_error);
}

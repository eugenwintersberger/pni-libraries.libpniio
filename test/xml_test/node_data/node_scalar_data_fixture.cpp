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
#include "node_scalar_data_fixture.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(node_scalar_data_fixture);

//-----------------------------------------------------------------------------
void node_scalar_data_fixture::setUp() { }

//-----------------------------------------------------------------------------
void node_scalar_data_fixture::tearDown() { }


//-----------------------------------------------------------------------------
void node_scalar_data_fixture::test_read_int()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef xml::node_data<int16> ndata;

    root = xml::create_from_string("<group1>12</group1>"
                                   "<group2>-12</group2>"
                                   "<group3>bla</group3>"
                                   "<group4>12.3</group4>"
                                   "<group5>100000</group5>"
                                   "<group6>-1000000</group6>");
                
    child = root.get_child("group1");

    //----------------------this should work-----------------------------------
    int32 value = 0;
    CPPUNIT_ASSERT_NO_THROW(value = ndata::read(child));
    CPPUNIT_ASSERT(value == 12);

    //------------------------this should work too ----------------------------
    child = root.get_child("group2");
    CPPUNIT_ASSERT_NO_THROW(value = ndata::read(child));
    CPPUNIT_ASSERT(value == -12);

    //-----------should not work as you cannot convert a string to an int------
    child = root.get_child("group3");
    CPPUNIT_ASSERT_THROW(ndata::read(child),pni::io::parser_error);
   
    //-----------should not work as you cannot convert a float to an int ------
    child = root.get_child("group4");
    CPPUNIT_ASSERT_THROW(ndata::read(child),pni::io::parser_error);

    //--------------this should overfowl-----------------------------------
    child = root.get_child("group5");
    CPPUNIT_ASSERT_THROW(ndata::read(child),pni::core::range_error);
    
    //--------------this should overfowl-----------------------------------
    child = root.get_child("group6");
    CPPUNIT_ASSERT_THROW(ndata::read(child),pni::core::range_error);
}

//------------------------------------------------------------------------------
void node_scalar_data_fixture::test_read_uint()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef xml::node_data<uint16> ndata;

    root = xml::create_from_string("<group1>12</group1>"
                                   "<group2>-12</group2>"
                                   "<group3>bla</group3>"
                                   "<group4>12.3</group4>"
                                   "<group5>100000</group5>");
    child = root.get_child("group1");

    //----------------------this should work-----------------------------------
    uint32 value;
    CPPUNIT_ASSERT_NO_THROW(value = ndata::read(child));
    CPPUNIT_ASSERT(value == 12);

    //------------------------this should not work too ----------------------------
    // see issue 26 for this porblem
    child = root.get_child("group2");
    CPPUNIT_ASSERT_THROW(value = ndata::read(child),pni::core::range_error);

    //-----------should not work as you cannot convert a string to an int------
    child = root.get_child("group3");
    CPPUNIT_ASSERT_THROW(ndata::read(child),pni::io::parser_error);
   
    //-----------should not work as you cannot convert a float to an int ------
    child = root.get_child("group4");
    CPPUNIT_ASSERT_THROW(ndata::read(child),pni::io::parser_error);

    //--------------this should overflow-------------------------------------
    child = root.get_child("group5");
    CPPUNIT_ASSERT_THROW(ndata::read(child),pni::io::range_error);

}

//-----------------------------------------------------------------------------
void node_scalar_data_fixture::test_read_float()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef xml::node_data<float32> ndata;

    root = xml::create_from_string("<group1>12.234</group1>"
                                   "<group2>-1.234e-13</group2>"
                                   "<group3>bla</group3>"
                                   "<group4>12</group4>"
                                   "<group5>1.e+40</group5>"
                                   "<group6>-1.e+40</group6>");
    child = root.get_child("group1");

    //----------------------this should work-----------------------------------
    float64 value;
    CPPUNIT_ASSERT_NO_THROW(value = ndata::read(child));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(value,12.234,1.e-6);

    //------------------------this should work too ----------------------------
    child = root.get_child("group2");
    CPPUNIT_ASSERT_NO_THROW(value = ndata::read(child));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(value,-1.234e-13,1.e-8);

    //-----------should not work as you cannot convert a string to an int------
    child = root.get_child("group3");
    CPPUNIT_ASSERT_THROW(value = ndata::read(child),pni::io::parser_error);
   
    //-----------should not work as you cannot convert a float to an int ------
    child = root.get_child("group4");
    CPPUNIT_ASSERT_NO_THROW(value = ndata::read(child));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(value,12,1.e-8);

    //the next two should overflow
    CPPUNIT_ASSERT_THROW(ndata::read(root.get_child("group5")),
                         pni::core::range_error);
    CPPUNIT_ASSERT_THROW(ndata::read(root.get_child("group6")),
                         pni::core::range_error);
}


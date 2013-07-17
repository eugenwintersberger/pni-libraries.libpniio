/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jul 11, 2013
 *      Author: Eugen Wintersberger
 */

#include <vector>
#include "xml_node_data_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(xml_node_data_test);

//-----------------------------------------------------------------------------
void xml_node_data_test::setUp() 
{ 
    int_vec = std::vector<int32>{1,2,3,4,5,6,10};
}

//-----------------------------------------------------------------------------
void xml_node_data_test::tearDown() { }

//-----------------------------------------------------------------------------
void xml_node_data_test::test_has_data()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_string("<group>hello world</group>");
    child = root.get_child("group");

    CPPUNIT_ASSERT(xml::has_data(child));

    root = xml::create_from_string("<group />");
    child = root.get_child("group");

    CPPUNIT_ASSERT(!xml::has_data(child));
    
}

//-----------------------------------------------------------------------------
void xml_node_data_test::test_read_data_int()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_string("<group1>12</group1>"
                                   "<group2>-12</group2>"
                                   "<group3>bla</group3>"
                                   "<group4>12.3</group4>");
    child = root.get_child("group1");

    //----------------------this should work-----------------------------------
    int32 value;
    CPPUNIT_ASSERT_NO_THROW(value = xml::node_data<int32>::read(child));
    CPPUNIT_ASSERT(value == 12);

    //------------------------this should work too ----------------------------
    child = root.get_child("group2");
    CPPUNIT_ASSERT_NO_THROW(value = xml::node_data<int32>::read(child));
    CPPUNIT_ASSERT(value == -12);

    //-----------should not work as you cannot convert a string to an int------
    child = root.get_child("group3");
    CPPUNIT_ASSERT_THROW(xml::node_data<int32>::read(child),pni::io::parser_error);
   
    //-----------should not work as you cannot convert a float to an int ------
    child = root.get_child("group4");
    CPPUNIT_ASSERT_THROW(xml::node_data<int32>::read(child),pni::io::parser_error);
}

//------------------------------------------------------------------------------
void xml_node_data_test::test_read_data_uint()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_string("<group1>12</group1>"
                                   "<group2>-12</group2>"
                                   "<group3>bla</group3>"
                                   "<group4>12.3</group4>");
    child = root.get_child("group1");

    //----------------------this should work-----------------------------------
    uint32 value;
    CPPUNIT_ASSERT_NO_THROW(value = xml::node_data<uint32>::read(child));
    CPPUNIT_ASSERT(value == 12);

    //------------------------this should not work too ----------------------------
    // see issue 26 for this porblem
    child = root.get_child("group2");
    value = xml::node_data<uint32>::read(child);
    std::cout<<value<<std::endl;

    //-----------should not work as you cannot convert a string to an int------
    child = root.get_child("group3");
    CPPUNIT_ASSERT_THROW(xml::node_data<uint32>::read(child),pni::io::parser_error);
   
    //-----------should not work as you cannot convert a float to an int ------
    child = root.get_child("group4");
    CPPUNIT_ASSERT_THROW(xml::node_data<uint32>::read(child),pni::io::parser_error);

}

//-----------------------------------------------------------------------------
void xml_node_data_test::test_read_data_float()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_string("<group1>12.234</group1>"
                                   "<group2>-1.234e-13</group2>"
                                   "<group3>bla</group3>"
                                   "<group4>12</group4>");
    child = root.get_child("group1");

    //----------------------this should work-----------------------------------
    float64 value;
    CPPUNIT_ASSERT_NO_THROW(value = xml::node_data<float64>::read(child));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(value,12.234,1.e-8);

    //------------------------this should work too ----------------------------
    child = root.get_child("group2");
    CPPUNIT_ASSERT_NO_THROW(value = xml::node_data<float64>::read(child));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(value,-1.234e-13,1.e-8);

    //-----------should not work as you cannot convert a string to an int------
    child = root.get_child("group3");
    CPPUNIT_ASSERT_THROW(value = xml::node_data<float64>::read(child),
            pni::io::parser_error);
   
    //-----------should not work as you cannot convert a float to an int ------
    child = root.get_child("group4");
    CPPUNIT_ASSERT_NO_THROW(value = xml::node_data<float64>::read(child));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(value,12,1.e-8);
}

//-----------------------------------------------------------------------------
void xml_node_data_test::test_read_array_float()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_string("<group1>1. 2. 3.  3. 4.</group1>");
    child = root.get_child("group1");
    std::vector<float64> int_vec{1.,2.,3.,3.,4.};

    //-------------------------------------------------------------------------
    array a;
    CPPUNIT_ASSERT_NO_THROW(a = xml::node_data<array>::read(child,' '));
    CPPUNIT_ASSERT(a.type_id() == type_id_t::FLOAT64);
    CPPUNIT_ASSERT(a.size() == 5);
    auto aiter = a.begin();
    auto viter = int_vec.begin();

    while(aiter!=a.end())
        CPPUNIT_ASSERT_DOUBLES_EQUAL((aiter++)->as<float64>(),*(viter++),1.e-8);

}

//-----------------------------------------------------------------------------
void xml_node_data_test::test_read_array_int_blank()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_string("<test> 1  2 3 4 5 6 10</test>");
    child = root.get_child("test");

    array v;
    CPPUNIT_ASSERT_NO_THROW(v = xml::node_data<array>::read(child,' '));
    CPPUNIT_ASSERT(v.type_id() == type_id_t::INT32);
    CPPUNIT_ASSERT(v.size() == 7);

    auto diter = int_vec.begin();
    auto aiter = v.begin();
    while(aiter!=v.end())
        CPPUNIT_ASSERT(*(diter++) == (aiter++)->as<int32>());
}

//-----------------------------------------------------------------------------
void xml_node_data_test::test_read_array_int_comma()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_string("<test> 1 , 2 ,3  ,4 ,5, 6, 10 </test>");
    child = root.get_child("test");

    array v;
    CPPUNIT_ASSERT_NO_THROW(v = xml::node_data<array>::read(child,','));
    CPPUNIT_ASSERT(v.type_id() == type_id_t::INT32);
    CPPUNIT_ASSERT(v.size() == 7);

    auto diter = int_vec.begin();
    auto aiter = v.begin();
    while(aiter!=v.end())
        CPPUNIT_ASSERT(*(diter++) == (aiter++)->as<int32>());
}

//-----------------------------------------------------------------------------
void xml_node_data_test::test_read_array_int_semicolon()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_string("<test> 1 ; 2 ;3  ;4 ;5; 6; 10</test>");
    child = root.get_child("test");

    array v;
    CPPUNIT_ASSERT_NO_THROW(v = xml::node_data<array>::read(child,';'));
    CPPUNIT_ASSERT(v.type_id() == type_id_t::INT32);
    CPPUNIT_ASSERT(v.size() == 7);

    auto diter = int_vec.begin();
    auto aiter = v.begin();
    while(aiter!=v.end())
        CPPUNIT_ASSERT(*(diter++) == (aiter++)->as<int32>());
}

//-----------------------------------------------------------------------------
void xml_node_data_test::test_read_array_int_fail()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_string("<test> a stupid text </test>");
    child = root.get_child("test");

    array v;
    CPPUNIT_ASSERT_THROW(v = xml::node_data<array>::read(child,' '),
            pni::io::parser_error);
}

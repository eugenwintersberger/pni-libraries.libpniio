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
#include "xml_lowlevel_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(xml_lowlevel_test);

//-----------------------------------------------------------------------------
void xml_lowlevel_test::setUp() 
{ 
    int_vec = std::vector<int32>{1,2,3,4,5,6,10};
}

//-----------------------------------------------------------------------------
void xml_lowlevel_test::tearDown() { } 

//-----------------------------------------------------------------------------
void xml_lowlevel_test::test_read_xml_attribute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    xml::node n = xml::create_from_string("<test attr=\"value\"/>");
   
    string v;
    CPPUNIT_ASSERT_NO_THROW(v = xml::read_xml_attribute<string>(n.get_child("test"),"attr"));

    //wont work because not convertible types
    CPPUNIT_ASSERT_THROW(xml::read_xml_attribute<double>(n.get_child("test"),"attr"),
                         pni::io::parser_error);

    //attribute does not exist
    CPPUNIT_ASSERT_THROW(xml::read_xml_attribute<string>(n.get_child("test"),"bla"),
                         pni::io::parser_error);
}

//-----------------------------------------------------------------------------
void xml_lowlevel_test::test_read_xml_data_str()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    xml::node n = xml::create_from_string("<test> hello world </test>");

    string v;
    CPPUNIT_ASSERT_NO_THROW(v = xml::read_xml_data<string>(n.get_child("test")));
    std::cout<<v<<std::endl;
    CPPUNIT_ASSERT(v == " hello world ");
}

//-----------------------------------------------------------------------------
void xml_lowlevel_test::test_read_xml_array_int_blank()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    xml::node root = xml::create_from_string("<test> 1  2 3 4 5 6 10</test>");
    xml::node test = root.get_child("test");

    array v;
    CPPUNIT_ASSERT_NO_THROW(v = xml::node_data<array>::read(test,' '));
    CPPUNIT_ASSERT(v.type_id() == type_id_t::INT32);
    CPPUNIT_ASSERT(v.size() == 7);

    auto diter = int_vec.begin();
    auto aiter = v.begin();
    while(aiter!=v.end())
        CPPUNIT_ASSERT(*(diter++) == (aiter++)->as<int32>());
}

//-----------------------------------------------------------------------------
void xml_lowlevel_test::test_read_xml_array_int_comma()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    xml::node root = xml::create_from_string("<test> 1 , 2 ,3  ,4 ,5, 6, 10 </test>");
    xml::node test = root.get_child("test");

    array v;
    CPPUNIT_ASSERT_NO_THROW(v = xml::node_data<array>::read(test,','));
    CPPUNIT_ASSERT(v.type_id() == type_id_t::INT32);
    CPPUNIT_ASSERT(v.size() == 7);

    auto diter = int_vec.begin();
    auto aiter = v.begin();
    while(aiter!=v.end())
        CPPUNIT_ASSERT(*(diter++) == (aiter++)->as<int32>());
}

//-----------------------------------------------------------------------------
void xml_lowlevel_test::test_read_xml_array_int_semicolon()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    xml::node root = xml::create_from_string("<test> 1 ; 2 ;3  ;4 ;5; 6; 10</test>");
    xml::node test = root.get_child("test");

    array v;
    CPPUNIT_ASSERT_NO_THROW(v = xml::node_data<array>::read(test,';'));
    CPPUNIT_ASSERT(v.type_id() == type_id_t::INT32);
    CPPUNIT_ASSERT(v.size() == 7);

    auto diter = int_vec.begin();
    auto aiter = v.begin();
    while(aiter!=v.end())
        CPPUNIT_ASSERT(*(diter++) == (aiter++)->as<int32>());
}
//-----------------------------------------------------------------------------
void xml_lowlevel_test::test_read_xml_array_int_fail()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    xml::node root = xml::create_from_string("<test> a stupid text </test>");
    xml::node test = root.get_child("test");

    array v;
    CPPUNIT_ASSERT_THROW(v = xml::node_data<array>::read(test,' '),
            pni::io::parser_error);
}

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
#include "xml_attribute_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(xml_attribute_test);

//-----------------------------------------------------------------------------
void xml_attribute_test::setUp() 
{
}

//-----------------------------------------------------------------------------
void xml_attribute_test::tearDown() 
{ 
}

//-----------------------------------------------------------------------------
void xml_attribute_test::test_has_attribute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    root = xml::create_from_string("<group name=\"test\"/>");
    child = root.get_child("group");

    CPPUNIT_ASSERT(xml::has_attribute(child,"name"));
    CPPUNIT_ASSERT(!xml::has_attribute(child,"bla"));
}

//-----------------------------------------------------------------------------
void xml_attribute_test::test_has_data()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_string("<group name=\"hello world\"/>");
    child = root.get_child("group");

    CPPUNIT_ASSERT(xml::has_attribute(child,"name"));
    CPPUNIT_ASSERT(xml::has_data(child,"name"));

    //code can throw an exception 
    CPPUNIT_ASSERT_THROW(xml::has_data(child,"bla"),pni::io::parser_error);

    root = xml::create_from_string("<group name=\"\"/>");
    child = root.get_child("group");

    CPPUNIT_ASSERT(!xml::has_data(child,"name"));
    
    root = xml::create_from_string("<group/>");
    child = root.get_child("group");

    CPPUNIT_ASSERT_THROW(xml::has_data(child,"name"),pni::io::parser_error);
}

//-----------------------------------------------------------------------------
void xml_attribute_test::test_read_data_int()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_string("<group1 value=\"12\"/>"
                                   "<group2 value=\"-12\"/>"
                                   "<group3 value=\"bla\"/>"
                                   "<group4 value=\"12.3\"/>");
    child = root.get_child("group1");

    //----------------------this should work-----------------------------------
    int32 value;
    CPPUNIT_ASSERT_NO_THROW(value = xml::attribute_data<int32>::read(child,"value"));
    CPPUNIT_ASSERT(value == 12);

    //------------------------this should work too ----------------------------
    child = root.get_child("group2");
    CPPUNIT_ASSERT_NO_THROW(value = xml::attribute_data<int32>::read(child,"value"));
    CPPUNIT_ASSERT(value == -12);

    //-----------should not work as you cannot convert a string to an int------
    child = root.get_child("group3");
    CPPUNIT_ASSERT_THROW(value = xml::attribute_data<int32>::read(child,"value"),
            pni::io::parser_error);
   
    //-----------should not work as you cannot convert a float to an int ------
    child = root.get_child("group4");
    CPPUNIT_ASSERT_THROW(value = xml::attribute_data<int32>::read(child,"value"),
            pni::io::parser_error);
    
}

//------------------------------------------------------------------------------
void xml_attribute_test::test_read_data_uint()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

}

//-----------------------------------------------------------------------------
void xml_attribute_test::test_read_data_float()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

}


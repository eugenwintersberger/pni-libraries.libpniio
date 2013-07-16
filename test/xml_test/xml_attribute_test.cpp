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
}

//-----------------------------------------------------------------------------
void xml_attribute_test::test_read_xml_attribute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
}


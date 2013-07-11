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

#include "xml_lowlevel_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(xml_lowlevel_test);

//-----------------------------------------------------------------------------
void xml_lowlevel_test::setUp() { }

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



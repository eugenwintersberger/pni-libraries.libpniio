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

#include "xml_node_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(xml_node_test);

//-----------------------------------------------------------------------------
void xml_node_test::setUp() { }

//-----------------------------------------------------------------------------
void xml_node_test::tearDown() { } 

//-----------------------------------------------------------------------------
void xml_node_test::test_node_from_file()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    xml::node n = xml::create_from_file("xml_test/node_from_str.xml");
    CPPUNIT_ASSERT(!n.empty());
    CPPUNIT_ASSERT(n.size() == 1);

    
}

//-----------------------------------------------------------------------------
void xml_node_test::test_node_from_string()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    xml::node n = xml::create_from_string(node_from_string_str);

    CPPUNIT_ASSERT(!n.empty());
    CPPUNIT_ASSERT(n.size() == 1);
}


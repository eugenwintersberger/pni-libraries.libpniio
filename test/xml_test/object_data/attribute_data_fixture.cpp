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
//  Created on: Dec 4, 2014
//      Author: Eugen Wintersberger
//

#include "attribute_data_fixture.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(attribute_data_fixture);

//-----------------------------------------------------------------------------
void attribute_data_fixture::setUp() 
{ 
    root = xml::create_from_file("attribute.xml");
}

//-----------------------------------------------------------------------------
void attribute_data_fixture::tearDown() { } 

//-----------------------------------------------------------------------------
void attribute_data_fixture::test_read_existing()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    string data = attr.read(root.get_child("group1"));
    CPPUNIT_ASSERT(data == "hello world");
}

//-----------------------------------------------------------------------------
void attribute_data_fixture::test_read_non_existing()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT_THROW(attr.read(root.get_child("group2")),
                         pni::core::key_error);
}

//----------------------------------------------------------------------------
void attribute_data_fixture::test_write_existing()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    group = root.get_child("group3"); 
    CPPUNIT_ASSERT(attr.read(group) == "a text");

    CPPUNIT_ASSERT_NO_THROW(attr.write("another text",group));
    CPPUNIT_ASSERT(attr.read(group) == "another text");
}

//----------------------------------------------------------------------------
void attribute_data_fixture::test_write_non_existing()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    group = root.get_child("group4");
    CPPUNIT_ASSERT(!xml::has_attribute(group,"test"));

    CPPUNIT_ASSERT_NO_THROW(attr.write("a new text",group));
    CPPUNIT_ASSERT(xml::has_attribute(group,"test"));
    CPPUNIT_ASSERT(attr.read(group) == "a new text");
}


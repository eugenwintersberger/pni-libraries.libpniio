//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Apr 15, 2015
//      Author: Eugen Wintersberger
//

#include <vector>
#include "attribute_node_io_fixture.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(attribute_node_io_fixture);

//-----------------------------------------------------------------------------
void attribute_node_io_fixture::setUp() 
{
    using namespace pni::io::nx::xml;
    
    root = xml::create_from_string("<group attr1=\"12\" attr2=\" -12    \""
                                   "attr3=\"bla    \""
                                   "attr4=\"   12.3\""
                                   "attr5=\" 100000 \""
                                   "attr6=\"-1000000\"></group>");

    root_array = xml::create_from_string("<group attr1=\"12 23 34.2  34 23\""
                                         "attr2=\"       12 23 34.2  34 23 \">"
                                         "</group>");
}

//-----------------------------------------------------------------------------
void attribute_node_io_fixture::tearDown() { }

//-----------------------------------------------------------------------------
void attribute_node_io_fixture::test_read_scalar()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    using namespace pni::io::nx::xml;
    
    root = root.get_child("group");
    node attr;
    CPPUNIT_ASSERT_NO_THROW(attr = xml::get_attribute(root,"attr1"));
    CPPUNIT_ASSERT(data_node::read(attr)=="12");

    CPPUNIT_ASSERT_NO_THROW(attr = xml::get_attribute(root,"attr2"));
    CPPUNIT_ASSERT(data_node::read(attr)=="-12");

    CPPUNIT_ASSERT_NO_THROW(attr = xml::get_attribute(root,"attr3"));
    CPPUNIT_ASSERT(data_node::read(attr)=="bla");

    CPPUNIT_ASSERT_NO_THROW(attr = xml::get_attribute(root,"attr4"));
    CPPUNIT_ASSERT(data_node::read(attr)=="12.3");

    CPPUNIT_ASSERT_NO_THROW(attr = xml::get_attribute(root,"attr5"));
    CPPUNIT_ASSERT(data_node::read(attr)=="100000");

    CPPUNIT_ASSERT_NO_THROW(attr = xml::get_attribute(root,"attr6"));
    CPPUNIT_ASSERT(data_node::read(attr)=="-1000000");
}

//-----------------------------------------------------------------------------
void attribute_node_io_fixture::test_read_array()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    using namespace pni::io::nx::xml;
    
    root_array = root_array.get_child("group");
    node attr;
    CPPUNIT_ASSERT_NO_THROW(attr = xml::get_attribute(root_array,"attr1"));
    CPPUNIT_ASSERT(data_node::read(attr)=="12 23 34.2  34 23");

    CPPUNIT_ASSERT_NO_THROW(attr = xml::get_attribute(root_array,"attr2"));
    CPPUNIT_ASSERT(data_node::read(attr)=="12 23 34.2  34 23");
}

//-----------------------------------------------------------------------------
void attribute_node_io_fixture::test_write_scalar()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    using namespace pni::io::nx::xml;
    
    data_node::write(child,"1234");
    CPPUNIT_ASSERT(data_node::read(child)=="1234");
}

//-----------------------------------------------------------------------------
void attribute_node_io_fixture::test_write_array()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    using namespace pni::io::nx::xml;

    data_node::write(child," 1 2    4 5 5  ");
    CPPUNIT_ASSERT(data_node::read(child)=="1 2    4 5 5");
}


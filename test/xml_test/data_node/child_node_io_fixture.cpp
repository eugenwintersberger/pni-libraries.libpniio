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

#include <boost/current_function.hpp>
#include "child_node_io_fixture.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(child_node_io_fixture);

//-----------------------------------------------------------------------------
void child_node_io_fixture::setUp() 
{
    using namespace pni::io::nx;
    root = xml::create_from_string("<group1>12</group1>"
                                   "<group2> -12    </group2>"
                                   "<group3>bla    </group3>"
                                   "<group4>   12.3</group4>"
                                   "<group5> 100000 </group5>"
                                   "<group6>-1000000</group6>");
    
    root_array = xml::create_from_string(
            "<group1> 12 23 34.2  34 23 </group1>"
            "<group2> "
            "       12 23 34.2  34 23  "
            "</group2>");
}

//-----------------------------------------------------------------------------
void child_node_io_fixture::tearDown() { }


//-----------------------------------------------------------------------------
void child_node_io_fixture::test_read_scalar()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    using namespace pni::io::nx::xml;
    
    CPPUNIT_ASSERT(data_node::read(root.get_child("group1"))=="12");
    CPPUNIT_ASSERT(data_node::read(root.get_child("group2"))=="-12");
    CPPUNIT_ASSERT(data_node::read(root.get_child("group3"))=="bla");
    CPPUNIT_ASSERT(data_node::read(root.get_child("group4"))=="12.3");
    CPPUNIT_ASSERT(data_node::read(root.get_child("group5"))=="100000");
    CPPUNIT_ASSERT(data_node::read(root.get_child("group6"))=="-1000000");
}

//------------------------------------------------------------------------------
void child_node_io_fixture::test_read_array()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    using namespace pni::io::nx::xml;

    CPPUNIT_ASSERT(data_node::read(root_array.get_child("group1"))== 
                   "12 23 34.2  34 23");

    CPPUNIT_ASSERT(data_node::read(root_array.get_child("group2"))== 
                   "12 23 34.2  34 23");
}

//----------------------------------------------------------------------------
void child_node_io_fixture::test_write_scalar()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    using namespace pni::io::nx::xml;

    data_node::write(child,"1234");
    CPPUNIT_ASSERT(data_node::read(child)=="1234");

}

//----------------------------------------------------------------------------
void child_node_io_fixture::test_write_array()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    using namespace pni::io::nx::xml;

    data_node::write(child," 1 2    4 5 5  ");
    CPPUNIT_ASSERT(data_node::read(child)=="1 2    4 5 5");

}

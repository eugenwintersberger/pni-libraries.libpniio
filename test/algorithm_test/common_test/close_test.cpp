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
//  Created on: Jun 03, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nx/algorithms/is_valid.hpp>
#include <boost/current_function.hpp>
#include <cppunit/extensions/HelperMacros.h>

#include "close_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(close_test);

//-----------------------------------------------------------------------------
void close_test::setUp()
{
    file = h5::nxfile::create_file("close_test.nx",true);
    root = file.root();
    group = root.create_group("group","NXentry");
    field = root.create_field<uint32>("data");
    attribute = group.attributes["NX_class"];
}

//-----------------------------------------------------------------------------
void close_test::tearDown() 
{ 
    attribute.close();
    field.close();
    group.close();
    root.close();
    file.close();
}

void close_test::test_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(is_valid(group));
    close(group);
    CPPUNIT_ASSERT(!is_valid(group));
}

//-----------------------------------------------------------------------------
void close_test::test_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(is_valid(field));
    close(field);
    CPPUNIT_ASSERT(!is_valid(field));
}

//----------------------------------------------------------------------------
void close_test::test_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(is_valid(attribute));
    close(attribute);
    CPPUNIT_ASSERT(!is_valid(attribute));
}

//-----------------------------------------------------------------------------
void close_test::test_visitor_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxobject object = group;
    CPPUNIT_ASSERT(is_valid(object));
    close(object);
    CPPUNIT_ASSERT(!is_valid(object));
}

//-----------------------------------------------------------------------------
void close_test::test_visitor_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject object = field;
    CPPUNIT_ASSERT(is_valid(object));
    close(object);
    CPPUNIT_ASSERT(!is_valid(object)); 
}

//-----------------------------------------------------------------------------
void close_test::test_visitor_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject object = attribute;
    CPPUNIT_ASSERT(is_valid(object));
    close(object);
    CPPUNIT_ASSERT(!is_valid(object));
   
}


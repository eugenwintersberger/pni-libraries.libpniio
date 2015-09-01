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

#include <boost/current_function.hpp>
#include "inquery_fixture.hpp"

using namespace pni::io::nx;

CPPUNIT_TEST_SUITE_REGISTRATION(inquery_fixture);

//-----------------------------------------------------------------------------
void inquery_fixture::setUp() 
{ 

    group = xml::create_from_file("inquery.xml").get_child("group");
}

//-----------------------------------------------------------------------------
void inquery_fixture::tearDown() { } 

//-----------------------------------------------------------------------------
void inquery_fixture::test_get_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT_NO_THROW(xml::get_attribute(group,"name"));

    //not a well formed XML file
    CPPUNIT_ASSERT_THROW(xml::get_attribute(group,"type"), pni::core::key_error);
}

//-----------------------------------------------------------------------------
void inquery_fixture::test_has_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(xml::has_attribute(group,"name"));
    CPPUNIT_ASSERT(!xml::has_attribute(group,"type"));
}


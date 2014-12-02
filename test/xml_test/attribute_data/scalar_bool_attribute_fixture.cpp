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
//  Created on: Dec 2, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <vector>
#include "scalar_bool_attribute_fixture.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(scalar_bool_attribute_fixture);

//-----------------------------------------------------------------------------
void scalar_bool_attribute_fixture::setUp() 
{ }

//-----------------------------------------------------------------------------
void scalar_bool_attribute_fixture::tearDown() { }

//----------------------------------------------------------------------------
xml::node scalar_bool_attribute_fixture::get_first(const string &s)
{
    return xml::create_from_string(s).front().second;
}

//----------------------------------------------------------------------------
void scalar_bool_attribute_fixture::test_bool()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef xml::attribute_data<bool> attr_data;
    
    xml::node n = get_first("<test number=\"True\" />");
    CPPUNIT_ASSERT(attr_data::read(n,"number"));

    n = get_first("<test number=\"true\" />");
    CPPUNIT_ASSERT(attr_data::read(n,"number"));
    
    n = get_first("<test number=\"1\" />");
    CPPUNIT_ASSERT(attr_data::read(n,"number"));
    
    n = get_first("<test number=\"x\" />");
    CPPUNIT_ASSERT_THROW(attr_data::read(n,"number"),pni::core::value_error);
}

//----------------------------------------------------------------------------
void scalar_bool_attribute_fixture::test_bool_t()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef xml::attribute_data<bool_t> attr_data;
    
    xml::node n = get_first("<test number=\"True\" />");
    CPPUNIT_ASSERT(attr_data::read(n,"number"));

    n = get_first("<test number=\"true\" />");
    CPPUNIT_ASSERT(attr_data::read(n,"number"));
    
    n = get_first("<test number=\"1\" />");
    CPPUNIT_ASSERT(attr_data::read(n,"number"));
    
    n = get_first("<test number=\"x\" />");
    CPPUNIT_ASSERT_THROW(attr_data::read(n,"number"),pni::core::value_error);
}



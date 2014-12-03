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
//  Created on: Dec 3, 2014
//      Author: Eugen Wintersberger
//

#include <vector>
#include "node_inquery_data_fixture.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(node_inquery_data_fixture);

//-----------------------------------------------------------------------------
void node_inquery_data_fixture::setUp() 
{ 
}

//-----------------------------------------------------------------------------
void node_inquery_data_fixture::tearDown() { }

//-----------------------------------------------------------------------------
void node_inquery_data_fixture::test_has_data()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_string("<group>hello world</group>");
    child = root.get_child("group");

    CPPUNIT_ASSERT(xml::has_data(child));

    root = xml::create_from_string("<group />");
    child = root.get_child("group");

    CPPUNIT_ASSERT(!xml::has_data(child));
}


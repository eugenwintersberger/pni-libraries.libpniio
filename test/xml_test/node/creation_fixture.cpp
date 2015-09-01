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

#include <pni/io/nx/xml/node.hpp>
#include <pni/io/exceptions.hpp>
#include <boost/current_function.hpp>
#include "creation_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

CPPUNIT_TEST_SUITE_REGISTRATION(creation_fixture);

//-----------------------------------------------------------------------------
void creation_fixture::setUp() { }

//-----------------------------------------------------------------------------
void creation_fixture::tearDown() { } 

//-----------------------------------------------------------------------------
void creation_fixture::test_from_file()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    xml::node n = xml::create_from_file("node_from_str.xml");
    CPPUNIT_ASSERT(!n.empty());
    CPPUNIT_ASSERT(n.size() == 1);

    //has to fail because file does not exist
    CPPUNIT_ASSERT_THROW(xml::create_from_file("bla.xml"),
                         file_error);

    //not a well formed XML file
    CPPUNIT_ASSERT_THROW(xml::create_from_file("node_from_bad_file.xml"),
            pni::io::parser_error);

    
}

//-----------------------------------------------------------------------------
void creation_fixture::test_from_string()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    xml::node n = xml::create_from_string(node_from_string_str);

    CPPUNIT_ASSERT(!n.empty());
    CPPUNIT_ASSERT(n.size() == 1);

    CPPUNIT_ASSERT_THROW(xml::create_from_string(node_from_bad_str),
            pni::io::parser_error);
}


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
//      Author: Eugen Wintersberger
//

#include <boost/current_function.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "write_fixture.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(write_fixture);

void write_fixture::setUp()
{}

//----------------------------------------------------------------------------
void write_fixture::tearDown()
{}

//----------------------------------------------------------------------------
void write_fixture::test_write_1()
{
    using namespace boost::property_tree;
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    shape_t s{55,100};

    xml::node root;
    root.add_child("dimensions",xml::dimensions::object_to_xml(s));

    write_xml("test.xml",root);

    CPPUNIT_ASSERT(!std::system("xmldiff -c test.xml dim1.xml"));
}

//----------------------------------------------------------------------------
void write_fixture::test_write_2()
{
    using namespace boost::property_tree;
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    shape_t s;

    xml::node root;
    root.add_child("dimensions",xml::dimensions::object_to_xml(s));

    write_xml("test.xml",root);

    CPPUNIT_ASSERT(!std::system("xmldiff -c test.xml dim6.xml"));
}

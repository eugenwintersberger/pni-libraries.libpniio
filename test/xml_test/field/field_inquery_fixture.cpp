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

#include <boost/property_tree/xml_parser.hpp>
#include <pni/io/nx/xml/attribute_data.hpp>
#include "inquery_fixture.hpp"
#include "../../uniform_distribution.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(inquery_fixture);

void inquery_fixture::setUp() { }

//-----------------------------------------------------------------------------
void inquery_fixture::tearDown() { }

//-----------------------------------------------------------------------------
void inquery_fixture::setup_xml(const string &fname)
{
    root = xml::create_from_file(fname);
    child = root.get_child("field");
}

//-----------------------------------------------------------------------------
void inquery_fixture::test_long_name()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    setup_xml("field1.xml");
    CPPUNIT_ASSERT(xml::field::long_name(child)=="motor along x-axis");
    setup_xml("field5.xml");
    CPPUNIT_ASSERT(xml::field::long_name(child)=="motor along x-axis");

    setup_xml("field3.xml");
    CPPUNIT_ASSERT_THROW(xml::field::long_name(child),pni::io::parser_error);
}

//-----------------------------------------------------------------------------
void inquery_fixture::test_unit()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    setup_xml("field1.xml");
    CPPUNIT_ASSERT(xml::field::unit(child)=="m");
    setup_xml("field3.xml");
    CPPUNIT_ASSERT_THROW(xml::field::unit(child),pni::io::parser_error);
}



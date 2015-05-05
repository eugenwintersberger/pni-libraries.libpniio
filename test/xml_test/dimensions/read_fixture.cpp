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
#include "read_fixture.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(read_fixture);

void read_fixture::setUp()
{}

//----------------------------------------------------------------------------
void read_fixture::tearDown()
{}

//----------------------------------------------------------------------------
void read_fixture::setup_xml(const string &fname)
{
    root = xml::create_from_file(fname);
    child = root.get_child("dimensions");
}


//-----------------------------------------------------------------------------
void read_fixture::test_read_1()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    setup_xml("dim1.xml");

    auto shape = xml::dimensions::object_from_xml<shape_t>(child);
    CPPUNIT_ASSERT(shape.size()==2);
    CPPUNIT_ASSERT(shape.front() == 55);
    CPPUNIT_ASSERT(shape.back()  == 100);
}

//-----------------------------------------------------------------------------
void read_fixture::test_read_2()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    setup_xml("dim2.xml");

    CPPUNIT_ASSERT_THROW(xml::dimensions::object_from_xml<shape_t>(child),
                         shape_mismatch_error);
}

//-----------------------------------------------------------------------------
void read_fixture::test_read_3()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    setup_xml("dim3.xml");

    CPPUNIT_ASSERT_THROW(xml::dimensions::object_from_xml<shape_t>(child),
                         pni::io::key_error);
}

//-----------------------------------------------------------------------------
void read_fixture::test_read_4()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    setup_xml("dim4.xml");

    CPPUNIT_ASSERT_THROW(xml::dimensions::object_from_xml<shape_t>(child),
                         pni::io::key_error);
}

//-----------------------------------------------------------------------------
void read_fixture::test_read_5()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    setup_xml("dim5.xml");
    child = root.get_child("dimensions");

    CPPUNIT_ASSERT_THROW(xml::dimensions::object_from_xml<shape_t>(child),
                         pni::io::key_error);
}

//----------------------------------------------------------------------------
void read_fixture::test_read_6()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    setup_xml("dim6.xml");
    auto s = xml::dimensions::object_from_xml<shape_t>(child);
    CPPUNIT_ASSERT(s.size() == 0);
}


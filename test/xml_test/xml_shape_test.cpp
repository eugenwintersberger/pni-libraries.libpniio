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
//  Created on: Nov 25, 2014
//      Author: Eugen Wintersberger
//

#include "xml_shape_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(xml_shape_test);

void xml_shape_test::setUp()
{}

//----------------------------------------------------------------------------
void xml_shape_test::tearDown()
{}

//-----------------------------------------------------------------------------
void xml_shape_test::test_read_1()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    root = xml::create_from_file("dim1.xml");
    child = root.get_child("dimensions");

    auto shape = xml::shape::from_xml<shape_t>(child);
    CPPUNIT_ASSERT(shape.size()==2);
    CPPUNIT_ASSERT(shape[0] == 55);
    CPPUNIT_ASSERT(shape[1] == 100);
}

//-----------------------------------------------------------------------------
void xml_shape_test::test_read_2()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    root = xml::create_from_file("dim2.xml");
    child = root.get_child("dimensions");

    CPPUNIT_ASSERT_THROW(xml::shape::from_xml<shape_t>(child),
                         shape_mismatch_error);
}

//-----------------------------------------------------------------------------
void xml_shape_test::test_read_3()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    root = xml::create_from_file("dim3.xml");
    child = root.get_child("dimensions");

    CPPUNIT_ASSERT_THROW(xml::shape::from_xml<shape_t>(child),
                         pni::io::parser_error);
}

//-----------------------------------------------------------------------------
void xml_shape_test::test_read_4()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    root = xml::create_from_file("dim4.xml");
    child = root.get_child("dimensions");

    CPPUNIT_ASSERT_THROW(xml::shape::from_xml<shape_t>(child),
                         pni::io::parser_error);
}

//-----------------------------------------------------------------------------
void xml_shape_test::test_read_5()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    root = xml::create_from_file("dim5.xml");
    child = root.get_child("dimensions");

    CPPUNIT_ASSERT_THROW(xml::shape::from_xml<shape_t>(child),
                         pni::io::parser_error);
}

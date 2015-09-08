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

#include <boost/current_function.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "inquery_fixture.hpp"
#include "../../uniform_distribution.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(inquery_fixture);

void inquery_fixture::setUp() { }

//-----------------------------------------------------------------------------
void inquery_fixture::tearDown() { }

//-----------------------------------------------------------------------------
xml::node inquery_fixture::get_object(const string &f,const string &n) const
{
    xml::node root  = xml::create_from_file(f);
    return root.get_child(n);
}


//-----------------------------------------------------------------------------
void inquery_fixture::test_name()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(xml::io_node::name(get_object("object1.xml","object1"))
                   =="hello");
    CPPUNIT_ASSERT_THROW(xml::io_node::name(get_object("object1.xml","object2")),
                    pni::core::key_error);
}

//-----------------------------------------------------------------------------
void inquery_fixture::test_size()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(xml::io_node::size(get_object("object2.xml","object1"))==1);

    CPPUNIT_ASSERT(xml::io_node::size(get_object("object2.xml","object2"))==
            40);
}

//-----------------------------------------------------------------------------
void inquery_fixture::test_rank()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(xml::field::rank(get_object("object2.xml","object1"))==0);
    CPPUNIT_ASSERT(xml::field::rank(get_object("object2.xml","object2"))==2);
}

//-----------------------------------------------------------------------------
void inquery_fixture::test_shape()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t s = xml::io_node::shape(get_object("object2.xml","object1"));
    CPPUNIT_ASSERT(s == shape_t({1}));

    s = xml::field::shape(get_object("object2.xml","object2"));
    CPPUNIT_ASSERT(s == shape_t({10,4}));
}


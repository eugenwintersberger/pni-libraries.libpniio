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
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Testing XML IO node objects

#include <boost/test/unit_test.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <pni/io/nx/xml/io_node.hpp>
#include <pni/io/nx/xml/field.hpp>
#include <pni/core/types.hpp>
#include "../../uniform_distribution.hpp"

using namespace pni::core;
using namespace pni::io::nx;

BOOST_AUTO_TEST_SUITE(inquery_test)

    //-------------------------------------------------------------------------
    xml::node get_object(const string &f,const string &n) 
    {
        xml::node root  = xml::create_from_file(f);
        return root.get_child(n);
    }


    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_name)
    {
        xml::node n = get_object("object1.xml","object1");
        BOOST_CHECK_EQUAL(xml::io_node::name(n),"hello");

        n = get_object("object1.xml","object2");
        BOOST_CHECK_THROW(xml::io_node::name(n),pni::core::key_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_size)
    {
        xml::node n = get_object("object2.xml","object1");
        BOOST_CHECK_EQUAL(xml::io_node::size(n),1);

        n = get_object("object2.xml","object2");
        BOOST_CHECK_EQUAL(xml::io_node::size(n),40);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_rank)
    {
        xml::node n = get_object("object2.xml","object1");
        BOOST_CHECK_EQUAL(xml::field::rank(n),0);

        n = get_object("object2.xml","object2");
        BOOST_CHECK_EQUAL(xml::field::rank(n),2);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_shape)
    {
        shape_t s = xml::io_node::shape(get_object("object2.xml","object1"));
        shape_t r{1};
        BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(),s.end(),r.begin(),r.end());

        s = xml::field::shape(get_object("object2.xml","object2"));
        r = shape_t{10,4};
        BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(),s.end(),r.begin(),r.end());
    }

BOOST_AUTO_TEST_SUITE_END()

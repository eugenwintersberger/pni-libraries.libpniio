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

#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/current_function.hpp>
#include <pni/io/nx/xml/io_node.hpp>
#include <pni/core/types.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string/trim.hpp>

using namespace pni::core;
using namespace pni::io::nx;


BOOST_AUTO_TEST_SUITE(data_from_xml_test)


    //-------------------------------------------------------------------------
    xml::node get_object(const string &f,const string &n) 
    {
        xml::node root  = xml::create_from_file(f);
        return root.get_child(n);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_scalar)
    {
        xml::node o = get_object("object3.xml","field1");
        auto data = xml::io_node::data_from_xml<float32>(o);
        BOOST_CHECK_CLOSE(float32(1.23),data,1.e-6);

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_array)
    {
        typedef std::vector<uint32> vector_type;
        
        xml::node o = get_object("object3.xml","field2");
        auto data = xml::io_node::data_from_xml<vector_type>(o);
        BOOST_CHECK_EQUAL(data.size(),6);

        for(uint32 i=0;i<6;++i)
            BOOST_CHECK_EQUAL(data[i],i+1);
    }

    //----------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_string)
    {
        xml::node o = get_object("object3.xml","field3");

        BOOST_CHECK_EQUAL(xml::io_node::type_id(o),type_id_t::STRING);
        auto text = xml::io_node::data_from_xml<string>(o);
        boost::algorithm::trim(text);
        BOOST_CHECK_EQUAL(text,"This is a stupid text");
    }

    //----------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_bool)
    {
        xml::node o = get_object("object3.xml","field4");
        BOOST_CHECK(xml::io_node::data_from_xml<bool_t>(o));

        o = get_object("object3.xml","field5");
        BOOST_CHECK(!xml::io_node::data_from_xml<bool_t>(o));

        o = get_object("object3.xml","field6");
        BOOST_CHECK_THROW(xml::io_node::data_from_xml<bool_t>(o),
                          pni::io::parser_error);

        o = get_object("object3.xml","field7");
        BOOST_CHECK_THROW(xml::io_node::data_from_xml<bool_t>(o),
                          pni::io::parser_error);
    }

BOOST_AUTO_TEST_SUITE_END()

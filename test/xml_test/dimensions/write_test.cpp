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

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/xml/dimensions.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "../xml_test_common.hpp"

using namespace pni::core;
using namespace pni::io::nx;


BOOST_AUTO_TEST_SUITE(write_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_write_1)
    {
        using namespace boost::property_tree;
        
        shape_t s{55,100};

        xml::node root;
        root.add_child("dimensions",xml::dimensions::object_to_xml(s));

        write_xml("test.xml",root);
        
        xml::node readback = xml::create_from_file("test.xml");
    
        BOOST_CHECK_EQUAL(readback,root);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_write_2)
    {
        using namespace boost::property_tree;
        
        shape_t s;

        xml::node root;
        root.add_child("dimensions",xml::dimensions::object_to_xml(s));

        write_xml("test.xml",root);

        xml::node readback = xml::create_from_file("test.xml");
        BOOST_CHECK_EQUAL(readback,root);
    }

BOOST_AUTO_TEST_SUITE_END()

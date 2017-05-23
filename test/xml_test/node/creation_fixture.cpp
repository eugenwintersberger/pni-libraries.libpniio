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
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE hello world

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/xml/node.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/core/types.hpp>
#include <pni/core/error.hpp>

using namespace pni::core;
using namespace pni::io::nx;

static const string node_from_string_str = 
                                    "<node>\n<group> </group>\n<group>"
                                    " </group>\n<group> </group>\n </node>";
static const string node_from_bad_str = "this has to fail";

BOOST_AUTO_TEST_SUITE(creation_test)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_from_file)
    {
        xml::node n = xml::create_from_file("node_from_str.xml");
        BOOST_CHECK(!n.empty());
        BOOST_CHECK_EQUAL(n.size(),1);

        //has to fail because file does not exist
        BOOST_CHECK_THROW(xml::create_from_file("bla.xml"), pni::core::file_error);

        //not a well formed XML file
        BOOST_CHECK_THROW(xml::create_from_file("node_from_bad_file.xml"),
                           pni::io::parser_error);

        
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_from_string)
    {
        xml::node n = xml::create_from_string(node_from_string_str);

        BOOST_CHECK(!n.empty());
        BOOST_CHECK_EQUAL(n.size(),1);

        BOOST_CHECK_THROW(xml::create_from_string(node_from_bad_str),
                          pni::io::parser_error);
    }


BOOST_AUTO_TEST_SUITE_END()



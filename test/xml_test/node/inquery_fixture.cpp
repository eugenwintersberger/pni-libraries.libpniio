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

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/xml/node.hpp>
#include <pni/core/types.hpp>
#include <pni/core/error.hpp>

using namespace pni::core;
using namespace pni::io::nx;

struct inquery_fixture
{
    xml::node group;

    inquery_fixture():
        group(xml::create_from_file("inquery.xml").get_child("group"))
    {}
    
};

BOOST_FIXTURE_TEST_SUITE(inquery_test,inquery_fixture)


    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_get_attribute)
    {
        
        BOOST_CHECK_NO_THROW(xml::get_attribute(group,"name"));

        //not a well formed XML file
        BOOST_CHECK_THROW(xml::get_attribute(group,"type"), key_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_has_attribute)
    {

        BOOST_CHECK(xml::has_attribute(group,"name"));
        BOOST_CHECK(!xml::has_attribute(group,"type"));
    }

BOOST_AUTO_TEST_SUITE_END()

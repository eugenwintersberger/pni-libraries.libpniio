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
#include <pni/core/types.hpp>
#include <pni/core/error.hpp>
#include <pni/io/exceptions.hpp>

#include "dimensions_fixture.hpp"

using namespace pni::io::nx;
using namespace pni::core;

BOOST_FIXTURE_TEST_SUITE(read_test,dimensions_fixture)


    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_1)
    {
        read_file("dim1.xml");
        
        auto shape = xml::dimensions::object_from_xml<shape_t>(child_node);
        BOOST_CHECK_EQUAL(shape.size(),2);
        BOOST_CHECK_EQUAL(shape.front(),55);
        BOOST_CHECK_EQUAL(shape.back(),100);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_2)
    {
        read_file("dim2.xml");

        BOOST_CHECK_THROW(xml::dimensions::object_from_xml<shape_t>(child_node),
                          shape_mismatch_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_3)
    {
        read_file("dim3.xml");

        BOOST_CHECK_THROW(xml::dimensions::object_from_xml<shape_t>(child_node),
                          key_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_4)
    {
        read_file("dim4.xml");

        BOOST_CHECK_THROW(xml::dimensions::object_from_xml<shape_t>(child_node),
                          key_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_5)
    {
        read_file("dim5.xml");

        BOOST_CHECK_THROW(xml::dimensions::object_from_xml<shape_t>(child_node),
                          key_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_6)
    {
        read_file("dim6.xml");
        auto s = xml::dimensions::object_from_xml<shape_t>(child_node);
        BOOST_CHECK_EQUAL(s.size(),0);
    }

BOOST_AUTO_TEST_SUITE_END()

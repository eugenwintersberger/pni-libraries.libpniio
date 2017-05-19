//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jun 28, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <boost/test/unit_test.hpp>
#include <pni/io/nx/algorithms/is_valid.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/core/types.hpp>

#include "../algorithm_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct is_valid_test_fixture : algorithm_test_fixture
{
    is_valid_test_fixture():
        algorithm_test_fixture("is_valid_test.nx")
    {}
};

BOOST_FIXTURE_TEST_SUITE(is_valid_test,is_valid_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        BOOST_CHECK(is_valid(group));
        group.close();
        BOOST_CHECK(!is_valid(group));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {
        BOOST_CHECK(is_valid(field));
        field.close();
        BOOST_CHECK(!is_valid(field));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        BOOST_CHECK(is_valid(attribute));
        attribute.close();
        BOOST_CHECK(!is_valid(attribute));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_file)
    {
        BOOST_CHECK(is_valid(file));
        file.close();
        BOOST_CHECK(!is_valid(file));
    }

#ifndef _MSC_VER
    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_group)
    {
        h5::nxobject o;
        BOOST_CHECK(!is_valid(o));
        o = group;
        BOOST_CHECK(is_valid(o));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_field)
    {
        h5::nxobject o;
        BOOST_CHECK(!is_valid(o));
        o = field;
        BOOST_CHECK(is_valid(o)); 
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_attribute)
    {
        h5::nxobject o;
        BOOST_CHECK(!is_valid(o));
        o = attribute;
        BOOST_CHECK(is_valid(o));
    }
#endif

BOOST_AUTO_TEST_SUITE_END()

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
//  Created on: Jul 4, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <boost/test/unit_test.hpp>
#include <pni/io/nx/algorithms/get_root.hpp>
#include <pni/io/nx/algorithms/get_name.hpp>
#include <pni/io/nx/algorithms/get_object.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include "../algorithm_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct get_root_test_fixture : algorithm_test_fixture
{
    
    get_root_test_fixture():
        algorithm_test_fixture("get_root_test.nx")
    {
        root.create_group("entry","NXentry").
             create_group("instrument","NXinstrument").
             create_group("detector","NXdetector");

    }
};

BOOST_FIXTURE_TEST_SUITE(get_root_test,get_root_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        h5::nxgroup g = get_object(root,"/entry/instrument"); 
        BOOST_CHECK_EQUAL(get_name(get_root(g)),"/");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_group)
    {
        BOOST_CHECK_EQUAL(get_name(get_root(get_object(root,":NXentry"))),"/");
        BOOST_CHECK_EQUAL(get_name(get_root(get_object(root,":NXentry/:NXinstrument"))),"/");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {
        BOOST_CHECK_EQUAL(get_name(get_root(field)),"/");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_field)
    {
        BOOST_CHECK_EQUAL(get_name(get_root(o_field)),"/");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        BOOST_CHECK_EQUAL(get_name(get_root(attribute)),"/");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_attribute)
    {
        BOOST_CHECK_EQUAL(get_name(get_root(o_attribute)),"/");
    }

BOOST_AUTO_TEST_SUITE_END()


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
#include <pni/io/nx/algorithms/create_group.hpp>
#include <pni/io/nx/algorithms/get_object.hpp>
#include <pni/io/nx/algorithms/get_class.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include "../algorithm_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;
using pni::io::invalid_object_error;

struct get_class_test_fixture : algorithm_test_fixture
{
    get_class_test_fixture():
        algorithm_test_fixture("get_class_test.nx")
    {
        root.create_group("entry","NXentry"); 
        root.create_group("log");
    }
};

BOOST_FIXTURE_TEST_SUITE(get_class_test,get_class_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        auto g = get_object(root,":NXentry");
        auto go = get_object(root,":NXentry");

        BOOST_CHECK_EQUAL(get_class(g),"NXentry");
        BOOST_CHECK_EQUAL(get_class(go),"NXentry");
        BOOST_CHECK_THROW(get_class(h5::nxobject(h5::nxgroup())),
                          invalid_object_error);
        BOOST_CHECK_THROW(get_class(h5::nxgroup()),invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_not_exists)
    {
        auto g = get_object(root,"log");
        BOOST_CHECK_EQUAL(get_class(g),"");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {
        BOOST_CHECK_THROW(get_class(o_field),type_error);
        //BOOST_CHECK_THROW(get_class(field),type_error); - static assert
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        BOOST_CHECK_THROW(get_class(o_attribute),type_error);
        //BOOST_CHECK_THROW(get_class(attribute),type_error); - static assert
    }

BOOST_AUTO_TEST_SUITE_END()


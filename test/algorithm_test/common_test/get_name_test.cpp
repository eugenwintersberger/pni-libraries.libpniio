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
#include <pni/io/nx/algorithms/get_name.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include "../algorithm_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx; 
using pni::io::invalid_object_error;
using pni::io::io_error;

struct get_name_test_fixture : algorithm_test_fixture
{
    get_name_test_fixture():
        algorithm_test_fixture("get_name_test.nx")
    {}
};

BOOST_FIXTURE_TEST_SUITE(get_name_test,get_name_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        BOOST_CHECK_EQUAL(get_name(group), "/");
        BOOST_CHECK_THROW(get_name(h5::nxgroup()),invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {
        BOOST_CHECK_EQUAL(get_name(field), "data");
        BOOST_CHECK_THROW(get_name(h5::nxfield()),invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        BOOST_CHECK_EQUAL(get_name(attribute),"NX_class");
        BOOST_CHECK_THROW(get_name(h5::nxattribute()),invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_group)
    {
        BOOST_CHECK_EQUAL(get_name(o_group) ,"/");
        BOOST_CHECK_THROW(get_name(h5::nxobject(h5::nxgroup())),
                          invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_field)
    {
        BOOST_CHECK_EQUAL(get_name(o_field),"data");
        BOOST_CHECK_THROW(get_name(h5::nxobject(h5::nxfield())),
                          invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_attribute)
    {
        BOOST_CHECK_EQUAL(get_name(o_attribute),"NX_class");
        BOOST_CHECK_THROW(get_name(h5::nxobject(h5::nxattribute())),
                          invalid_object_error);
       
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_errors)
    {
        h5::nxobject object = h5::nxgroup();
        BOOST_CHECK_THROW(get_name(object),invalid_object_error);
    }

BOOST_AUTO_TEST_SUITE_END()


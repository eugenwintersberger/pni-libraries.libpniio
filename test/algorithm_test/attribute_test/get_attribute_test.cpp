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
#include "../algorithm_test_fixture.hpp"

#include <pni/io/nx/algorithms/get_attribute.hpp>
#include <pni/io/nx/algorithms/is_valid.hpp>
#include <pni/io/nx/algorithms/get_name.hpp>
#include <pni/io/nx/algorithms/set_unit.hpp>
#include <pni/io/exceptions.hpp>


using namespace pni::core;
using namespace pni::io::nx;
using pni::io::object_error;
using pni::io::invalid_object_error;

struct get_attribute_test_fixture : algorithm_test_fixture
{
    
    get_attribute_test_fixture():
        algorithm_test_fixture("get_attribute_test.nx")
    {
        set_unit(field,"mm");
        group = group.create_group("entry","NXentry");
        o_group = group;
    }
};

BOOST_FIXTURE_TEST_SUITE(get_attribute_test,get_attribute_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        BOOST_CHECK(is_valid(get_attribute(o_group,"NX_class")));
        BOOST_CHECK_EQUAL(get_name(get_attribute(o_group,"NX_class")),"NX_class");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {
        BOOST_CHECK_EQUAL(get_name(get_attribute(o_field,"units")),"units");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        BOOST_CHECK_THROW(get_attribute(o_attribute,"bla"),type_error);
    }

    BOOST_AUTO_TEST_CASE(test_errors)
    {
        h5::nxfield f;
        h5::nxgroup g;
        h5::nxobject o = f;
        BOOST_CHECK_THROW(get_attribute(f,"test"),invalid_object_error);
        BOOST_CHECK_THROW(get_attribute(g,"test"),invalid_object_error);
        BOOST_CHECK_THROW(get_attribute(o,"test"),invalid_object_error);

        BOOST_CHECK_THROW(get_attribute(group,"hello"),key_error);
        BOOST_CHECK_THROW(get_attribute(o_group,"hello"),key_error);
    }

BOOST_AUTO_TEST_SUITE_END()

//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jul 31, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/algorithms/get_attribute.hpp>
#include <pni/io/nx/algorithms/is_valid.hpp>
#include <pni/io/nx/algorithms/get_name.hpp>
#include <pni/io/nx/algorithms/set_unit.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/algorithms.hpp>
#include <vector>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include "../algorithm_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;
using pni::io::object_error;
using pni::io::invalid_object_error;


struct get_attributes_test_fixture : algorithm_test_fixture
{
    
    get_attributes_test_fixture():
        algorithm_test_fixture("get_attributes_test.nx")
    {
        set_unit(o_field,"mm");
    };
};


BOOST_FIXTURE_TEST_SUITE(get_attributes_test,get_attributes_test_fixture)

    typedef std::vector<h5::nxobject> container_type;

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        auto a = get_attributes<container_type>(o_group);
        BOOST_CHECK_EQUAL(a.size(),6);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {
        auto a = get_attributes<container_type>(o_field);
        BOOST_CHECK_EQUAL(a.size(),1);
        BOOST_CHECK_EQUAL(get_name(a.front()),"units");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        BOOST_CHECK_THROW(get_attributes<container_type>(o_attribute),type_error);
    }

BOOST_AUTO_TEST_SUITE_END()

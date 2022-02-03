//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pninexus.
//
// pninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
//  Created on: Apr 7, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include <boost/test/unit_test.hpp>
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include <boost/current_function.hpp>
#include <pni/error/exception_utils.hpp>
#include <vector>
#include <list>
#include "types.hpp"

using namespace pni;

struct check_equal_size_test_fixture
{
    vector_type std_vector;
    list_type   std_list;
    array_type  std_array;
    fixed_dim_array<size_t,2> fdarray_1;
    fixed_dim_array<size_t,1> fdarray_2;
    static_array<size_t,2,5>  sarray_1;
    dynamic_array<size_t>     darray_1;
    dynamic_array<float64>    darray_2;

    check_equal_size_test_fixture()
    {}
};


BOOST_FIXTURE_TEST_SUITE(check_equal_size_test,check_equal_size_test_fixture)

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_no_throw)
{
    std_vector = vector_type(10);

    BOOST_CHECK(check_equal_size(std_vector,std_array));
    BOOST_CHECK(check_equal_size(std_vector,sarray_1));

    fdarray_1 = fixed_dim_array<size_t,2>::create(shape_t{4,10});
    BOOST_CHECK(!check_equal_size(fdarray_1,std_vector));
    BOOST_CHECK(!check_equal_size(fdarray_1,sarray_1));

    vector_type v1,v2;
    BOOST_CHECK(check_equal_size(v1,v2));

}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_throw)
{
    std_vector = vector_type(100);

    BOOST_CHECK_THROW(check_equal_size(std_vector,std_array,EXCEPTION_RECORD)
                         ,size_mismatch_error);
    BOOST_CHECK_THROW(check_equal_size(sarray_1,std_vector,EXCEPTION_RECORD),
                         size_mismatch_error);

    vector_type v1,v2;
    BOOST_CHECK_NO_THROW(check_equal_size(v1,v2));
}

BOOST_AUTO_TEST_SUITE_END()

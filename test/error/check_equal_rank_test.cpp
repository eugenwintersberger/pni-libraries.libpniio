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
//  Created on: Apr 8, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include <boost/test/included/unit_test.hpp>
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include <boost/current_function.hpp>
#include <vector>
#include <list>

#include <pni/error/exception_utils.hpp>
#include "types.hpp"

using namespace pni;

struct check_equal_rank_test_fixture
{
    vector_type                std_vector;
    dynamic_array<float64>     darray_1;
    fixed_dim_array<uint32,2>  farray_1;
    static_array<size_t,4,4,5> sarray_1;

    check_equal_rank_test_fixture():
        darray_1(dynamic_array<float64>::create(shape_t{2,3}))
    {}
};

BOOST_FIXTURE_TEST_SUITE(check_equal_rank_test,check_equal_rank_test_fixture)


//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_no_throw)
{
    BOOST_CHECK(check_equal_rank(darray_1,farray_1));
    BOOST_CHECK(!check_equal_rank(farray_1,sarray_1));

}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_throw)
{
    BOOST_CHECK_NO_THROW(check_equal_rank(darray_1,farray_1,EXCEPTION_RECORD));
    BOOST_CHECK_THROW(check_equal_rank(darray_1,sarray_1,EXCEPTION_RECORD),
                         shape_mismatch_error);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_invalid_input)
{
    dynamic_array<float64> d1,d2;

    BOOST_CHECK(check_equal_rank(d1,d2));
    BOOST_CHECK(!check_equal_rank(d1,darray_1));
    BOOST_CHECK(!check_equal_rank(darray_1,d2));

    BOOST_CHECK_NO_THROW(check_equal_rank(d1,d2,EXCEPTION_RECORD));
    BOOST_CHECK_THROW(check_equal_rank(d1,darray_1,EXCEPTION_RECORD),
                         shape_mismatch_error);
    BOOST_CHECK_THROW(check_equal_rank(darray_1,d2,EXCEPTION_RECORD),
                         shape_mismatch_error);
    
}

BOOST_AUTO_TEST_SUITE_END()

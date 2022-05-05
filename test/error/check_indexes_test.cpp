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

struct check_indexes_test_fixture
{
    vector_type std_vector;
    std::array<size_t,1> index_1;
    std::array<size_t,2> index_2;
    std::array<size_t,3> index_3;

    check_indexes_test_fixture():
        index_1({{4}}),
        index_2({{5,3}}),
        index_3({{7,3,10}})
    {}
};


BOOST_FIXTURE_TEST_SUITE(check_indexes_test,check_indexes_test_fixture)


//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_no_throw)
{
    //check 1D case
    BOOST_CHECK(check_indexes(vector_type{0},index_1));
    BOOST_CHECK(check_indexes(vector_type{3},index_1));
    BOOST_CHECK(!check_indexes(vector_type{4},index_1));
    BOOST_CHECK(!check_indexes(vector_type{10},index_1));

    // check 2D case
    BOOST_CHECK(check_indexes(vector_type{2,1},index_2));
    BOOST_CHECK(check_indexes(vector_type{4,2},index_2));
    BOOST_CHECK(!check_indexes(vector_type{10,10},index_2));
    BOOST_CHECK(!check_indexes(vector_type{10,2},index_2));
    BOOST_CHECK(!check_indexes(vector_type{3,5},index_2));

    // check the 3D case
    BOOST_CHECK(check_indexes(vector_type{0,0,0},index_3));
    BOOST_CHECK(!check_indexes(vector_type{7,0,0},index_3));
    BOOST_CHECK(!check_indexes(vector_type{0,3,0},index_3));
    BOOST_CHECK(!check_indexes(vector_type{0,0,10},index_3));

    // check different ranks
    BOOST_CHECK(!check_indexes(vector_type{2},index_3));
    BOOST_CHECK(!check_indexes(vector_type{3,2},index_1));

}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_throw)
{
    //check 1D case
    BOOST_CHECK_NO_THROW(check_indexes(vector_type{0},index_1,PNINEXUS_EXCEPTION_RECORD));
    BOOST_CHECK_NO_THROW(check_indexes(vector_type{3},index_1,PNINEXUS_EXCEPTION_RECORD));
    BOOST_CHECK_THROW(check_indexes(vector_type{4},index_1,PNINEXUS_EXCEPTION_RECORD),
                         index_error);
    BOOST_CHECK_THROW(check_indexes(vector_type{10},index_1,PNINEXUS_EXCEPTION_RECORD),
                         index_error);

    // check 2D case
    BOOST_CHECK_NO_THROW(check_indexes(vector_type{2,1},index_2,PNINEXUS_EXCEPTION_RECORD));
    BOOST_CHECK_NO_THROW(check_indexes(vector_type{4,2},index_2,PNINEXUS_EXCEPTION_RECORD));
    BOOST_CHECK_THROW(check_indexes(vector_type{10,10},index_2,PNINEXUS_EXCEPTION_RECORD),
                         index_error);
    BOOST_CHECK_THROW(check_indexes(vector_type{10,2},index_2,PNINEXUS_EXCEPTION_RECORD),
                         index_error);
    BOOST_CHECK_THROW(check_indexes(vector_type{3,5},index_2,PNINEXUS_EXCEPTION_RECORD),
                         index_error);
    
    // check the 3D case
    BOOST_CHECK_NO_THROW(check_indexes(vector_type{0,0,0},index_3,PNINEXUS_EXCEPTION_RECORD));
    BOOST_CHECK_THROW(check_indexes(vector_type{7,0,0},index_3,PNINEXUS_EXCEPTION_RECORD),
                         index_error);
    BOOST_CHECK_THROW(check_indexes(vector_type{0,3,0},index_3,PNINEXUS_EXCEPTION_RECORD),
                         index_error);
    BOOST_CHECK_THROW(check_indexes(vector_type{0,0,10},index_3,PNINEXUS_EXCEPTION_RECORD),
                         index_error);

    // check different ranks
    BOOST_CHECK_THROW(check_indexes(vector_type{2},index_3,PNINEXUS_EXCEPTION_RECORD),
                         shape_mismatch_error);
    BOOST_CHECK_THROW(check_indexes(vector_type{3,2},index_1,PNINEXUS_EXCEPTION_RECORD),
                         shape_mismatch_error);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_invalid_input)
{
    BOOST_CHECK(check_indexes(vector_type(),vector_type()));
    BOOST_CHECK_NO_THROW(check_indexes(vector_type(),vector_type(),PNINEXUS_EXCEPTION_RECORD));
    BOOST_CHECK_THROW(check_indexes(vector_type(),index_3,PNINEXUS_EXCEPTION_RECORD),
                         shape_mismatch_error);
    BOOST_CHECK_THROW(check_indexes(vector_type{2,2},vector_type(),PNINEXUS_EXCEPTION_RECORD),
                         shape_mismatch_error);
}

BOOST_AUTO_TEST_SUITE_END()

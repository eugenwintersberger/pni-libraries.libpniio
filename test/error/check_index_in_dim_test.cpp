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
#include "../boost_unit_test.hpp"
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include <boost/current_function.hpp>
#include <pni/error/exception_utils.hpp>
#include <vector>
#include <list>
#include "types.hpp"

using namespace pni;

BOOST_AUTO_TEST_SUITE(check_index_in_dim_test)

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_no_throw)
{
    BOOST_CHECK(check_index_in_dim(0,100));
    BOOST_CHECK(check_index_in_dim(10,100));
    BOOST_CHECK(check_index_in_dim(99,100));
    BOOST_CHECK(!check_index_in_dim(100,100));
    BOOST_CHECK(!check_index_in_dim(101,100));
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_throw)
{
    BOOST_CHECK_NO_THROW(check_index_in_dim(0,100,EXCEPTION_RECORD));
    BOOST_CHECK_NO_THROW(check_index_in_dim(10,100,EXCEPTION_RECORD));
    BOOST_CHECK_NO_THROW(check_index_in_dim(99,100,EXCEPTION_RECORD));
    BOOST_CHECK_THROW(check_index_in_dim(100,100,EXCEPTION_RECORD),
                         index_error);
    BOOST_CHECK_THROW(check_index_in_dim(101,100,EXCEPTION_RECORD),
                         index_error);
}

BOOST_AUTO_TEST_SUITE_END()

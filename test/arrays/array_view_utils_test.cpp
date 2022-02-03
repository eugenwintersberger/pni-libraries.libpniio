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
// ===========================================================================
//
//  Created on: Apr 6, 2014
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
#include <pni/arrays.hpp>

using namespace pni;

BOOST_AUTO_TEST_SUITE(array_view_utils_test)
    
    //========================================================================
    BOOST_AUTO_TEST_CASE(test_is_index_type)
    {
        BOOST_CHECK(is_index_type<int>::value);
        BOOST_CHECK(!is_index_type<std::vector<size_t>>::value);
        BOOST_CHECK(is_index_type<slice>::value);
        BOOST_CHECK(is_index_type<size_t>::value);
        BOOST_CHECK(!is_index_type<float64>::value);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_is_index_types)
    {

        typedef is_index_types<int,slice,size_t> type_1;
        BOOST_CHECK(type_1::value);

        typedef is_index_types<int,float32> type_2;
        BOOST_CHECK(!type_2::value);

        typedef is_index_types<size_t> type_3;
        BOOST_CHECK(type_3::value);

        typedef is_index_types<std::vector<size_t>> type_4;
        BOOST_CHECK(!type_4::value);
    }

BOOST_AUTO_TEST_SUITE_END()



//-----------------------------------------------------------------------------








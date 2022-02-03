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
//  Created on: Apr 11, 2014
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
#include <pni/types/container_trait.hpp>

using namespace pni;

BOOST_AUTO_TEST_SUITE(container_trait_test)

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_vector)
    {
        typedef std::vector<size_t> vector_type;
        typedef container_trait<vector_type> trait_type;

        BOOST_CHECK(trait_type::is_random_access);
        BOOST_CHECK(trait_type::is_iterable);
        BOOST_CHECK(trait_type::is_contiguous);
        BOOST_CHECK(!trait_type::is_multidim);
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_array)
    {
        typedef std::array<size_t,4> array_type;
        typedef container_trait<array_type> trait_type;

        BOOST_CHECK(trait_type::is_random_access);
        BOOST_CHECK(trait_type::is_iterable);
        BOOST_CHECK(trait_type::is_contiguous);
        BOOST_CHECK(!trait_type::is_multidim);
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_list)
    {
        typedef std::list<size_t> list_type;
        typedef container_trait<list_type> trait_type;

        BOOST_CHECK(!trait_type::is_random_access);
        BOOST_CHECK(trait_type::is_iterable);
        BOOST_CHECK(!trait_type::is_contiguous);
        BOOST_CHECK(!trait_type::is_multidim);
    }

BOOST_AUTO_TEST_SUITE_END()

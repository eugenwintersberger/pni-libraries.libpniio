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
#include <iostream>
#include <pni/types/bool.hpp>

using namespace pni;


BOOST_AUTO_TEST_SUITE(bool_test)

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_construction)
    {
        BOOST_TEST_MESSAGE("test bool_t construction...");
        bool_t bvalue;  //default constructed - should be false
        BOOST_CHECK(!bvalue);
        
        bool_t bvalue2 = true; 
        BOOST_CHECK(bvalue2);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_comparison)
    {
        BOOST_TEST_MESSAGE("test bool_t comparison...");
        bool_t v1;
        bool_t v2 = true;
        bool_t v3 = false;

        BOOST_CHECK(v1 != v2);
        BOOST_CHECK(v1 == v3);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_assignment)
    {
        BOOST_TEST_MESSAGE("test bool_t assignment...");
        bool_t v1;
        BOOST_CHECK(!v1);

        v1 = true;
        BOOST_CHECK(v1);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_compatability)
    {
        BOOST_TEST_MESSAGE("test bool_t vector compatability ...");
        typedef std::vector<bool_t> vector_type;

        vector_type v(10);
        
        bool_t *ptr = v.data();
        for(auto x: v) BOOST_CHECK_EQUAL(x,*ptr++);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_operators)
    {
        BOOST_TEST_MESSAGE("test bool_t with operators...");
        bool_t v1 = true;
        bool_t v2 = false;

        BOOST_CHECK(!(v1 && v2));
        BOOST_CHECK(v1 && v1);

        BOOST_CHECK(v1 || v2);
        BOOST_CHECK(!(v2 || v2));
    }

BOOST_AUTO_TEST_SUITE_END()

//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jan 9, 2015
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
#include <boost/test/tools/floating_point_comparison.hpp>

#include <pni/types.hpp>
#include <pni/type_erasures.hpp>

#include "../value/fixture.hpp"
#include "../value/types.hpp"

using namespace pni;

BOOST_AUTO_TEST_SUITE(value_ref_construction_test)

    BOOST_AUTO_TEST_CASE(test_default_construction)
    {
        value_ref v;
        BOOST_CHECK_THROW(v.as<double>(),memory_not_allocated_error);
        BOOST_CHECK_THROW(v.type_id(),memory_not_allocated_error);

    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_from_value,T,all_types)
    {
        fixture<T> f;
        value_ref v1(std::ref(f.value_1));
        value_ref v2(std::ref(f.value_2));

        BOOST_CHECK_EQUAL(v1.as<T>(),f.value_1);
        BOOST_CHECK_EQUAL(v2.as<T>(),f.value_2);

        f.value_1 = f.generator();
        f.value_2 = f.generator();

        BOOST_CHECK_EQUAL(v1.as<T>(),f.value_1);
        BOOST_CHECK_EQUAL(v2.as<T>(),f.value_2);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_construction,T,all_types)
    {
        fixture<T> f;
        value_ref v1(std::ref(f.value_1));
        value_ref v2(v1);
        BOOST_CHECK_EQUAL(v1.as<T>(),v2.as<T>());

        //change value_1
        f.value_1 = f.generator();
        BOOST_CHECK_EQUAL(v1.as<T>(),f.value_1);
        BOOST_CHECK_EQUAL(v2.as<T>(),f.value_1);

    }

BOOST_AUTO_TEST_SUITE_END()


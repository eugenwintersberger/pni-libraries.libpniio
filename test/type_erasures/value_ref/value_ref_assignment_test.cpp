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
#include <boost/test/unit_test.hpp>
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include <boost/test/tools/floating_point_comparison.hpp>

#include <pni/type_erasures.hpp>
#include "../value/fixture.hpp"
#include "../value/types.hpp"

using namespace pni;

BOOST_AUTO_TEST_SUITE(value_ref_assignment_test)

    BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_assignment,T,all_types)
    {
        fixture<T> f;
        value_ref v1(std::ref(f.value_1)); 
        value_ref v2(std::ref(f.value_2));

        v2 = v1; //now v2 referes to the same value - value_1

        BOOST_CHECK_EQUAL(v1.as<T>(),f.value_1);
        BOOST_CHECK_EQUAL(v2.as<T>(),f.value_1);

        f.value_1 = f.generator();

        BOOST_CHECK_EQUAL(v1.as<T>(),f.value_1);
        BOOST_CHECK_EQUAL(v2.as<T>(),f.value_1);
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_assignment_from_value,T,all_types)
    {
        fixture<T> f;
        value v(f.value_1);
        value_ref ref(std::ref(f.value_2));
    
        ref = v;
        BOOST_CHECK_EQUAL(ref.as<T>(),f.value_1);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_from_T,T,all_types)
    {
        fixture<T> f;
        value_ref v(std::ref(f.value_1));
        v = f.value_2;
        BOOST_CHECK_EQUAL(v.as<T>(),f.value_2);
        BOOST_CHECK_EQUAL(f.value_2,f.value_1);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_to_value,T,all_types)
    {
        fixture<T> f;
        value_ref v_ref(std::ref(f.value_1));
        value v = to_value(v_ref);
        
        BOOST_CHECK_EQUAL(v.as<T>(),v_ref.as<T>());
        BOOST_CHECK_EQUAL(v.as<T>(),f.value_1);
    }

BOOST_AUTO_TEST_SUITE_END()



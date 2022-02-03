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
//  Created on: Apr 28, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include "../../boost_unit_test.hpp"
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include <pni/type_erasures.hpp>

#include "array_types.hpp"
#include "fixture.hpp"

using namespace pni;

BOOST_AUTO_TEST_SUITE(array_iterator_test)

    BOOST_AUTO_TEST_CASE_TEMPLATE(test_iterator,AT,all_array_types)
    {
        typedef typename md_array_trait<AT>::value_type value_type;
        fixture<AT> f;

        array a1(f.mdarray_1);
        array a2(f.mdarray_2);
     
        size_t index = 0;
        auto iter1 = a1.begin();
        auto iter2 = a2.begin();

        for(;iter1!=a1.end();++iter1,++iter2,++index)
        {
            *iter2 = *iter1;
            *iter1 = f.mdarray_2[index];
            BOOST_CHECK_EQUAL((*iter1).as<value_type>(),f.mdarray_2[index]);
            BOOST_CHECK_EQUAL((*iter2).as<value_type>(),f.mdarray_1[index]);

            value v(to_value(*iter1));
            BOOST_CHECK_EQUAL(v.as<value_type>(),f.mdarray_2[index]);
        }
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_const_iterator,AT,all_array_types)
    {
        typedef typename md_array_trait<AT>::value_type value_type;
        fixture<AT> f;
        
        array a1(f.mdarray_1);
        const array &r = a1;

        size_t index = 0;
        auto iter = r.begin();
        for(;iter!=r.end();++iter,++index)
        {
            BOOST_CHECK_EQUAL((*iter).as<value_type>(),f.mdarray_1[index]);

            value v(*iter);
            BOOST_CHECK_EQUAL(v.as<value_type>(),f.mdarray_1[index]);
        }
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_foreach,AT,all_array_types)
    {
        typedef typename md_array_trait<AT>::value_type value_type;
        fixture<AT> f;

        array a1(f.mdarray_1);
     
        size_t index = 0;
        for(auto v: a1)
            v = f.mdarray_1[index++];


        index = 0;
        for(auto v: a1)
            BOOST_CHECK_EQUAL(v.as<value_type>(),f.mdarray_1[index++]); 
    }

BOOST_AUTO_TEST_SUITE_END()

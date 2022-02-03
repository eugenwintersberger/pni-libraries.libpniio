//!
//! (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of pninexus.
//!
//! pninexus is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! pninexus is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with pninexus.  If not, see <http://www.gnu.org/licenses/>.
//!
//! ===========================================================================
//!
//!  Created on: Apr 28, 2015
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
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

BOOST_AUTO_TEST_SUITE(array_access_test)
   
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_linear_read_at,AT,all_array_types)
    {
        typedef typename md_array_trait<AT>::value_type value_type;
        fixture<AT> f;

        array a(f.mdarray_1);
        const array &aref = a;

        //reading from the instance itself
        for(size_t i=0;i<a.size();++i)
        {
            BOOST_CHECK_EQUAL(a.at(i).as<value_type>(),f.mdarray_1.at(i));
            BOOST_CHECK_EQUAL(aref.at(i).as<value_type>(),f.mdarray_1.at(i));
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_linear_write_at,AT,all_array_types)
    {
        typedef typename md_array_trait<AT>::value_type value_type;
        fixture<AT> f;

        array a1(f.mdarray_1);
        array a2(f.mdarray_2);

        //reading from the instance itself
        for(size_t i=0;i<a1.size();++i)
        {
            a2.at(i) = a1.at(i);
            a1.at(i) = f.mdarray_2.at(i);
            BOOST_CHECK_EQUAL(a1.at(i).as<value_type>(),f.mdarray_2.at(i));
            BOOST_CHECK_EQUAL(a2.at(i).as<value_type>(),f.mdarray_1.at(i));
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_linear_read_operator,AT,all_array_types)
    {
        typedef typename md_array_trait<AT>::value_type value_type;
        fixture<AT> f;

        array a(f.mdarray_1);
        const array &aref = a;

        //reading from the instance itself
        for(size_t i=0;i<a.size();++i)
        {
            BOOST_CHECK_EQUAL(a[i].as<value_type>(),f.mdarray_1[i]);
            BOOST_CHECK_EQUAL(aref[i].as<value_type>(),f.mdarray_1[i]);
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_linear_write_operator,AT,all_array_types)
    {
        typedef typename md_array_trait<AT>::value_type value_type;
        fixture<AT> f;
        
        array a1(f.mdarray_1);
        array a2(f.mdarray_2);

        //reading from the instance itself
        for(size_t i=0;i<a1.size();++i)
        {
            a2[i] = a1[i];
            a1[i] = f.mdarray_2[i];
            BOOST_CHECK_EQUAL(a1[i].as<value_type>(),f.mdarray_2[i]);
            BOOST_CHECK_EQUAL(a2[i].as<value_type>(),f.mdarray_1[i]);
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_linear_read_multidim,AT,all_array_types)
    {
        typedef typename md_array_trait<AT>::value_type value_type;
        typedef array::element_index index_type;
        fixture<AT> f;

        array a(f.mdarray_1);
        const array &aref = a;

        //reading from the instance itself
        for(size_t i=0;i<f.shape[0];++i)
        {
            for(size_t j=0;j<f.shape[1];++j)
            {
                BOOST_CHECK_EQUAL(a(index_type{i,j}).as<value_type>(),
                                  f.mdarray_1(i,j));
                BOOST_CHECK_EQUAL(aref(index_type{i,j}).as<value_type>(),
                                  f.mdarray_1(i,j));
            }
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_linear_write_multidim,AT,all_array_types)
    {
        typedef typename md_array_trait<AT>::value_type value_type;
        typedef array::element_index index_type;
        fixture<AT> f;

        array a1(f.mdarray_1);
        array a2(f.mdarray_2);

        //reading from the instance itself
        for(size_t i=0;i<f.shape[0];++i)
        {
            for(size_t j=0;j<f.shape[1];++j)
            {
                index_type index{i,j};
                a2(index) = a1(index);
                a1(index) = f.mdarray_2(i,j);
                BOOST_CHECK_EQUAL(a1(index).as<value_type>(),
                                  f.mdarray_2(i,j));
                BOOST_CHECK_EQUAL(a2(index).as<value_type>(),
                                  f.mdarray_1(i,j));
            }
        }
    }
BOOST_AUTO_TEST_SUITE_END()


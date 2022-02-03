//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jul 25, 2012
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

#include <pni/algorithms/math/div_op.hpp>
#include "array_types.hpp"
#include "fixture.hpp"
#include "number_ranges.hpp"

using namespace pni;

BOOST_AUTO_TEST_SUITE(div_operator_test)

    BOOST_AUTO_TEST_CASE_TEMPLATE(construction_test,AT,all_array_types)
    {
        typedef fixture<AT> fixture_type; 
        typedef div_op<AT,AT> aa_div_op;
        typedef div_op<typename fixture_type::scalar_type,AT> sa_div_op;
        typedef div_op<AT,typename fixture_type::scalar_type> as_div_op;

        fixture_type f((div_ranges<typename fixture_type::value_type>()));

        aa_div_op o1(f.lhs,f.rhs);
        BOOST_CHECK_EQUAL(o1.size(),f.lhs.size());
        BOOST_CHECK_EQUAL(o1.size(),f.rhs.size());

        sa_div_op o2(f.lhs_s,f.rhs);
        BOOST_CHECK_EQUAL(o2.size(),f.rhs.size());

        as_div_op o3(f.lhs,f.rhs_s);
        BOOST_CHECK_EQUAL(o3.size(),f.lhs.size());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(access_test,AT,all_array_types)
    {
        typedef fixture<AT> fixture_type; 
        typedef typename fixture_type::value_type value_type;
        typedef typename fixture_type::scalar_type scalar_type;

        fixture_type f((div_ranges<value_type>()));

        div_op<AT,AT> o1(f.lhs,f.rhs);
        for(size_t index=0;index<o1.size();++index)
            BOOST_CHECK_EQUAL(o1[index],f.lhs[index]/f.rhs[index]);

        div_op<AT,scalar_type> o2(f.lhs,f.rhs_s);
        for(size_t index=0;index<o2.size();++index)
            BOOST_CHECK_EQUAL(o2[index], 
                              value_type(f.lhs[index]/f.rhs_s[index]));

        div_op<scalar_type,AT> o3(f.lhs_s,f.rhs);
        for(size_t index=0;index<o3.size();++index)
            BOOST_CHECK_EQUAL(o3[index], 
                              value_type(f.lhs_s[index]/f.rhs[index]));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(iterator_test,AT,all_array_types)
    {
        typedef fixture<AT> fixture_type; 
        typedef typename fixture_type::value_type value_type;
        typedef typename fixture_type::scalar_type scalar_type;

        fixture_type f((div_ranges<value_type>()));

        size_t index=0;
        div_op<AT,AT> o1(f.lhs,f.rhs);
        for(auto v: o1)
        {
            BOOST_CHECK_EQUAL(v,value_type(f.lhs[index]/f.rhs[index]));
            index++;
        }

        
        div_op<scalar_type,AT> o2(f.lhs_s,f.rhs);
        index=0;
        for(auto v: o2)
        {
            BOOST_CHECK_EQUAL(v,value_type(f.lhs_s[index]/f.rhs[index]));
            index++;
        }

        div_op<AT,scalar_type> o3(f.lhs,f.rhs_s);
        index=0;
        for(auto v: o3)
        {
            BOOST_CHECK_EQUAL(v,value_type(f.lhs[index]/f.rhs_s[index]));
            index++;
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(operator_test,AT,all_array_types)
    {
        typedef fixture<AT> fixture_type; 
        typedef typename fixture_type::value_type value_type;

        fixture_type f((div_ranges<value_type>()));
        auto result = AT::create(f.shape);

        result = f.lhs/f.rhs;
        BOOST_CHECK_EQUAL(result.size(),f.lhs.size());
        for(size_t index=0;index<result.size();++index)
            BOOST_CHECK_EQUAL(result[index],f.lhs[index]/f.rhs[index]);

        result = f.lhs_scalar/f.rhs;
        BOOST_CHECK_EQUAL(result.size(),f.rhs.size());
        for(size_t index=0;index<result.size();++index)
            BOOST_CHECK_EQUAL(result[index],f.lhs_scalar/f.rhs[index]);

        result = f.lhs / f.rhs_scalar;
        BOOST_CHECK_EQUAL(result.size(),f.lhs.size());
        for(size_t index=0;index<result.size();++index)
            BOOST_CHECK_EQUAL(result[index],f.lhs[index]/f.rhs_scalar);
        
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(operator_on_view_test,AT,all_array_types)
    {
        typedef fixture<AT> fixture_type; 
        typedef typename fixture_type::value_type value_type;
        typedef dynamic_array<value_type> result_type;

        fixture_type f((div_ranges<value_type>()));

        auto vrhs = f.rhs(0,slice(0,3),slice(0,4));
        auto vlhs = f.lhs(0,slice(0,3),slice(0,4));

        result_type result(vlhs / vrhs);
        for(size_t index=0;index<result.size();index++)
            BOOST_CHECK_EQUAL(result[index],
                              value_type(vlhs[index]/vrhs[index]));

        result = vlhs / f.rhs_scalar;
        for(size_t index=0;index<result.size();index++)
            BOOST_CHECK_EQUAL(result[index],
                              value_type(vlhs[index]/f.rhs_scalar));

        result = f.lhs_scalar / vrhs;
        for(size_t index=0;index<result.size();index++)
            BOOST_CHECK_EQUAL(result[index],
                              value_type(f.lhs_scalar/vrhs[index]));

    }

BOOST_AUTO_TEST_SUITE_END()




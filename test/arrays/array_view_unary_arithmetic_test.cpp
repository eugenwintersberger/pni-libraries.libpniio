//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Nov 28, 2013
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
#include <boost/mpl/joint_view.hpp>
#include "array_types.hpp"
#include "../data_generator.hpp"
#include "../math/number_ranges.hpp"

using namespace pni;

typedef  boost::mpl::joint_view<numeric_dynamic_arrays,
#if GCC_VERSION > 40800
                                boost::mpl::joint_view<
                                numeric_fixed_dim_arrays<3>,
                                numeric_static_arrays<2,3,5>
                                >
#else 
                                numeric_fixed_dim_arrays<3>
#endif
                                > numeric_array_types;


template<typename TestArrayT> struct fixture
{
    typedef TestArrayT array_type;
    typedef typename TestArrayT::value_type value_type;
    typedef random_generator<value_type> generator_type; 

    shape_t shape; 
    generator_type generator_rhs;
    generator_type generator_lhs;
    value_type rhs_scalar;
    array_type lhs;
    array_type lhs_orig;

    fixture(typename pni::type_info<value_type>::base_type rhs_lbound,
            typename pni::type_info<value_type>::base_type rhs_ubound,
            typename pni::type_info<value_type>::base_type lhs_lbound,
            typename pni::type_info<value_type>::base_type lhs_ubound):
        shape(shape_t{2,3,5}),
        generator_rhs(rhs_lbound,rhs_ubound),
        generator_lhs(lhs_lbound,lhs_ubound),
        rhs_scalar(generator_rhs()),
        lhs(array_type::create(shape)),
        lhs_orig(array_type::create(shape))
    {
        std::generate(lhs.begin(),lhs.end(),generator_lhs); 
        std::copy(lhs.begin(),lhs.end(),lhs_orig.begin());
    }
};

BOOST_AUTO_TEST_SUITE(array_view_unary_arithmetic_test)

    BOOST_AUTO_TEST_CASE_TEMPLATE(test_add_scalar,TestArrayT,numeric_array_types)
    {
        typedef fixture<TestArrayT> fixture_type; 
        typedef typename TestArrayT::value_type value_type;

        add_ranges<value_type> ranges;
        fixture_type fixture(ranges.rhs_min(),ranges.rhs_max(),
                             ranges.lhs_min(),ranges.lhs_max());

        auto view = fixture.lhs(0,slice(0,3),slice(0,5));
        view += fixture.rhs_scalar;

        //check if data has gone through
        for(size_t i=0;i<3;++i)
        {
            for(size_t j=0;j<5;++j)
            {
                BOOST_CHECK_EQUAL(view(i,j),fixture.lhs(0,i,j));
                BOOST_CHECK_EQUAL(view(i,j),
                                  fixture.lhs_orig(0,i,j)+fixture.rhs_scalar);
            }
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_add_array,TestArrayT,numeric_array_types)
    {
        typedef fixture<TestArrayT> fixture_type;
        typedef typename TestArrayT::value_type value_type;

        add_ranges<value_type> ranges;
        fixture_type fixture(ranges.rhs_min(),ranges.rhs_max(),
                             ranges.lhs_min(),ranges.lhs_max());

        auto view = fixture.lhs(1,slice(0,3),slice(0,5));
        dynamic_array<value_type> orig(view);
        auto view_shape = view.template shape<shape_t>();
        auto rhs = dynamic_array<value_type>::create(view_shape);
        std::generate(rhs.begin(),rhs.end(),fixture.generator_rhs);

        view += rhs;

        auto orig_iter = orig.begin();
        auto rhs_iter  = rhs.begin();
        for(auto v: view)
            BOOST_CHECK_EQUAL(v,(*orig_iter++)+(*rhs_iter++));

    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_sub_scalar,TestArrayT,numeric_array_types)
    {
        typedef fixture<TestArrayT> fixture_type; 
        typedef typename TestArrayT::value_type value_type;

        add_ranges<value_type> ranges;
        fixture_type fixture(ranges.rhs_min(),ranges.rhs_max(),
                             ranges.lhs_min(),ranges.lhs_max());

        auto view = fixture.lhs(slice(0,2),0,slice(0,5));
        view -= fixture.rhs_scalar;

        for(size_t i=0;i<2;++i)
            for(size_t j=0;j<5;++j)
            {
                BOOST_CHECK_EQUAL(view(i,j),fixture.lhs(i,0,j));
                BOOST_CHECK_EQUAL(view(i,j),
                                  value_type(fixture.lhs_orig(i,0,j)
                                              -fixture.rhs_scalar));
            }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_sub_array,TestArrayT,numeric_array_types)
    {
        typedef fixture<TestArrayT> fixture_type; 
        typedef typename TestArrayT::value_type value_type;
        
        add_ranges<value_type> ranges;
        fixture_type fixture(ranges.rhs_min(),ranges.rhs_max(),
                             ranges.lhs_min(),ranges.lhs_max());

        auto view = fixture.lhs(1,slice(0,3),slice(0,5));
        dynamic_array<value_type> orig(view);
        auto view_shape = view.template shape<shape_t>();
        auto rhs = dynamic_array<value_type>::create(view_shape);
        std::generate(rhs.begin(),rhs.end(),fixture.generator_rhs);

        view -= rhs;

        auto orig_iter = orig.begin();
        auto rhs_iter  = rhs.begin();
        for(auto v: view)
            BOOST_CHECK_EQUAL(v,value_type((*orig_iter++)-(*rhs_iter++)));
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_div_scalar,TestArrayT,numeric_array_types)
    {
        typedef fixture<TestArrayT> fixture_type;
        typedef typename TestArrayT::value_type value_type;
        
        div_ranges<value_type> ranges;
        fixture_type fixture(ranges.rhs_min(),ranges.rhs_max(),
                             ranges.lhs_min(),ranges.lhs_max());

        auto view = fixture.lhs(slice(0,2),slice(1,3),slice(2,5));
        view /= fixture.rhs_scalar;

        for(size_t i=0;i<2;++i)
            for(size_t j=0;j<2;++j)
                for(size_t k=0;k<3;++k)
                {
                    BOOST_CHECK_EQUAL(view(i,j,k),fixture.lhs(i,j+1,k+2));
                    BOOST_CHECK_EQUAL(view(i,j,k),
                                      value_type(fixture.lhs_orig(i,j+1,k+2)/
                                                 fixture.rhs_scalar));
                }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_div_array,TestArrayT,numeric_array_types)
    {
        typedef fixture<TestArrayT> fixture_type;
        typedef typename TestArrayT::value_type value_type;
        
        div_ranges<value_type> ranges;
        fixture_type fixture(ranges.rhs_min(),ranges.rhs_max(),
                             ranges.lhs_min(),ranges.lhs_max());

        auto view = fixture.lhs(1,slice(0,3),slice(0,5));
        dynamic_array<value_type> orig(view);
        auto view_shape = view.template shape<shape_t>();
        auto rhs = dynamic_array<value_type>::create(view_shape);
        std::generate(rhs.begin(),rhs.end(),fixture.generator_rhs);

        view /= rhs;

        auto orig_iter = orig.begin();
        auto rhs_iter  = rhs.begin();
        for(auto v: view)
            BOOST_CHECK_EQUAL(v,value_type((*orig_iter++)/(*rhs_iter++)));
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_mult_scalar,TestArrayT,numeric_array_types)
    {
        typedef fixture<TestArrayT> fixture_type;
        typedef typename TestArrayT::value_type value_type;
        
        mult_ranges<value_type> ranges;
        fixture_type fixture(ranges.rhs_min(),ranges.rhs_max(),
                             ranges.lhs_min(),ranges.lhs_max());

        auto view = fixture.lhs(slice(0,2),slice(0,2),3);
        view *= fixture.rhs_scalar;
        
        for(size_t i=0;i<2;++i)
            for(size_t j=0;j<2;++j)
            {
                BOOST_CHECK_EQUAL(view(i,j),fixture.lhs(i,j,3));
                BOOST_CHECK_EQUAL(view(i,j),
                                  value_type(fixture.lhs_orig(i,j,3)*
                                             fixture.rhs_scalar));
            }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_mult_array,TestArrayT,numeric_array_types)
    {
        typedef fixture<TestArrayT> fixture_type;
        typedef typename TestArrayT::value_type value_type;
        
        mult_ranges<value_type> ranges;
        fixture_type fixture(ranges.rhs_min(),ranges.rhs_max(),
                             ranges.lhs_min(),ranges.lhs_max());

        auto view = fixture.lhs(1,slice(0,3),slice(0,5));
        dynamic_array<value_type> orig(view);
        auto view_shape = view.template shape<shape_t>();
        auto rhs = dynamic_array<value_type>::create(view_shape);
        std::generate(rhs.begin(),rhs.end(),fixture.generator_rhs);

        view *= rhs;

        auto orig_iter = orig.begin();
        auto rhs_iter  = rhs.begin();
        for(auto v: view)
            BOOST_CHECK_EQUAL(v,value_type((*orig_iter++)*(*rhs_iter++)));
    }

BOOST_AUTO_TEST_SUITE_END()








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
//  Created on: Nov 27, 2013
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
#include <boost/current_function.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <pni/algorithms/math/inplace_arithmetics.hpp>

#include "array_types.hpp"
#include <cmath>
#include "number_ranges.hpp"
#include "fixture.hpp"


namespace std{

    //utility funtion template to check for the finiteness of a 
    //comples value. This is only the case if real and imaginary part 
    //are finite.
    template<typename GeneralT> bool isfinite(std::complex<GeneralT> v)
    {

        return isfinite(v.real()) && isfinite(v.imag());
    }
}



typedef inplace_arithmetics ip_type; 

BOOST_AUTO_TEST_SUITE(inplace_arithmetics_test)

    BOOST_AUTO_TEST_CASE_TEMPLATE(add_scalar_test,TestArrayT,all_array_types)
    {
        typedef typename TestArrayT::value_type value_type;
        fixture<TestArrayT> f((add_ranges<value_type>()));
    
        ip_type::add(f.lhs,f.rhs_scalar);

        for(size_t i=0;i<f.lhs.size();++i) 
        {
            if(!(std::isfinite)(f.lhs[i]))
            {
                BOOST_TEST_MESSAGE( "Infinite result "<<f.lhs[i]<<" from "<<
                                    f.lhs_orig[i]<<"+"<<f.rhs_scalar
                                    <<" at index "<<i<< "with type: "<<
                                    f.type_name);
            }
            else
            {
                BOOST_CHECK_EQUAL(f.lhs[i],
                                  value_type(f.lhs_orig[i]+f.rhs_scalar));
            }
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(add_array_test,TestArrayT,all_array_types)
    {
        typedef typename TestArrayT::value_type value_type;
        fixture<TestArrayT> f((add_ranges<value_type>()));
    
        ip_type::add(f.lhs,f.rhs);

        for(size_t i=0;i<f.lhs.size();++i) 
        {
            if(!(std::isfinite)(f.lhs[i]))
            {
                BOOST_TEST_MESSAGE( "Infinite result "<<f.lhs[i]<<" from "<<
                                    f.lhs_orig[i]<<"+"<<f.rhs[i]
                                    <<" at index "<<i<<" with type: "<<
                                    f.type_name);
            }
            else
            {
                BOOST_CHECK_EQUAL(f.lhs[i],
                                  value_type(f.lhs_orig[i]+f.rhs[i]));
            }
        }

    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(sub_scalar_test,TestArrayT,all_array_types)
    {
        typedef typename TestArrayT::value_type value_type;
        fixture<TestArrayT> f((add_ranges<value_type>()));
    
        ip_type::sub(f.lhs,f.rhs_scalar);

        for(size_t i=0;i<f.lhs.size();++i) 
        {
            if(!(std::isfinite)(f.lhs[i]))
            {
                BOOST_TEST_MESSAGE( "Infinite result "<<f.lhs[i]<<" from "<<
                                    f.lhs_orig[i]<<"-"<<f.rhs_scalar
                                    <<" at index "<<i<<" with type: "<<
                                    f.type_name);
            }
            else
            {
                BOOST_CHECK_EQUAL(f.lhs[i],
                                  value_type(f.lhs_orig[i]-f.rhs_scalar));
            }
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(sub_array_test,TestArrayT,all_array_types)
    {
        typedef typename TestArrayT::value_type value_type;
        fixture<TestArrayT> f((add_ranges<value_type>()));
    
        ip_type::sub(f.lhs,f.rhs);

        for(size_t i=0;i<f.lhs.size();++i) 
        {
            if(!(std::isfinite)(f.lhs[i]))
            {
                BOOST_TEST_MESSAGE( "Infinite result "<<f.lhs[i]<<" from "<<
                                    f.lhs_orig[i]<<"-"<<f.rhs[i]
                                    <<" at index "<<i<<" with type: "<<
                                    f.type_name);
            }
            else
            {
                BOOST_CHECK_EQUAL(f.lhs[i],
                                  value_type(f.lhs_orig[i]-f.rhs[i]));
            }
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_div_scalar,TestArrayT,all_array_types)
    {
        typedef typename TestArrayT::value_type value_type;
        fixture<TestArrayT> f((div_ranges<value_type>()));

        ip_type::div(f.lhs,f.rhs_scalar);
    
        for(size_t i=0;i<f.lhs.size();++i)
        {
            if(!(std::isfinite)(f.lhs[i]))
            {
                BOOST_TEST_MESSAGE( "Infinite result "<<f.lhs[i]<<" from "<<
                                    f.lhs_orig[i]<<"/"<<f.rhs_scalar
                                    <<" at index "<<i<<" with type: "<<
                                    f.type_name);
            }
            else
            {
                BOOST_CHECK_EQUAL(f.lhs[i],
                                  value_type(f.lhs_orig[i]/f.rhs_scalar));
            }
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_div_array,TestArrayT,all_array_types)
    {
        typedef typename TestArrayT::value_type value_type;
        fixture<TestArrayT> f((div_ranges<value_type>()));

        ip_type::div(f.lhs,f.rhs);

        for(size_t i=0;i<f.lhs.size();++i)
        {
            if(!(std::isfinite)(f.lhs[i]))
            {
                BOOST_TEST_MESSAGE( "Infinite result "<<f.lhs[i]<<" from "<<
                                    f.lhs_orig[i]<<"/"<<f.rhs[i]
                                    <<" at index "<<i<<" with type: "<<
                                    f.type_name);
            }
            else
            {
                BOOST_CHECK_EQUAL(f.lhs[i],
                                  value_type(f.lhs_orig[i]/f.rhs[i]));
            }
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_mult_scalar,TestArrayT,all_array_types)
    {
        typedef typename TestArrayT::value_type value_type;
        fixture<TestArrayT> f((mult_ranges<value_type>()));

        ip_type::mult(f.lhs,f.rhs_scalar);
        
        for(size_t i=0;i<f.lhs.size();++i)
        {
            if(!(std::isfinite)(f.lhs[i]))
            {
                BOOST_TEST_MESSAGE( "Infinite result "<<f.lhs[i]<<" from "<<
                                    f.lhs_orig[i]<<"*"<<f.rhs_scalar
                                    <<" at index "<<i<<" with type: "<<
                                    f.type_name);
            }
            else
            {
                BOOST_CHECK_EQUAL(f.lhs[i],
                                  value_type(f.lhs_orig[i]*f.rhs_scalar));
            }
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_mult_array,TestArrayT,all_array_types)
    {
        typedef typename TestArrayT::value_type value_type;
        fixture<TestArrayT> f((mult_ranges<value_type>()));

        ip_type::mult(f.lhs,f.rhs);

        for(size_t i=0;i<f.lhs.size();++i)
        {
            if(!(std::isfinite)(f.lhs[i]))
            {
                BOOST_TEST_MESSAGE( "Infinite result "<<f.lhs[i]<<" from "<<
                                    f.lhs_orig[i]<<"*"<<f.rhs[i]
                                    <<" at index "<<i<<" with type: "<<
                                    f.type_name);
            }
            else
            {
                BOOST_CHECK_EQUAL(f.lhs[i],
                                  value_type(f.lhs_orig[i]*f.rhs[i]));
            }
        }
    }

BOOST_AUTO_TEST_SUITE_END()


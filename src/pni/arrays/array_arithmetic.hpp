//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
// Created on: Dec 2, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/arrays/mdarray.hpp>
#include <pni/arrays/index_map/index_maps.hpp>
#include <pni/types/complex_utils.hpp>
#include <pni/arrays/scalar.hpp>
#include <pni/algorithms.hpp>
#include <pni/utilities/sfinae_macros.hpp>

namespace pni{

    //!
    //! \ingroup mdim_array_arithmetic_classes
    //! \brief struct identifying a type as an array type
    //! 
    //! If GeneralT is an array type value is true, otherwise it is false. 
    //! 
    template<typename GeneralT> struct is_array
    {
        //! 
        //! true if GeneralT is an arra type, false otherwise
        //!
        const static bool value = container_trait<GeneralT>::is_multidim;
    };

    template<typename GeneralT>
    using map_type = typename GeneralT::map_type;

    template<typename GeneralT>
    using ipa_type = typename GeneralT::inplace_arithmetic;


    //======================binary addition operator===========================
    //!
    //! \ingroup mdim_array_arithmetic_classes
    //! \brief binary addition operator 
    //! 
    //! Addition between two instaces of array like objects.
    //!  
    //! \code
    //! mdarray<...> a = ...;
    //! mdarray<...> b = ...;
    //! mdarray<...> c = ...;
    //! 
    //! c = a+b;
    //! \endcode
    //! 
    //! \tparam LHSArrayT left hand side array type
    //! \tparam RHSArrayT right hand side array type
    //! \param a left operand instance
    //! \param b right operand instance
    //! \return mdarray with the expression template
    //!
    template<
             typename LHSArrayT,
             typename RHSArrayT,
             typename = enable_if<and_t<is_array<LHSArrayT>,is_array<RHSArrayT>>>
            >
    mdarray<add_op<LHSArrayT,RHSArrayT>,map_type<LHSArrayT>,ipa_type<LHSArrayT>>
    operator+(const LHSArrayT &a,const RHSArrayT &b)
    {
        typedef add_op<LHSArrayT,RHSArrayT> operator_type;
        typedef mdarray<operator_type,map_type<LHSArrayT>,ipa_type<LHSArrayT>> return_type;

        return return_type(a.map(),operator_type(a,b));
    }

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup mdim_array_arithmetic_classes
    //! \brief binary addition operator
    //! 
    //! Addition operator between an array type object and a scalar.
    //! \code
    //! dynamic_array<float32> a = ....;
    //! dynamic_array<float32> c = ....;
    //! float32 d = ...;
    //! 
    //! c = a+d;
    //! \endcode
    //! 
    //! \tparam LHSArrayT left hand side array type
    //! \tparam ScalarT   scalar data type
    //! \param a reference to LHSArrayT operand
    //! \param b reference to RHSArrayT operand
    //! \return mdarray with the expression template
    //!
    template<
             typename LHSArrayT,
             typename ScalarT,
             typename = enable_if<and_t<
                        is_array<LHSArrayT>,not_t<is_array<T>> 
                        >>
            >
    mdarray<add_op<LHSArrayT,scalar<T>>,map_type<LHSArrayT>,ipa_type<LHSArrayT>>
    operator+(const LHSArrayT &a, const ScalarT& b)
    {
        typedef add_op<LHSArrayT,scalar<ScalarT>> operator_type;
        typedef mdarray<operator_type,map_type<LHSArrayT>,ipa_type<LHSArrayT>> return_type;

        return return_type(a.map(),operator_type(a,b));
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_arithmetic_classes
    //! \brief binary addition operator
    //!
    //! Addition operator between an array type object and a scalar.
    //! \code
    //! dynamic_array<float32> a = ....;
    //! dynamic_array<float32> c = ....;
    //! float32 d = ...;
    //! 
    //! c = d+a;
    //! \endcode
    //! 
    //! \tparam ScalarT data type of the scalar operand
    //! \tparam RHSArrayT data type of the right hand side operand
    //! \param a scalar value
    //! \param b instance of an RHSArrayT array
    //! \return mdarray instance with the expression template
    //!
    template<
             typename ScalarT,
             typename RHSArrayT,
             typename = enable_if<and_t<
                        not_t<is_array<ScalarT>>,is_array<RHSArrayT>
                        >>
            >
    mdarray<add_op<scalar<ScalarT>,RHSArrayT>,map_type<RHSArrayT>,ipa_type<RHSArrayT>>
    operator+(const ScalarT& a, const RHSArrayT &b)
    {
        typedef add_op<scalar<ScalarT>,RHSArrayT> operator_type;
        typedef mdarray<operator_type,map_type<RHSArrayT>,ipa_type<RHSArrayT>> result_type;
        typedef scalar<ScalarT> scalar_type;
        
        return result_type(b.map(),operator_type(scalar_type(a),b));
    }

    //======================binary subtraction operator========================
    //!
    //! \ingroup mdim_array_arithmetic_classes
    //! \brief binary subtraction operator 
    //!  
    //! Subtraction between two array like objects.
    //! 
    //! \code
    //! mdarray<...> a = ...;
    //! mdarray<...> b = ...;
    //! mdarray<...> c = ...;
    //! 
    //! c = a - b;
    //! \endcode
    //! 
    //! \tparam LHSArrayT left hand side operator type
    //! \tparam RHSArrayT right hand side operator type
    //! \param a left operand
    //! \param b right operand
    //! \return mdarray with the expression template
    //!
    template<
             typename LHSArrayT,
             typename RHSArrayT,
             typename = enable_if<and_t<is_array<LHSArrayT>,is_array<RHSArrayT>>>
            >
    mdarray<sub_op<LHSArrayT,RHSArrayT >,map_type<LHSArrayT>,ipa_type<LHSArrayT>>
    operator-(const LHSArrayT &a, const RHSArrayT &b)
    {
        typedef sub_op<LHSArrayT,RHSArrayT> operator_type;
        typedef mdarray<operator_type,map_type<LHSArrayT>,ipa_type<LHSArrayT>> result_type;

        return result_type(a.map(),operator_type(a,b));
    }

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup mdim_array_arithmetic_classes
    //! \brief binary subtraction operator
    //!
    //! Subtracting a scalar type from an array type.
    //! \code
    //! dynamic_array<float32> a = ...;
    //! dynamic_array<float32> c = ...;
    //! float32 b = ...;
    //! 
    //! c = a - b; 
    //! \endcode
    //!
    //! \tparam LHSArrayT left hand side array type
    //! \tparam ScalarT right handside scalar type
    //! \param a left operand 
    //! \param b right operand 
    //! \return mdarray instance with the expression template
    //! 
    template<
             typename LHSArrayT,
             typename ScalarT,
             typename = enable_if<and_t<
                      is_array<LHSArrayT>,not_t<is_array<ScalarT>>
                      >>
            >
    mdarray<sub_op<LHSArrayT,scalar<ScalarT> >,map_type<LHSArrayT>,ipa_type<LHSArrayT>>
    operator-(const LHSArrayT &a, const ScalarT& b)
    {
        typedef sub_op<LHSArrayT,scalar<ScalarT>> operator_type;
        typedef mdarray<operator_type,map_type<LHSArrayT>,ipa_type<LHSArrayT>> result_type;

        return result_type(a.map(),operator_type(a,b));
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup  mdim_array_arithmetic_classes
    //! \brief binary subtraction operator
    //!
    //! Subtracting an array from a scalar
    //! \code
    //! float32 b = ...;
    //! dynamic_array<float32> a = ...;
    //! dynamic_array<float32> c = ...;
    //!
    //! c = b - a;
    //! \endcode
    //! 
    //! \tparam ScalarT scalar right handside type
    //! \tparam RHSArrayT right hand side array type
    //! \param a scalar value
    //! \param b array like right handside
    //! \return instance of NumArray with an expression template
    //!
    template<
             typename ScalarT,
             typename RHSArrayT,
             typename = enable_if<and_t<
                        not_t<is_array<ScalarT>>,is_array<RHSArrayT> 
                        >>
            >
    mdarray<sub_op<scalar<ScalarT>,RHSArrayT>,map_type<RHSArrayT>,ipa_type<RHSArrayT>>
    operator-(const ScalarT &a, const RHSArrayT &b)
    {
        typedef sub_op<scalar<ScalarT>,RHSArrayT> operator_type;
        typedef mdarray<operator_type,map_type<RHSArrayT>,ipa_type<RHSArrayT>> result_type;
        
        return result_type(b.map(),operator_type(a,b));
    }
    
    //=================binary division operator================================
    //!
    //! \ingroup mdim_array_arithmetic_classes
    //! \brief binary division operator 
    //!
    //! Binary division between two array objects
    //! 
    //! \code
    //! mdarray<...> a = ...;
    //! mdarray<...> b = ...;
    //! mdarray<...> c = ...;
    //! c = a / b;
    //! \endcode
    //!
    //! \tparam LHSArrayT left hand side array type
    //! \tparam RHSArrayT right hand side array type
    //! \param a left operand
    //! \param b right operand
    //! \return mdarray with the expression template
    //!
    template<
             typename LHSArrayT,
             typename RHSArrayT,
             typename = enable_if<and_t<is_array<LHSArrayT>,is_array<RHSArrayT>>>
            >
    mdarray<div_op<LHSArrayT,RHSArrayT>,map_type<LHSArrayT>,ipa_type<LHSArrayT>>
    operator/(const LHSArrayT &a, const RHSArrayT &b)
    {
        typedef div_op<LHSArrayT,RHSArrayT> operator_type;
        typedef mdarray<operator_type,map_type<LHSArrayT>,ipa_type<LHSArrayT>> result_type;

        return result_type(a.map(),operator_type(a,b));
    }

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup mdim_array_arithmetic_classes 
    //! \brief binary division operator
    //!
    //! Division of an array type by a scalar type
    //! \code
    //! mdarray<...> a = ...;
    //! mdarray<...> c = ...;
    //! float64 b = ...;
    //!
    //! c = a/b;
    //! \endcode
    //!
    //! \tparam LHSArrayT left hand side array type
    //! \tparam ScalarT right hand side scalar type
    //! \param a left operand
    //! \param b right operand 
    //! \return mdarray with the expression template
    //!
    template<
             typename LHSArrayT,
             typename ScalarT,
             typename = enable_if<and_t<
                        is_array<LHSArrayT>,not_t<is_array<T>>
                        >>
            >
    mdarray<div_op<LHSArrayT,scalar<T>>,map_type<LHSArrayT>,ipa_type<LHSArrayT>>
    operator/(const LHSArrayT &a, const ScalarT &b)
    {
        typedef div_op<LHSArrayT,scalar<T>> operator_type;
        typedef mdarray<operator_type,map_type<LHSArrayT>,ipa_type<LHSArrayT>> result_type;

        return result_type(a.map(),operator_type(a,b));
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_arithmetic_classes 
    //! \brief binary division operator
    //! 
    //! Division of a scalar by an array type
    //! \code
    //! mdarray<...> a = ...;
    //! mdarray<...> c = ...;
    //! float64 b = ...;
    //! 
    //! c = b / a;
    //! \endcode
    //! 
    //! \tparam ScalarT left hand side scalar type
    //! \tparam RHSArrayT right hand side array type
    //! \param a scalar value
    //! \param b array instance
    //! \return mdarray with the expression template
    //!
    template<
             typename ScalarT,
             typename RHSArrayT,
             typename = enable_if<and_t<
                        not_t<is_array<T>>,is_array<RHSArrayT>
                        >>
            >
    mdarray<div_op<scalar<ScalarT>,RHSArrayT>,map_type<RHSArrayT>,ipa_type<RHSArrayT>>
    operator/(const ScalarT &a, const RHSArrayT &b)
    {
        typedef div_op<scalar<ScalarT>,RHSArrayT> operator_type;
        typedef mdarray<operator_type,map_type<RHSArrayT>,ipa_type<RHSArrayT>> result_type;

        return result_type(b.map(),operator_type(a,b));
    }
    
    //===================Multiplication operator================================
    //!
    //! \ingroup mdim_arithemtic_classes
    //! \brief binary multiplication operator
    //!
    //! Multiplication between two array type instances
    //! \code
    //! mdarray<...> a = ...;
    //! mdarray<...> b = ...;
    //! mdarray<...> c = ...;
    //! c = a * b;
    //! \endcode
    //!
    //! \tparam LHSArrayT left hand side array type
    //! \tparam RHSArrayT right hand side array type
    //! \param a left operand
    //! \param b right operand
    //! \return return mdarray instance with expression template
    //!
    template<
             typename LHSArrayT,
             typename RHSArrayT,
             typename = enable_if<and_t<is_array<LHSArrayT>,is_array<RHSArrayT> >>
            >
    mdarray<mult_op<LHSArrayT,RHSArrayT>,map_type<LHSArrayT>,ipa_type<LHSArrayT>>
    operator*(const LHSArrayT &a, const RHSArrayT &b)
    {
        typedef mult_op<LHSArrayT,RHSArrayT> operator_type;
        typedef mdarray<operator_type,map_type<LHSArrayT>,ipa_type<LHSArrayT>> result_type;

        return result_type(a.map(),operator_type(a,b));
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_arithmetic_classes
    //! \brief binary multiplication operator
    //!
    //! Multiplication between an array and a scalar
    //! \code
    //! dynamic_array<float32> a = ...;
    //! dynamic_array<float32> c = ...;
    //! float32 b = 200;
    //!
    //! c = a * b;
    //! \endcode
    //! 
    //! \tparam LHSArrayT left hand side array type
    //! \tparam ScalarT right hand scalar type
    //! \param a left operand 
    //! \param b right operand 
    //! \return mdarray with the expression template
    //!
    template<
             typename LHSArrayT,
             typename ScalarT,
             typename = enable_if<and_t<
                        is_array<LHSArrayT>,not_t<is_array<ScalarT>>
                        >>
            >
    mdarray<mult_op<LHSArrayT,scalar<ScalarT>>,map_type<LHSArrayT>,ipa_type<LHSArrayT>>
    operator*(const LHSArrayT &a, const ScalarT &b)
    {
        typedef mult_op<LHSArrayT,scalar<ScalarT>> operator_type;
        typedef mdarray<operator_type,map_type<LHSArrayT>,ipa_type<LHSArrayT>> result_type;
        
        return result_type(a.map(),operator_type(a,b));
    }

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup mdim_arithmetic_classes
    //! \brief binary multiplication operator
    //!
    //! Multiplication between an array and a scalar
    //! \code
    //! dynamic_array<float32> a = ...;
    //! dynamic_array<float32> c = ...;
    //! float32 b = 200;
    //!
    //! c = b * a;
    //! \endcode
    //!
    //! \tparam ScalarT left hand side scalar type
    //! \tparam RHSArrayT right hand side array type
    //! \param a left operand
    //! \param b right operand 
    //! \return mdarray with the expression template
    //!
    template< 
             typename ScalarT,
             typename RHSArrayT,
             typename = enable_if<and_t<
                        not_t<is_array<ScalarT>>,is_array<RHSArrayT>
                        >>
            >
    mdarray<mult_op<scalar<ScalarT>,RHSArrayT>,map_type<RHSArrayT>,ipa_type<RHSArrayT>>
    operator*(const ScalarT &a, const RHSArrayT &b)
    {
        typedef mult_op<scalar<ScalarT>,RHSArrayT> operator_type;
        typedef mdarray<operator_type,map_type<RHSArrayT>,ipa_type<RHSArrayT>> result_type;

        return result_type(b.map(),operator_type(a,b));
    }

//end of namespace
}

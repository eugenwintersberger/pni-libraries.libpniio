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
    //! If T is an array type value is true, otherwise it is false. 
    //! 
    template<typename T> struct is_array
    {
        //! 
        //! true if T is an arra type, false otherwise
        //!
        const static bool value = container_trait<T>::is_multidim;
    };

    template<typename T>
    using map_type = typename T::map_type;

    template<typename T>
    using ipa_type = typename T::inplace_arithmetic;


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
    //! \tparam LHS left hand side array type
    //! \tparam RHS right hand side array type
    //! \param a left operand instance
    //! \param b right operand instance
    //! \return mdarray with the expression template
    //!
    template<
             typename LHS,
             typename RHS,
             typename = enable_if<and_t<is_array<LHS>,is_array<RHS>>>
            >
    mdarray<add_op<LHS,RHS>,map_type<LHS>,ipa_type<LHS>>
    operator+(const LHS &a,const RHS &b)
    {
        typedef add_op<LHS,RHS> operator_type;
        typedef mdarray<operator_type,map_type<LHS>,ipa_type<LHS>> return_type;

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
    //! \tparam LHS left hand side array type
    //! \tparam T   scalar data type
    //! \param a reference to LHS operand
    //! \param b reference to RHS operand
    //! \return mdarray with the expression template
    //!
    template<
             typename LHS,
             typename T,
             typename = enable_if<and_t<
                        is_array<LHS>,not_t<is_array<T>> 
                        >>
            >
    mdarray<add_op<LHS,scalar<T>>,map_type<LHS>,ipa_type<LHS>>
    operator+(const LHS &a, const T& b)
    {
        typedef add_op<LHS,scalar<T>> operator_type;
        typedef mdarray<operator_type,map_type<LHS>,ipa_type<LHS>> return_type;

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
    //! \tparam T data type of the scalar operand
    //! \tparam RHS data type of the right hand side operand
    //! \param a scalar value
    //! \param b instance of an RHS array
    //! \return mdarray instance with the expression template
    //!
    template<
             typename T,
             typename RHS,
             typename = enable_if<and_t<
                        not_t<is_array<T>>,is_array<RHS>
                        >>
            >
    mdarray<add_op<scalar<T>,RHS>,map_type<RHS>,ipa_type<RHS>>
    operator+(const T& a, const RHS &b)
    {
        typedef add_op<scalar<T>,RHS> operator_type;
        typedef mdarray<operator_type,map_type<RHS>,ipa_type<RHS>> result_type;
        typedef scalar<T> scalar_type;
        
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
    //! \tparam LHS left hand side operator type
    //! \tparam RHS right hand side operator type
    //! \param a left operand
    //! \param b right operand
    //! \return mdarray with the expression template
    //!
    template<
             typename LHS,
             typename RHS,
             typename = enable_if<and_t<is_array<LHS>,is_array<RHS>>>
            >
    mdarray<sub_op<LHS,RHS >,map_type<LHS>,ipa_type<LHS>>
    operator-(const LHS &a, const RHS &b)
    {
        typedef sub_op<LHS,RHS> operator_type;
        typedef mdarray<operator_type,map_type<LHS>,ipa_type<LHS>> result_type;

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
    //! \tparam LHS left hand side array type
    //! \tparam T right handside scalar type
    //! \param a left operand 
    //! \param b right operand 
    //! \return mdarray instance with the expression template
    //! 
    template<
             typename LHS,
             typename T,
             typename = enable_if<and_t<
                      is_array<LHS>,not_t<is_array<T>>
                      >>
            >
    mdarray<sub_op<LHS,scalar<T> >,map_type<LHS>,ipa_type<LHS>>
    operator-(const LHS &a, const T& b)
    {
        typedef sub_op<LHS,scalar<T>> operator_type;
        typedef mdarray<operator_type,map_type<LHS>,ipa_type<LHS>> result_type;

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
    //! \tparam T scalar right handside type
    //! \tparam RHS right hand side array type
    //! \param a scalar value
    //! \param b array like right handside
    //! \return instance of NumArray with an expression template
    //!
    template<
             typename T,
             typename RHS,
             typename = enable_if<and_t<
                        not_t<is_array<T>>,is_array<RHS> 
                        >>
            >
    mdarray<sub_op<scalar<T>,RHS>,map_type<RHS>,ipa_type<RHS>>
    operator-(const T &a, const RHS &b)
    {
        typedef sub_op<scalar<T>,RHS> operator_type;
        typedef mdarray<operator_type,map_type<RHS>,ipa_type<RHS>> result_type;
        
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
    //! \tparam LHS left hand side array type
    //! \tparam RHS right hand side array type
    //! \param a left operand
    //! \param b right operand
    //! \return mdarray with the expression template
    //!
    template<
             typename LHS,
             typename RHS,
             typename = enable_if<and_t<is_array<LHS>,is_array<RHS>>>
            >
    mdarray<div_op<LHS,RHS>,map_type<LHS>,ipa_type<LHS>>
    operator/(const LHS &a, const RHS &b)
    {
        typedef div_op<LHS,RHS> operator_type;
        typedef mdarray<operator_type,map_type<LHS>,ipa_type<LHS>> result_type;

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
    //! \tparam LHS left hand side array type
    //! \tparam T right hand side scalar type
    //! \param a left operand
    //! \param b right operand 
    //! \return mdarray with the expression template
    //!
    template<
             typename LHS,
             typename T,
             typename = enable_if<and_t<
                        is_array<LHS>,not_t<is_array<T>>
                        >>
            >
    mdarray<div_op<LHS,scalar<T>>,map_type<LHS>,ipa_type<LHS>>
    operator/(const LHS &a, const T &b)
    {
        typedef div_op<LHS,scalar<T>> operator_type;
        typedef mdarray<operator_type,map_type<LHS>,ipa_type<LHS>> result_type;

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
    //! \tparam T left hand side scalar type
    //! \tparam RHS right hand side array type
    //! \param a scalar value
    //! \param b array instance
    //! \return mdarray with the expression template
    //!
    template<
             typename T,
             typename RHS,
             typename = enable_if<and_t<
                        not_t<is_array<T>>,is_array<RHS>
                        >>
            >
    mdarray<div_op<scalar<T>,RHS>,map_type<RHS>,ipa_type<RHS>>
    operator/(const T &a, const RHS &b)
    {
        typedef div_op<scalar<T>,RHS> operator_type;
        typedef mdarray<operator_type,map_type<RHS>,ipa_type<RHS>> result_type;

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
    //! \tparam LHS left hand side array type
    //! \tparam RHS right hand side array type
    //! \param a left operand
    //! \param b right operand
    //! \return return mdarray instance with expression template
    //!
    template<
             typename LHS,
             typename RHS,
             typename = enable_if<and_t<is_array<LHS>,is_array<RHS> >>
            >
    mdarray<mult_op<LHS,RHS>,map_type<LHS>,ipa_type<LHS>>
    operator*(const LHS &a, const RHS &b)
    {
        typedef mult_op<LHS,RHS> operator_type;
        typedef mdarray<operator_type,map_type<LHS>,ipa_type<LHS>> result_type;

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
    //! \tparam LHS left hand side array type
    //! \tparam T right hand scalar type
    //! \param a left operand 
    //! \param b right operand 
    //! \return mdarray with the expression template
    //!
    template<
             typename LHS,
             typename T,
             typename = enable_if<and_t<
                        is_array<LHS>,not_t<is_array<T>>
                        >>
            >
    mdarray<mult_op<LHS,scalar<T>>,map_type<LHS>,ipa_type<LHS>>
    operator*(const LHS &a, const T &b)
    {
        typedef mult_op<LHS,scalar<T>> operator_type;
        typedef mdarray<operator_type,map_type<LHS>,ipa_type<LHS>> result_type;
        
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
    //! \tparam T left hand side scalar type
    //! \tparam RHS right hand side array type
    //! \param a left operand
    //! \param b right operand 
    //! \return mdarray with the expression template
    //!
    template< 
             typename T,
             typename RHS,
             typename = enable_if<and_t<
                        not_t<is_array<T>>,is_array<RHS>
                        >>
            >
    mdarray<mult_op<scalar<T>,RHS>,map_type<RHS>,ipa_type<RHS>>
    operator*(const T &a, const RHS &b)
    {
        typedef mult_op<scalar<T>,RHS> operator_type;
        typedef mdarray<operator_type,map_type<RHS>,ipa_type<RHS>> result_type;

        return result_type(b.map(),operator_type(a,b));
    }

//end of namespace
}

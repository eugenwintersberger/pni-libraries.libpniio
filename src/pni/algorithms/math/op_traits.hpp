//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 25,2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/arrays/scalar.hpp>

namespace pni{
    
    //! 
    //! \ingroup mdim_array_internal_classes
    //! \brief operator reference trait
    //! 
    //! This trait determines which reference type to use for the operands
    //! of an expression template. While for standard containers an ordinary 
    //! expression can be used, scalars are stored by value as they are often 
    //! passed as temporaries. 
    //!
    //! \tparam OperatorT operator type
    //!
    template<typename OperatorT> 
    struct op_trait
    {
        //! reference type for the operand
        typedef OperatorT const& ref_type; 
    };

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup mdim_array_internal_classes
    //! \brief  operator trait for scalars
    //! 
    //! This is a specialization of the operator trait for a scalar value. 
    //! For scalars the value instead of a reference will be stored. 
    //! 
    //! \tparam T data type of the scalar
    //!
    template<typename T> 
    struct op_trait<scalar<T> >
    {
        //! reference type for a scalar operand
        typedef scalar<T> ref_type;
    };
   
    //-------------------------------------------------------------------------
    //! 
    //! \ingroup mdim_array_internal_classes
    //! \brief array trait for expression templates 
    //! 
    //! This trait determines the common index map and inplace arithmetic 
    //! implementation types to use for an expression template. 
    //! This is the default template where we assume that both operands are 
    //! array types.
    //! 
    //! \tparam Operand1T LHS operand type
    //! \tparam Operand2T RHS operand type
    //! 
    template<
             typename Operand1T,
             typename Operand2T
            > 
    struct array_trait
    {
        //! index map type
        typedef typename Operand1T::map_type map_type;
        //! inplace arithmetic type
        typedef typename Operand1T::inplace_arithmetic inplace_arithmetic;
    };

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup mdim_array_internal_classes
    //! \brief array trait for expression templates 
    //! 
    //! This trait determines the common index map and inplace arithmetic 
    //! implementation types to use for an expression template. 
    //! This specialization assumes that the LHS is an array while the RHS 
    //! of the expression is a scalar.
    //! 
    //! \tparam Operand1T LHS operand type
    //! \tparam ScalarOperandT   data type of the RHS scalar operand
    //! 
    template<
             typename Operand1T,
             typename ScalarOperandT
            >
    struct array_trait<Operand1T,scalar<ScalarOperandT>>
    {
        //! index map type
        typedef typename Operand1T::map_type map_type;
        //! inplace arithmetic type
        typedef typename Operand1T::inplace_arithmetic inplace_arithmetic;
    };

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup mdim_array_internal_classes
    //! \brief array trait for expression templates 
    //! 
    //! This trait determines the common index map and inplace arithmetic 
    //! implementation types to use for an expression template. 
    //! This specialization assumes that the LHS is a scalar while the RHS 
    //! of the expression is an array.
    //! 
    //! \tparam ScalarOperandT data type of the LHS scalar operand
    //! \tparam Operand1T RHS type
    //! 
    template<
             typename ScalarOperandT,
             typename Operand1T
            > 
    struct array_trait<scalar<ScalarOperandT>,Operand1T>
    {
        //! index map type
        typedef typename Operand1T::map_type map_type;
        //! inplace arithmetic type
        typedef typename Operand1T::inplace_arithmetic inplace_arithmetic;
    };

//end of namespace
}

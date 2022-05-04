//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jan 12, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include<iostream>
#include<memory>

#include <pni/types/types.hpp>
#include <pni/types/convert.hpp>
#include <pni/types/type_conversion.hpp>
#include <pni/types/traits.hpp>
#include <pni/type_erasures/value_holder.hpp>

namespace pni{


    //------------------------------------------------------------------------
    //! 
    //! \ingroup type_erasure_classes_internal
    //! \brief converter class
    //! 
    //! This template provides a static conversion function from the source 
    //! type SourceT to the target type TargetT. The convertible template parameters 
    //! makes a decission about whether or not the conversion can be done. 
    //! The default value of the convertible parameter is false, causing 
    //! the static convert() member function to throw a type_error 
    //! exception. We need this special system here as in the generic code 
    //! we may need to compile TargetT and SourceT pairs where the plain convert()
    //! function template would throw a static assertion.
    //! 
    //! \tparam TargetT target type
    //! \tparam SourceT source type
    //! \tparam convertible if true the conversion is possible, otherwise not
    //! 
    template<
             typename TargetT,
             typename SourceT,
             bool     convertible=false
            > 
    struct value_converter
    {
        //! target type alias
        typedef TargetT target_type;
        //! source type alias
        typedef SourceT source_type;
        
        //! 
        //! \brief static conversion function
        //! 
        //! This implementation does nothing else than throwing a type 
        //! error exception. 
        //! 
        //! \throws type_error types cannot be converted 
        //! \return nothing 
        //! 
        static target_type convert(const source_type &)
        {
            throw type_error(EXCEPTION_RECORD,"Conversion not possible!");
            return target_type();
        }
    };



    //------------------------------------------------------------------------
    //! 
    //! \ingroup type_erasure_classes_internal
    //! \brief converter class specialization
    //! 
    //! Specialization of the value_converter template for convertible 
    //! types. 
    //! 
    //! \tparam TargetT target type
    //! \tparam SourceT source type
    //! 
    template<
             typename TargetT,
             typename SourceT
            >
    struct value_converter<TargetT,SourceT,true>
    {
        //! target type alias 
        typedef TargetT target_type;
        //! source type alias 
        typedef SourceT source_type;

        //!
        //! \brief conversion function
        //!
        //! Converts an instance of a source type to an instance of 
        //! the target type. 
        //! 
        //! \throws range_error if v does not fit in the range spanned by 
        //!                     TargetT
        //! \throws type_error in case of any other type related error 
        //! \param v reference to the source value
        //! \return instance of TargetT with the converted value
        //! 
        static target_type convert(const source_type &v)
        {
            return pni::convert<target_type>(v);
        }
    };

    //------------------------------------------------------------------------
    template<
             typename TargetT,
             typename SourceT
            >
    using strategy = value_converter<TargetT,SourceT,convertible<SourceT,TargetT>::value>;

    //------------------------------------------------------------------------
    //!
    //! \brief alias for std::reference_wrapper
    //!
    //! A simple alias for the std::reference_wrapper template to reduce
    //! typing work. 
    //!
    //! \tparam T type of the reference
    //!
    template<typename T> using ref_type = std::reference_wrapper<T>;

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief get pointer to value holder
    //! 
    //! Retrieve the pointer to a concrete value holder instance. 
    //! The value class only stores a pointer to value_holder_interface. 
    //! However, to retrieve typed data the pointer to the particular
    //! holder instance is required. This template function performs the 
    //! cast based on the original data type T (which can be obtained 
    //! from the type ID of the value. 
    //! 
    //! \tparam DataT erased data type
    //! \tparam PointerT interface pointer type
    //! \param ptr reference to the interface pointer
    //! \return pointer of value_holder<T> type
    //! 
    template<
             typename DataT,
             typename PointerT
            >
    value_holder<DataT> *get_holder_ptr(PointerT &ptr)
    {
        typedef value_holder<DataT> holder_type;
                
        return dynamic_cast<holder_type*>(ptr.get());
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief get value from holder
    //! 
    //! Get the value stored in a particular holder as an instance of a 
    //! user requested type T. 
    //!
    //! \throws range_error if the value stored in the holder does not fit 
    //!                     in the range of the requested target type T 
    //! \throws type_error in case of any other type related error 
    //! 
    //! \tparam TargetT target type
    //! \tparam SourceT source type (the original type)
    //! \tparam PointerT holder pointer type
    //! 
    //! \param holder_ptr pointer to the original holder 
    //! \return value as an instance of type T 
    //!
    template<
             typename TargetT,
             typename SourceT,
             typename PointerT
            > 
    TargetT get_value(PointerT holder_ptr)  
    {
        typedef strategy<TargetT,SourceT>   strategy_type;

        return strategy_type::convert(holder_ptr->as()); 
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief set value to holder
    //! 
    //! Take a value of type  T and store it to a value_holder of type S. 
    //! If S and T are not equal a type conversion is performed. 
    //! 
    //! \throws range_error if v does not fit in the range provided by S 
    //! \throws type_error in case of any other type related error
    //! 
    //! \tparam TargetT target type (the holder type)
    //! \tparam SourceT source type (provided by the user)
    //! \tparam PointerT holder pointer type 
    //! 
    //! \param holder_ptr pointer to the typed value_holder
    //! \param v reference to the value of type T 
    //! 
    template<
             typename TargetT,
             typename SourceT,
             typename PointerT
            >
    void set_value(PointerT holder_ptr,const SourceT &v)
    {
        typedef strategy<TargetT,SourceT> strategy_type;

        holder_ptr->as() = strategy_type::convert(v);
    }



//end of namespace
}

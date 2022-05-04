//
// Declaration of template class TypeInfo
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
//  Created on: Dec 10, 2011
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
//
#pragma once

#include <pni/types/type_id_map.hpp>
#include <boost/static_assert.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <pni/error/exceptions.hpp>
#include <pni/error/exception_utils.hpp>
#include <pni/types/type_info.hpp>
#include <pni/types/unchecked_convertible.hpp>
#include <pni/types/checked_convertible.hpp>
#include <pni/types/convertible.hpp>
#include <pni/types/type_conversion.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>
#include <pni/types/bool.hpp>



namespace pni{

    //!
    //! \ingroup type_classes_internal
    //! \brief simple numeric converter
    //!
    //! Implements conversion between simple scalar numeric types.
    //!
    //! \tparam TargetT target type
    //! \tparam SourceT source type
    //!
    template<
             typename TargetT,
             typename SourceT
            >
    struct converter
    {
        //!
        //! \brief perform conversion
        //!
        //! \param value reference of instance of source type
        //! \return instance of target type with the converted value
        //!
        static TargetT convert(const SourceT &value)
        {
            return boost::numeric_cast<TargetT>(value);
        }
    };

    //!
    //! \ingroup type_classes_internal
    //! \brief simple numeric converter
    //!
    //! This is a specialization of the converter template for the case
    //! that the target and source type are equal.
    //!
    //! \tparam TargetT target and source type
    //!
    template<typename TargetT>
    struct converter<TargetT,TargetT>
    {
        //!
        //! \brief perform conversion
        //!
        //! As the target and the source type are equal this function
        //! does nothing. It just passes the user provided value through.
        //!
        //! \param value original value
        //! \return the same as the original value
        //!
        static TargetT convert(const TargetT &value)
        {
            return value;
        }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief simple to complex conversion
    //!
    //! Implements conversion from a simple scalar type to a complex type.
    //!
    //! \tparam BaseT target base type
    //! \tparam SourceT simple source type
    //!
    template<
             typename BaseT,
             typename SourceT
            >
    struct converter<std::complex<BaseT>,SourceT>
    {
        //!
        //! \brief perform conversion
        //!
        //! The scalar type becomes the real part of the complex
        //! value.
        //!
        //! \param value the original simple scalar type
        //! \return complex type  with value as its real part
        //!
        static std::complex<BaseT> convert(const SourceT &value)
        {
            BaseT real = boost::numeric_cast<BaseT>(value);

            return std::complex<BaseT>(real,0);
        }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief complex to complex conversion
    //!
    //! Implements complex to complex conversion.
    //!
    //! \tparam TargetBaseT target base type
    //! \tparam SourceBaseT source base type
    //!
    template<
             typename TargetBaseT,
             typename SourceBaseT
            >
    struct converter<std::complex<TargetBaseT>,std::complex<SourceBaseT>>
    {
        //!
        //! \brief perform conversion
        //!
        //! Convert two complex numbers of different base type.
        //!
        //! \param value instance of the source complex type
        //! \return new instance of target type
        //!
        static std::complex<TargetBaseT> convert(const std::complex<SourceBaseT> &value)
        {
            TargetBaseT real = boost::numeric_cast<TargetBaseT>(value.real());
            TargetBaseT imag = boost::numeric_cast<TargetBaseT>(value.imag());

            return std::complex<TargetBaseT>(real,imag);
        }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief simple unchecked strategy
    //!
    //! This strategy implements a simple unchecked type conversion.
    //!
    //! \tparam TargetT target type
    //! \tparam SourceT source type
    //! \tparam unchecked_convertible a flag if true use this strategy
    //!
    template<
             typename TargetT,
             typename SourceT,
             bool unchecked_convertible=true
            >
    struct conversion_strategy
    {
        //!
        //! \brief perform conversion
        //!
        //! For types which can be converted unchecked we just do a cast.
        //!
        //! \param value reference to the original value
        //! \return converted value
        static TargetT convert(const SourceT &value)
        {
#ifdef _MSC_VER
#pragma warning(disable: 4244)
#endif
            return TargetT(value);
#ifdef _MSC_VER
#pragma warning(default: 4244)
#endif
        }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief simple unchecked strategy
    //!
    //! This strategy implements a simple unchecked type conversion
    //! between bool types
    //!
    //!
    template<
            >
    struct conversion_strategy<hdf5::datatype::EBool,bool_t,true>
    {
        //!
        //! \brief perform conversion
        //!
        //! For types which can be converted unchecked we just do a cast.
        //!
        //! \param value reference to the original value
        //! \return converted value
        static hdf5::datatype::EBool convert(const pni::bool_t &value)
        {
          if(value)
            return hdf5::datatype::EBool::True;
          else
            return hdf5::datatype::EBool::False;
        }
    };


    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief checked conversion strategy
    //!
    //! This strategy uses the numeric_cast function to implement the
    //! conversion.
    //!
    //! \tparam TargetT target type
    //! \tparam SourceT source type
    //!
    template<
             typename TargetT,
             typename SourceT
            >
    struct conversion_strategy<TargetT,SourceT,false>
    {
        //!
        //! \brief perform conversion
        //!
        //! Use one of the converters to perform the conversion between
        //! the source and the target type.
        //!
        //! \param value original value of type SourceT
        //! \return converted value of type TargetT
        //!
        static TargetT convert(const SourceT &value)
        {
            try
            {
                return converter<TargetT,SourceT>::convert(value);
            }
            catch(const boost::numeric::positive_overflow &)
            {
                throw range_error(EXCEPTION_RECORD,
                        "Source value exceeded range of target type!");
            }
            catch(const boost::numeric::negative_overflow &)
            {
                throw range_error(EXCEPTION_RECORD,
                        "Source value exceeded range of target type!");
            }
            catch(...)
            {
                throw type_error(EXCEPTION_RECORD,
                        "Unknown error during type conversion!");
            }
        }

    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief type conversion function template
    //!
    //! This function template finally performs the type conversion. Several
    //! static asserts are performed which ensure the two cases of conversions
    //! will not even compile: conversion from a floating point number of an
    //! integer value and conversion from a complex value to a non-complex
    //! type.
    //!
    //! \throws range_error if u does not fit in the range covered by T
    //! \throws type_error in case of all other errors
    //!
    //! \tparam TargetT target type
    //! \tparam S source type
    //!
    //! \param source value of type S
    //! \return value of u converted to TargetT
    //!
    template<
             typename TargetT,
             typename SourceT
            >
    TargetT convert(const SourceT &source)
    {
        static_assert(convertible<SourceT,TargetT>::value,
                      "Types are in no way convertible!");

        typedef conversion_strategy<TargetT,SourceT,unchecked_convertible<SourceT,TargetT>::value> strategy;
        return strategy::convert(source);

    }

//end of namespace
}

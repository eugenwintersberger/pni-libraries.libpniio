/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Definition of a datatype factory.
 *
 * Created on: Feb 9, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __H5DATATYPEFACTORY_HPP__
#define __H5DATATYPEFACTORY_HPP__

#include <pni/utils/Types.hpp>

extern "C"{
#include <hdf5.h>
}

#include "H5Datatype.hpp"
#include "H5Exceptions.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{
namespace h5{

    /*! 
    \ingroup nxh5_classes
    \brief data type factory

    This class acts as a factory for H5Datatype objects. For complex
    data a compound data type is used. The naming convention of the
    structure memebers follows those of h5py (in order to produce files
    which can be opened easily from Python). 
    */
    class H5DatatypeFactory
    {
        private:
            //from this class we would need a singleton - should be available only
            //once at runtime - most probably as a global object.

            //! \brief structure for 32Bit complex number
            typedef struct {
                Float32 r;   //!< real part
                Float32 i;   //!< imaginary part

            } __struct_complex_32;  //!< C structure for a 32Bit complex type

            //! \brief structure for 64Bit complex numbers
            typedef struct {
                Float64 r;   //!< real part
                Float64 i;   //!< imaginary part
            } __struct_complex_64;  //!< C structure for a 64Bit complex type

            //! \brief structure for 128Bit complex numbers
            typedef struct {
                Float128 r;  //!< real part
                Float128 i;  //!< imaginary part
            } __struct_complex_128; //!< C structure for a 128Bit complex type

            //==========private static types provided by the factory===========
            H5Datatype _bool_t;   //!< boolean HDF5 type
            H5Datatype _uint8_t;  //!< 8Bit unsigned integer HDF5 type
            H5Datatype _int8_t;   //!< 8Bit signed integer HDF5 type
            H5Datatype _uint16_t; //!< 16Bit unsigned integer HDF5 type
            H5Datatype _int16_t;  //!< 16Bit signed integer HDF5 type
            H5Datatype _uint32_t; //!< 32Bit unsigned integer HDF5 type
            H5Datatype _int32_t;  //!< 32Bit signed integer HDF5 type
            H5Datatype _uint64_t; //!< 64Bit unsigned integer HDF5 type
            H5Datatype _int64_t;  //!< 64Bit signed integer HDF5 type

            H5Datatype _float32_t; //!< 32Bit IEEE floating point type
            H5Datatype _float64_t; //!< 64Bit IEEE floating point type
            H5Datatype _float128_t; //!< 128Bit IEEE floating point type
            
            H5Datatype _cmplx32_t; //!< 32Bit IEEE complex type
            H5Datatype _cmplx64_t; //!< 64Bit IEEE complex type
            H5Datatype _cmplx128_t; //!< 128Bit IEEE complex type

            H5Datatype _string_t; //!< string data type
            H5Datatype _binary_t; //!< binary data type
        public:
            //=======================constructors and destructor===============
            //! default constructor
            H5DatatypeFactory();

            //-----------------------------------------------------------------
            //! destructor
            ~H5DatatypeFactory();

            //==================public class methods===========================
            /*! \brief create from type

            This static template method can be used to create a H5Datatype
            object from a particular type T. T must be a type defined in
            pni/utils/Types.hpp. 

            \code
            H5Datatype t = H5DatatypeFactor::create_type<Float32>();
            \endcode

            \throws H5DataTypeError if type creation was unsuccessful 
            \return instance of H5Datatype 
            */
            template<typename T> static H5Datatype create_type();

            //-----------------------------------------------------------------
            /*! \brief create from type id

            Static template method to create an instance of H5Datatype from a
            PNI type id. 

            \code
            H5Datatype t = H5DatatypeFactor::create_type<TypeID::UINT8>();
            \endcode

            \throws H5DataTypeError if type creation was unsuccessful
            \return instance of H5Datatype
            */
            template<TypeID ID> static H5Datatype create_type();

            //-----------------------------------------------------------------
            /*! \brief get data type 

            Returns a reference to an already existing data type.
            \tparam T data type to select
            \return reference to the corresponding HDF5 data type
            */
            template<typename T> const H5Datatype &get_type() const;

            //-----------------------------------------------------------------
            /*!
            \brief get data type 

            Return a reference to a predefined HDF5 data type. 
            \tparam ID type id of the required type
            \return reference to the corresponding HDF5 data type
            */
            template<TypeID ID> const H5Datatype &get_type() const;
    };

    static H5DatatypeFactory H5TFactory;


//end of namespace
}
}
}


#endif

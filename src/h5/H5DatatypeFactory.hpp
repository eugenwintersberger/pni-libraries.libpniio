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

            /*! \ingroup nxh5_classes

            \brief data type factory

            This class acts as a factory for H5Datatype objects.
            */
            class H5DatatypeFactory{
                private:
                    //from this class we would need a singleton - should be available only
                    //once at runtime - most probably as a global object.
                    typedef struct {
                        Float32 r;
                        Float32 i;

                    } __struct_complex_32;  //!< C structure for a 32Bit complex type
                    typedef struct {
                        Float64 r;
                        Float64 i;
                    } __struct_complex_64;  //!< C structure for a 64Bit complex type

                    typedef struct {
                        Float128 r;
                        Float128 i;
                    } __struct_complex_128; //!< C structure for a 128Bit complex type
                public:
                    /*! \brief create from type

                    This static template method can be used to create a
                    H5Datatype object from a particular type T. T must be a type
                    defined in pni/utils/Types.hpp. 

                    \code
                    H5Datatype t = H5DatatypeFactor::create_type<Float32>();
                    \endcode

                    \throws H5DataTypeError if type creation was unsuccessful 
                    \return instance of H5Datatype 
                    */
                    template<typename T> static H5Datatype create_type();

                    //---------------------------------------------------------
                    /*! \brief create from type id

                    Static template method to create an instance of H5Datatype 
                    from a PNI type id. 

                    \code
                    H5Datatype t = H5DatatypeFactor::create_type<TypeID::UINT8>();
                    \endcode

                    \throws H5DataTypeError if type creation was unsuccessful
                    \return instance of H5Datatype
                    */
                    template<TypeID ID> static H5Datatype create_type();
            };


        }
    }
}


#endif

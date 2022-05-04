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
// Created on: Jan 11, 2013
// Authors:
//         Eugen Wintersberger <eugen.wintersberger@desy.de>
//         Jan Kotanski <jan.kotanski@desy.de>
//
#pragma once

#include <pni/arrays.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>

namespace pni{

    //!
    //! \ingroup type_erasure_classes
    //! \brief create an array 
    //! 
    //! Create an array of a particular shape and type. The type is determined 
    //! at compile time via a template parameters. The underlying mdarray 
    //! specialization is dynamic_array. 
    //!
    //! \tparam ElementT data type of the elements
    //! \tparam ShapeT shape type
    //! \param shape number of elements along each dimension
    //! \return instance of array
    //! 
    template<
             typename ElementT,
             typename ShapeT
            >
    array make_array(const ShapeT &shape)
    {
        typedef dynamic_array<ElementT> array_type;

        return array(array_type::create(shape));
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes
    //! \brief create array
    //! 
    //! Create an array of a particular type and shape. The type is determined 
    //! by an argument and thus can be set at runtime.
    //!
    //! \throws type_error if the passed data type cannot be handled
    //! \tparam ContainerT container type for the shape
    //! \param tid type id for the array
    //! \param shape number of elements along each dimension
    //! \return instance of array
    //! 
    template<typename ContainerT> 
    array make_array(type_id_t tid,const ContainerT &shape)
    {
        if(tid == type_id_t::UInt8)
            return make_array<uint8>(shape);
        else if(tid == type_id_t::Int8)
            return make_array<int8>(shape);
        else if(tid == type_id_t::UInt16)
            return make_array<uint16>(shape);
        else if(tid == type_id_t::Int16)
            return make_array<int16>(shape);
        else if(tid == type_id_t::UInt32)
            return make_array<uint32>(shape);
        else if(tid == type_id_t::Int32)
            return make_array<int32>(shape);
        else if(tid == type_id_t::UInt64)
            return make_array<uint64>(shape);
        else if(tid == type_id_t::Int64)
            return make_array<int64>(shape);
        else if(tid == type_id_t::Float32)
            return make_array<float32>(shape);
        else if(tid == type_id_t::Float64)
            return make_array<float64>(shape);
        else if(tid == type_id_t::Float128)
            return make_array<float128>(shape);
        else if(tid == type_id_t::Complex32)
            return make_array<complex32>(shape);
        else if(tid == type_id_t::Complex64)
            return make_array<complex64>(shape);
        else if(tid == type_id_t::Complex128)
            return make_array<complex128>(shape);
        else if(tid == type_id_t::Bool)
            return make_array<bool_t>(shape);
        else if(tid == type_id_t::EBool)
            return make_array<hdf5::datatype::EBool>(shape);
        else if(tid == type_id_t::Binary)
            return make_array<binary>(shape);
        else if(tid == type_id_t::String)
            return make_array<string>(shape);
        else 
            throw type_error(EXCEPTION_RECORD,"Type ID cannot be processed!");

        
    }
//end of namespace
}

//
// Declaration of the NXfield template
//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Jan 16, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/type_erasures.hpp>
#include <pni/core/error.hpp>


namespace pni{
namespace io{
namespace nx{

    using namespace pni::core;
    using pni::core::array;
    using pni::core::string;

    //!
    //! \brief write array to object
    //! 
    //! This is a utility function writing an object of type array to an 
    //! IO-type. The function throws whatever exception is thrown by the 
    //! write() method of the passed instance of IOT. In addtion TypeError 
    //! is thrown if array is of an unsupported type.
    //! 
    //! \throws type_error if the type of the array is not supported
    //! \tparam IOT I/O-type 
    //! \param obj reference to instance of IOT
    //! \param a array to write 
    //!
    template<typename IOT> void write_array(const IOT &obj,const array& a)
    {
        type_id_t tid = a.type_id();

        if(tid == type_id_t::UINT8)         obj.write(tid,a.data());
        else if(tid == type_id_t::INT8)     obj.write(tid,a.data());
        else if(tid == type_id_t::UINT16)   obj.write(tid,a.data());
        else if(tid == type_id_t::INT16)    obj.write(tid,a.data());
        else if(tid == type_id_t::UINT32)   obj.write(tid,a.data());
        else if(tid == type_id_t::INT32)    obj.write(tid,a.data());
        else if(tid == type_id_t::UINT64)   obj.write(tid,a.data());
        else if(tid == type_id_t::INT64)    obj.write(tid,a.data());
        else if(tid == type_id_t::FLOAT32)  obj.write(tid,a.data());
        else if(tid == type_id_t::FLOAT64)  obj.write(tid,a.data());
        else if(tid == type_id_t::FLOAT128) obj.write(tid,a.data());
        else if(tid == type_id_t::STRING)   obj.write(tid,a.data());

        else if(tid == type_id_t::COMPLEX32)  obj.write(tid,a.data());
        else if(tid == type_id_t::COMPLEX64)  obj.write(tid,a.data());
        else if(tid == type_id_t::COMPLEX128) obj.write(tid,a.data());
        else
            throw type_error(EXCEPTION_RECORD,
                    "Unsupported data type!");
    }

    //-------------------------------------------------------------------------
    //!
    //! \brief read array 
    //!
    //! Read data form a readable object and store it to an array instance. 
    //! It throws whatever exception the read method of obj is throwing. In 
    //! addtion if the data type of the array is not supported a TypeError 
    //! exception is thrown.
    //!
    //! \throws type_error in case of an unsupported datat type
    //! \tparam IOT IO type
    //! \param obj instance of IOT from which to read data
    //! \param a instance of array where to store the data
    //!
    template<typename IOT> void read_array(const IOT &obj,array &a)
    {
        type_id_t tid = a.type_id();

        if(tid == type_id_t::UINT8)       obj.read(tid,a.data());
        else if(tid == type_id_t::INT8)   obj.read(tid,a.data());
        else if(tid == type_id_t::UINT16) obj.read(tid,a.data());
        else if(tid == type_id_t::INT16)  obj.read(tid,a.data());
        else if(tid == type_id_t::UINT32) obj.read(tid,a.data());
        else if(tid == type_id_t::INT32)  obj.read(tid,a.data());
        else if(tid == type_id_t::UINT64) obj.read(tid,a.data());
        else if(tid == type_id_t::INT64)  obj.read(tid,a.data());

        else if(tid == type_id_t::FLOAT32)  obj.read(tid,a.data());
        else if(tid == type_id_t::FLOAT64)  obj.read(tid,a.data());
        else if(tid == type_id_t::FLOAT128) obj.read(tid,a.data());
        else if(tid == type_id_t::STRING)   obj.read(tid,a.data());

        else if(tid == type_id_t::COMPLEX32)  obj.read(tid,a.data());
        else if(tid == type_id_t::COMPLEX64)  obj.read(tid,a.data());
        else if(tid == type_id_t::COMPLEX128) obj.read(tid,a.data());
        else
            throw type_error(EXCEPTION_RECORD,
                    "Unsupported data type!");
    }


//end of namespace
}
}
}

/*
 * Declaration of the NXfield template
 *
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: Jan 16, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
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

    /*!
    \brief write array to object

    This is a utility function writing an object of type array to an IO-type. 
    The function throws whatever exception is thrown by the write() method of
    the passed instance of IOT. In addtion TypeError is thrown if array is of an
    unsupported type.
    \throws type_error if the type of the array is not supported
    \tparam IOT I/O-type 
    \param obj reference to instance of IOT
    \param a array to write 
    */
    template<typename IOT> void write_array(const IOT &obj,const array& a)
    {
        if(a.type_id() == type_id_t::UINT8) 
            obj.write((uint8*)a.data());
        else if(a.type_id() == type_id_t::INT8)
            obj.write((int8*)a.data());

        if(a.type_id() == type_id_t::UINT16) 
            obj.write((uint16*)a.data());
        else if(a.type_id() == type_id_t::INT16)
            obj.write((int16*)a.data());

        if(a.type_id() == type_id_t::UINT32) 
            obj.write((uint32*)a.data());
        else if(a.type_id() == type_id_t::INT32)
            obj.write((int32*)a.data());

        if(a.type_id() == type_id_t::UINT64) 
            obj.write((uint64*)a.data());
        else if(a.type_id() == type_id_t::INT64)
            obj.write((int64*)a.data());

        else if(a.type_id() == type_id_t::FLOAT32)
            obj.write((float32*)a.data());
        else if(a.type_id() == type_id_t::FLOAT64)
            obj.write((float64*)a.data());
        else if(a.type_id() == type_id_t::FLOAT128)
            obj.write((float128*)a.data());

        else if(a.type_id() == type_id_t::STRING)
            obj.write((string*)a.data());

        else if(a.type_id() == type_id_t::COMPLEX32)
            obj.write((complex32*)a.data());
        else if(a.type_id() == type_id_t::COMPLEX64)
            obj.write((complex64*)a.data());
        else if(a.type_id() == type_id_t::COMPLEX128)
            obj.write((complex128*)a.data());
        else
            throw type_error(EXCEPTION_RECORD,
                    "Unsupported data type!");
    }

    //-------------------------------------------------------------------------
    /*!
    \brief read array 

    Read data form a readable object and store it to an array instance. 
    It throws whatever exception the read method of obj is throwing. In addtion
    if the data type of the array is not supported a TypeError exception is
    thrown.
    \throws type_error in case of an unsupported datat type
    \tparam IOT IO type
    \param obj instance of IOT from which to read data
    \param a instance of array where to store the data
    */
    template<typename IOT> void read_array(const IOT &obj,array &a)
    {
        if(a.type_id() == type_id_t::UINT8) 
            obj.read((uint8*)(a.data()));
        else if(a.type_id() == type_id_t::INT8)
            obj.read((int8*)a.data());

        if(a.type_id() == type_id_t::UINT16) 
            obj.read((uint16*)a.data());
        else if(a.type_id() == type_id_t::INT16)
            obj.read((int16*)a.data());

        if(a.type_id() == type_id_t::UINT32) 
            obj.read((uint32*)a.data());
        else if(a.type_id() == type_id_t::INT32)
            obj.read((int32*)a.data());

        if(a.type_id() == type_id_t::UINT64) 
            obj.read((uint64*)a.data());
        else if(a.type_id() == type_id_t::INT64)
            obj.read((int64*)a.data());

        else if(a.type_id() == type_id_t::FLOAT32)
            obj.read((float32*)a.data());
        else if(a.type_id() == type_id_t::FLOAT64)
            obj.read((float64*)a.data());
        else if(a.type_id() == type_id_t::FLOAT128)
            obj.read((float128*)a.data());

        else if(a.type_id() == type_id_t::STRING)
            obj.read((string*)a.data());

        else if(a.type_id() == type_id_t::COMPLEX32)
            obj.read((complex32*)a.data());
        else if(a.type_id() == type_id_t::COMPLEX64)
            obj.read((complex64*)a.data());
        else if(a.type_id() == type_id_t::COMPLEX128)
            obj.read((complex128*)a.data());
        else
            throw type_error(EXCEPTION_RECORD,
                    "Unsupported data type!");
    }


//end of namespace
}
}
}

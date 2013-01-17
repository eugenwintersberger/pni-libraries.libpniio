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

#include <pni/core/Types.hpp>
#include <pni/core/array.hpp>
#include <pni/core/Exceptions.hpp>

using namespace pni::core;

namespace pni{
namespace io{
namespace nx{

    /*!
    \brief write array to object

    This is a utility function writing an object of type array to an IO-type. 
    The function throws whatever exception is thrown by the write() method of
    the passed instance of IOT. In addtion TypeError is thrown if array is of an
    unsupported type.
    \throws TypeError if the type of the array is not supported
    \tparam IOT I/O-type 
    \param obj reference to instance of IOT
    \param a array to write 
    */
    template<typename IOT> void write_array(const IOT &obj,const array& a)
    {
        if(a.type_id() == TypeID::UINT8) 
            obj.write((UInt8*)a.ptr());
        else if(a.type_id() == TypeID::INT8)
            obj.write((Int8*)a.ptr());

        if(a.type_id() == TypeID::UINT16) 
            obj.write((UInt16*)a.ptr());
        else if(a.type_id() == TypeID::INT16)
            obj.write((Int16*)a.ptr());

        if(a.type_id() == TypeID::UINT32) 
            obj.write((UInt32*)a.ptr());
        else if(a.type_id() == TypeID::INT32)
            obj.write((Int32*)a.ptr());

        if(a.type_id() == TypeID::UINT64) 
            obj.write((UInt64*)a.ptr());
        else if(a.type_id() == TypeID::INT64)
            obj.write((Int64*)a.ptr());

        else if(a.type_id() == TypeID::FLOAT32)
            obj.write((Float32*)a.ptr());
        else if(a.type_id() == TypeID::FLOAT64)
            obj.write((Float64*)a.ptr());
        else if(a.type_id() == TypeID::FLOAT128)
            obj.write((Float128*)a.ptr());

        else if(a.type_id() == TypeID::STRING)
            obj.write((String*)a.ptr());

        else if(a.type_id() == TypeID::COMPLEX32)
            obj.write((Complex32*)a.ptr());
        else if(a.type_id() == TypeID::COMPLEX64)
            obj.write((Complex64*)a.ptr());
        else if(a.type_id() == TypeID::COMPLEX128)
            obj.write((Complex128*)a.ptr());
        else
            throw TypeError(EXCEPTION_RECORD,
                    "Unsupported data type!");
    }

    //-------------------------------------------------------------------------
    /*!
    \brief read array 

    Read data form a readable object and store it to an array instance. 
    It throws whatever exception the read method of obj is throwing. In addtion
    if the data type of the array is not supported a TypeError exception is
    thrown.
    \throws TypeError in case of an unsupported datat type
    \tparam IOT IO type
    \param obj instance of IOT from which to read data
    \param a instance of array where to store the data
    */
    template<typename IOT> void read_array(const IOT &obj,array &a)
    {
        if(a.type_id() == TypeID::UINT8) 
            obj.read((UInt8*)(const_cast<void*>(a.ptr())));
        else if(a.type_id() == TypeID::INT8)
            obj.read((Int8*)const_cast<void*>(a.ptr()));

        if(a.type_id() == TypeID::UINT16) 
            obj.read((UInt16*)const_cast<void*>(a.ptr()));
        else if(a.type_id() == TypeID::INT16)
            obj.read((Int16*)const_cast<void*>(a.ptr()));

        if(a.type_id() == TypeID::UINT32) 
            obj.read((UInt32*)const_cast<void*>(a.ptr()));
        else if(a.type_id() == TypeID::INT32)
            obj.read((Int32*)const_cast<void*>(a.ptr()));

        if(a.type_id() == TypeID::UINT64) 
            obj.read((UInt64*)const_cast<void*>(a.ptr()));
        else if(a.type_id() == TypeID::INT64)
            obj.read((Int64*)const_cast<void*>(a.ptr()));

        else if(a.type_id() == TypeID::FLOAT32)
            obj.read((Float32*)const_cast<void*>(a.ptr()));
        else if(a.type_id() == TypeID::FLOAT64)
            obj.read((Float64*)const_cast<void*>(a.ptr()));
        else if(a.type_id() == TypeID::FLOAT128)
            obj.read((Float128*)const_cast<void*>(a.ptr()));

        else if(a.type_id() == TypeID::STRING)
            obj.read((String*)const_cast<void*>(a.ptr()));

        else if(a.type_id() == TypeID::COMPLEX32)
            obj.read((Complex32*)const_cast<void*>(a.ptr()));
        else if(a.type_id() == TypeID::COMPLEX64)
            obj.read((Complex64*)const_cast<void*>(a.ptr()));
        else if(a.type_id() == TypeID::COMPLEX128)
            obj.read((Complex128*)const_cast<void*>(a.ptr()));
        else
            throw TypeError(EXCEPTION_RECORD,
                    "Unsupported data type!");
    }


//end of namespace
}
}
}

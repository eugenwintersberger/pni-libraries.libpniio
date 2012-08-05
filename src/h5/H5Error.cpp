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
 * H5Error.cpp
 *
 *  Created on: Aug 2, 2011
 *      Author: Eugen Wintersberger
 */

#include <pni/utils/Exceptions.hpp>
extern "C"{
#include <hdf5.h>
}

#include "H5ErrorStack.hpp"


namespace pni{
namespace nx{
namespace h5{

    //--------------------------------------------------------------------------
    H5Error::H5Error() { }

    //--------------------------------------------------------------------------
    H5Error::H5Error(const H5Error &e)
    {
        _class_id = e._class_id;
        _class_name = e._class_name;
        _major_number = e._major_number;
        _minor_number = e._minor_number;
        _file_name = e._file_name;
        _func_name = e._func_name;
        _description = e._description;
        _minor_message = e._minor_message;
        _major_message = e._major_message;
    }

    //--------------------------------------------------------------------------
    H5Error::~H5Error(){ }

    //--------------------------------------------------------------------------
    H5Error &H5Error::operator=(const H5Error &e)
    {
        if(this != &e)
        {
            _class_id = e._class_id;
            _class_name = e._class_name;
            _major_number = e._major_number;
            _minor_number = e._minor_number;
            _file_name = e._file_name;
            _func_name = e._func_name;
            _description = e._description;
            _minor_message = e._minor_message;
            _major_message = e._major_message;
        }

        return *this;
    }

    //--------------------------------------------------------------------------
    hid_t H5Error::class_id() const
    {
        return _class_id;
    }

    //--------------------------------------------------------------------------
    void H5Error::class_id(hid_t id)
    {
        char *ptr = nullptr;
        size_t buffer_size = 0;

        //set the class id
        _class_id = id;
        //determine the class name from the class id

        //allocate memory
        buffer_size = H5Eget_class_name(id,NULL,1)+1;
        ptr = new char[buffer_size];
        if(!ptr)
            throw MemoryAllocationError(EXCEPTION_RECORD, 
                                        "Memory allocation failed!");

        //obtain error class
        H5Eget_class_name(id,ptr,buffer_size);
        _class_name = String(ptr);
        //free memory
        if(ptr) delete [] ptr;
    }

    //--------------------------------------------------------------------------
    hid_t H5Error::major_number() const
    {
        return _major_number;
    }

    //--------------------------------------------------------------------------
    void H5Error::major_number(hid_t v)
    {
        char *ptr = nullptr;
        size_t buffer_size = 0;
        H5E_type_t msg_type;

        //set the major number
        _major_number = v;

        //get the major message from the error stack
        buffer_size = H5Eget_msg(v,&msg_type,NULL,1);
        if(buffer_size > 0){
            //memory allocation
            ptr = new char[buffer_size+1];
            if(!ptr)
                throw MemoryAllocationError(EXCEPTION_RECORD, 
                                            "Memory allocation failed!");

            //read error message
            H5Eget_msg(v,&msg_type,ptr,buffer_size+1);
            _major_message = String(ptr);

            //free memory
            if(ptr) delete [] ptr;
            ptr = nullptr;
        }
    }

    //-------------------------------------------------------------------------
    hid_t H5Error::minor_number() const
    {
        return _minor_number;
    }

    //--------------------------------------------------------------------------
    void H5Error::minor_number(hid_t v)
    {
        char *ptr = nullptr;
        size_t buffer_size = 0;
        H5E_type_t msg_type;

        //set the minor number
        _minor_number = v;

        //get the minor message
        buffer_size = H5Eget_msg(v,&msg_type,NULL,1);
        if(buffer_size > 0){
            //memory allocation
            ptr = new char[buffer_size+1];
            if(!ptr)
                throw MemoryAllocationError(EXCEPTION_RECORD, 
                                            "Memory allocation failed!");

            //read minor number
            H5Eget_msg(v,&msg_type,ptr,buffer_size+1);
            _minor_message = String(ptr);

            //free memory	
            if(ptr) delete [] ptr;	
            ptr = nullptr;
        }
    }

    //--------------------------------------------------------------------------
    String H5Error::file_name() const
    {
        return _file_name;
    }

    //--------------------------------------------------------------------------
    void H5Error::file_name(const String &n)
    {
        _file_name = n;
    }

    //--------------------------------------------------------------------------
    String H5Error::func_name() const
    {
        return _func_name;
    }

    //--------------------------------------------------------------------------
    void H5Error::func_name(const String &n)
    {
        _func_name = n;
    }

    //--------------------------------------------------------------------------
    String H5Error::description() const
    {
        return _description;
    }

    //--------------------------------------------------------------------------
    void H5Error::description(const String &n)
    {
        _description = n;
    }


    //--------------------------------------------------------------------------
    String H5Error::major_message() const
    {
        return _major_message;
    }


    //--------------------------------------------------------------------------
    String H5Error::minor_message() const
    {
        return _minor_message;
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const H5Error &e)
    {
        o<<e._class_name<<" - Error in: "<<e._func_name<<" ("<<e._file_name
         <<")"<<std::endl;
        o<<e._description<<": "<<e._major_message<<" -- "<<e._minor_message
         <<std::endl;

        return o;
    }

//end of namespace
}
}
}

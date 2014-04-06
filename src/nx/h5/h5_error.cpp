/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * H5Error.cpp
 *
 *  Created on: Aug 2, 2011
 *      Author: Eugen Wintersberger
 */

#include <pni/core/error.hpp>
extern "C"{
#include <hdf5.h>
}

#include <pni/io/nx/h5/h5_error.hpp>


namespace pni{
namespace io{
namespace nx{
namespace h5{

    //--------------------------------------------------------------------------
    h5_error::h5_error():
        _class_id(0),
        _class_name(),
        _major_number(0),
        _minor_number(0),
        _file_name(),
        _func_name(),
        _description(),
        _minor_message(),
        _major_message()
    { }

    //--------------------------------------------------------------------------
    h5_error::h5_error(const h5_error &e):
        _class_id(e._class_id),
        _class_name(e._class_name),
        _major_number(e._major_number),
        _minor_number(e._minor_number),
        _file_name(e._file_name),
        _func_name(e._func_name),
        _description(e._description),
        _minor_message(e._minor_message),
        _major_message(e._major_message)
    { }

    //--------------------------------------------------------------------------
    h5_error::~h5_error(){ }

    //--------------------------------------------------------------------------
    h5_error &h5_error::operator=(const h5_error &e)
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
    hid_t h5_error::class_id() const
    {
        return _class_id;
    }

    //--------------------------------------------------------------------------
    void h5_error::class_id(hid_t id)
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
            throw memory_allocation_error(EXCEPTION_RECORD, 
                                        "Memory allocation failed!");

        //obtain error class
        H5Eget_class_name(id,ptr,buffer_size);
        _class_name = string(ptr);
        //free memory
        if(ptr) delete [] ptr;
    }

    //--------------------------------------------------------------------------
    hid_t h5_error::major_number() const
    {
        return _major_number;
    }

    //--------------------------------------------------------------------------
    void h5_error::major_number(hid_t v)
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
                throw memory_allocation_error(EXCEPTION_RECORD, 
                                            "Memory allocation failed!");

            //read error message
            H5Eget_msg(v,&msg_type,ptr,buffer_size+1);
            _major_message = string(ptr);

            //free memory
            if(ptr) delete [] ptr;
            ptr = nullptr;
        }
    }

    //-------------------------------------------------------------------------
    hid_t h5_error::minor_number() const
    {
        return _minor_number;
    }

    //--------------------------------------------------------------------------
    void h5_error::minor_number(hid_t v)
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
                throw memory_allocation_error(EXCEPTION_RECORD, 
                                            "Memory allocation failed!");

            //read minor number
            H5Eget_msg(v,&msg_type,ptr,buffer_size+1);
            _minor_message = string(ptr);

            //free memory	
            if(ptr) delete [] ptr;	
            ptr = nullptr;
        }
    }

    //--------------------------------------------------------------------------
    string h5_error::file_name() const
    {
        return _file_name;
    }

    //--------------------------------------------------------------------------
    void h5_error::file_name(const string &n)
    {
        _file_name = n;
    }

    //--------------------------------------------------------------------------
    string h5_error::func_name() const
    {
        return _func_name;
    }

    //--------------------------------------------------------------------------
    void h5_error::func_name(const string &n)
    {
        _func_name = n;
    }

    //--------------------------------------------------------------------------
    string h5_error::description() const
    {
        return _description;
    }

    //--------------------------------------------------------------------------
    void h5_error::description(const string &n)
    {
        _description = n;
    }


    //--------------------------------------------------------------------------
    string h5_error::major_message() const
    {
        return _major_message;
    }


    //--------------------------------------------------------------------------
    string h5_error::minor_message() const
    {
        return _minor_message;
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const h5_error &e)
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
}

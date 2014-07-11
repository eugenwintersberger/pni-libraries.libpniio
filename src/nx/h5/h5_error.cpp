//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Aug 2, 2011
//      Author: Eugen Wintersberger
//

#include <pni/core/error.hpp>
extern "C"{
#include <hdf5.h>
}

#include <pni/io/exceptions.hpp>
#include <pni/io/nx/h5/h5_error.hpp>


namespace pni{
namespace io{
namespace nx{
namespace h5{
    using pni::io::io_error;

    //--------------------------------------------------------------------------
    h5_error::h5_error() noexcept:
        _class_name(),
        _file_name(),
        _func_name(),
        _description(),
        _minor_message(),
        _major_message()
    { }

    //--------------------------------------------------------------------------
    h5_error::h5_error(const h5_error &e):
        _class_name(e._class_name),
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
            _class_name = e._class_name;
            _file_name = e._file_name;
            _func_name = e._func_name;
            _description = e._description;
            _minor_message = e._minor_message;
            _major_message = e._major_message;
        }

        return *this;
    }

    //------------------------------------------------------------------------
    string h5_error::get_message(hid_t mid,H5E_type_t *mtype)
    {
        ssize_t buffer_size = 0;

        //get the major message from the error stack
        buffer_size = H5Eget_msg(mid,mtype,NULL,1);
        if(buffer_size<0)
            return "Error: could not retrieve HDF5 error message";

        string buffer(buffer_size,' ');

        char*ptr = const_cast<char*>(buffer.data());
        if(H5Eget_msg(mid,mtype,ptr,buffer_size+1)<0)
            return "Error: could not retrieve HDF5 error message";
    
        return buffer;
    }


    //--------------------------------------------------------------------------
    void h5_error::class_name(hid_t id)
    {
        ssize_t buffer_size = 0;

        //allocate memory
        buffer_size = H5Eget_class_name(id,NULL,1);
        if(buffer_size<0)
        {
            _class_name = "UNKNOWN";  
            return;
        }

        _class_name = string(buffer_size,' ');

        //obtain error class
        if(H5Eget_class_name(id,const_cast<char*>(_class_name.data()),buffer_size+1)<0)
        {
            _class_name = "UNKOWN";
            return;
        }
    }

    //--------------------------------------------------------------------------
    string h5_error::class_name() const
    {
        return _class_name;
    }

    //--------------------------------------------------------------------------
    void h5_error::major_message(hid_t mid)
    {
        H5E_type_t msg_type;

        //set the major number
        _major_message = get_message(mid,&msg_type);
        if(msg_type != H5E_MAJOR)
            _major_message = "Error - Not Major message!: "+_major_message;

    }

    //--------------------------------------------------------------------------
    void h5_error::minor_message(hid_t mid)
    {
        H5E_type_t msg_type;

        //set the minor number
        _minor_message = get_message(mid,&msg_type);
        
        if(msg_type != H5E_MINOR)
            _minor_message = "Error - Not Minor message!:"+_minor_message;
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
        o<<e.class_name()<<" - Error in: "<<e.func_name()<<" ("<<e.file_name()
         <<")"<<std::endl;
        o<<e.description()<<": "<<e.major_message()<<" -- "
         <<e.minor_message()<<std::endl;

        return o;
    }

//end of namespace
}
}
}
}

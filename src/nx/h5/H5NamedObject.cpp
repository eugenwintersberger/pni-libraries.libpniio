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
//
// Created on: Jan 10, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nx/h5/H5NamedObject.hpp>
#include <pni/io/exceptions.hpp>

#include "hdf5_utilities.hpp"

namespace pni{
namespace io{
namespace nx{
namespace h5{

    using pni::io::io_error;
    using pni::io::invalid_object_error;

    //=============implementation of constructors and destructors==============
    H5NamedObject::H5NamedObject():H5Object(){ }

    //-------------------------------------------------------------------------
    H5NamedObject::H5NamedObject(const H5NamedObject &o):H5Object(o){ }

    //-------------------------------------------------------------------------
    H5NamedObject::H5NamedObject(const H5Object &o):H5Object(o){ }

    //-------------------------------------------------------------------------
    H5NamedObject::H5NamedObject(H5NamedObject &&o) :H5Object(std::move(o)){ }

    //-------------------------------------------------------------------------
    H5NamedObject::H5NamedObject(H5Object &&o) :H5Object(std::move(o)){ }

    //-------------------------------------------------------------------------
    H5NamedObject::H5NamedObject(const hid_t &id):H5Object(id){ }

    //-------------------------------------------------------------------------
    H5NamedObject::~H5NamedObject(){ }

    //===========implementation of assignment operators========================
    //implementation of copy assignment operator
    H5NamedObject &H5NamedObject::operator=(const H5NamedObject &o)
    {
        if(this == &o) return *this;

        H5Object::operator=(o);

        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of conversion copy assignment
    H5NamedObject &H5NamedObject::operator=(const H5Object &o)
    {
        if(this == &o) return *this;

        H5Object::operator=(o);
        
        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of move assignment
    H5NamedObject &H5NamedObject::operator=(H5NamedObject &&o)
    {
        if(this == &o) return *this;

        H5Object::operator=(std::move(o));

        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of move conversion assignment
    H5NamedObject &H5NamedObject::operator=(H5Object &&o)
    {
        if(this == &o) return *this;

        H5Object::operator=(std::move(o));

        return *this;
    }

    //================implementation of name operations========================
    string H5NamedObject::name() const
    {
        if(!is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Try to obtain the name of an invalid object!");

        string p(H5NamedObject::path());

        //if the path is empty return an empty string
        if(p.empty()) return p;

        if((p.size() == 1) && (p[0] == '/')) return p;

        //need to extract the the name information from the path
        size_t lpos = p.find_last_of("/");
        string name = p;
        if(lpos != p.npos) name = string(p,lpos+1,p.size()-lpos+1);

        return name;
    }
    
    //-------------------------------------------------------------------------
    string H5NamedObject::base() const
    {
        string p(H5NamedObject::path());

        if(p.empty()) return p;

        //if the string is of size 1 and has
        //only one / return this
        string base;
        if((p.size() == 1) && (p[0] == '/')) return string("/");

        size_t lpos = p.find_last_of("/");
        if(lpos != p.npos)
        {
            //if the / has been found in the 
            //first position we can simply return this
            if(lpos == 0) base = string("/");
            else
            {
                //in all other cases a bit more work 
                //is necessary
                base = string(p,0,lpos+1);

                //remove a trailing /
                if(base[base.size()-1] == '/'){
                    base = string(base,0,base.size()-1);
                }
            }
        }

        return base;
    }

    //-------------------------------------------------------------------------
    string H5NamedObject::path() const
    {
        return get_object_path(id());
    }

    //-------------------------------------------------------------------------
    string H5NamedObject::filename() const
    {
        return get_filename(id());
    }

    //-------------------------------------------------------------------------
    H5Object H5NamedObject::parent() const
    {
        hid_t fid = H5Iget_file_id(id());
        if(fid<0)
            throw object_error(EXCEPTION_RECORD,
                    "Error obtaining file ID in order to retrieve the parent"
                    " object - HDF5 error:\n\n"+get_h5_error_string());

        hid_t pid = H5Oopen(fid,get_parent_path(id()).c_str(),H5P_DEFAULT);
        if(pid<0)
        {
            H5Fclose(fid); //close file ID in case of an error
            throw object_error(EXCEPTION_RECORD,
                    "Error obtaining parent ID of object ["+name()+"] "
                    "- HDF5 error:\n\n"+get_h5_error_string());
        }

        H5Fclose(fid); //close file ID in case of success
        //H5Group g(gid);

        return H5Object(H5NamedObject(pid));

    }


//end of namespace
}
}
}
}

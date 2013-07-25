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
 *
 * Implementation of a general named HDF5 object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "H5NamedObject.hpp"
#include <pni/core/dbuffer.hpp>

namespace pni{
namespace io{
namespace nx{
namespace h5{

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
        dbuffer<char> buffer;

        if(is_valid()){
            //if the object has already been created return this value
            hsize_t bsize;
            bsize = H5Iget_name(id(),NULL,1)+1;
            buffer.allocate(bsize);

            H5Iget_name(id(),const_cast<char*>(buffer.ptr()),bsize);
            string name(buffer.ptr());
            return name;
        }

        return string("");
    }

    //-------------------------------------------------------------------------
    pni::io::nx::nxlink_type H5NamedObject::link_type() const
    {
        H5L_info_t info;


        if(H5Lget_info(parent().id(),name().c_str(),&info,H5P_DEFAULT)<0)
        {
            //throw an exception here
        }

        if(info.type == H5L_TYPE_HARD)
            return pni::io::nx::nxlink_type::HARD;
        else if(info.type == H5L_TYPE_SOFT)
            return pni::io::nx::nxlink_type::SOFT;
        else if(info.type == H5L_TYPE_EXTERNAL)
            return pni::io::nx::nxlink_type::EXTERNAL;
        else 
            throw pni::core::type_error(EXCEPTION_RECORD,
                    "Link is of unknown type!");
        
    }

    H5Object H5NamedObject::parent() const
    {

        return H5Object();
    }


//end of namespace
}
}
}
}

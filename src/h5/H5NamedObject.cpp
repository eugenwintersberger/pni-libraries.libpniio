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
#include "H5Exceptions.hpp"
#include <pni/core/DBuffer.hpp>
//#include "H5Group.hpp"

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
    String H5NamedObject::name() const
    {
        String p(H5NamedObject::path());

        //if the path is empty return an empty string
        if(p.empty()) return p;

        if((p.size() == 1) && (p[0] == '/')) return p;

        //need to extract the the name information from the path
        size_t lpos = p.find_last_of("/");
        String name = p;
        if(lpos != p.npos) name = String(p,lpos+1,p.size()-lpos+1);

        return name;
    }
    
    //-------------------------------------------------------------------------
    String H5NamedObject::base() const
    {
        String p(H5NamedObject::path());

        if(p.empty()) return p;

        //if the string is of size 1 and has
        //only one / return this
        String base;
        if((p.size() == 1) && (p[0] == '/')) return String("/");

        size_t lpos = p.find_last_of("/");
        if(lpos != p.npos)
        {
            //if the / has been found in the 
            //first position we can simply return this
            if(lpos == 0) base = String("/");
            else
            {
                //in all other cases a bit more work 
                //is necessary
                base = String(p,0,lpos+1);

                //remove a trailing /
                if(base[base.size()-1] == '/'){
                    base = String(base,0,base.size()-1);
                }
            }
        }

        return base;
    }

    //-------------------------------------------------------------------------
    String H5NamedObject::path() const
    {
        DBuffer<char> buffer;

        if(is_valid()){
            //if the object has already been created return this value
            hsize_t bsize;
            bsize = H5Iget_name(id(),NULL,1)+1;
            buffer.allocate(bsize);

            H5Iget_name(id(),const_cast<char*>(buffer.ptr()),bsize);
            String name(buffer.ptr());
            return name;
        }

        return String("");
    }


//end of namespace
}
}
}
}

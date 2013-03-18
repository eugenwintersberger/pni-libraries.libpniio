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
 * Implementation of an HDF5 attribute object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#include "H5AttributeObject.hpp"



namespace pni{
namespace io{
namespace nx{
namespace h5{
    //=======implementation of constructors and destructors====================
    //implementation of the default constructor
    H5AttributeObject::H5AttributeObject():H5NamedObject(){ }

    //-------------------------------------------------------------------------
    //implementation of the copy constructor
    H5AttributeObject::H5AttributeObject(const H5AttributeObject &o):
        H5NamedObject(o)
    { }

    //-------------------------------------------------------------------------
    //implementation of the conversion constructor
    H5AttributeObject::H5AttributeObject(const H5Object &o):
        H5NamedObject(o)
    { }

    //-------------------------------------------------------------------------
    //implementation of the move constructor
    H5AttributeObject::H5AttributeObject(H5AttributeObject &&o):
        H5NamedObject(std::move(o))
    { }

    //-------------------------------------------------------------------------
    //implementation of the move conversion constructor
    H5AttributeObject::H5AttributeObject(H5Object &&o):
        H5NamedObject(std::move(o))
    { }

    //-------------------------------------------------------------------------
    //implementation of a constructor using an object ID to 
    //create the object.
    H5AttributeObject::H5AttributeObject(const hid_t&oid):
        H5NamedObject(oid)
    { }

    //-------------------------------------------------------------------------
    //implementation of the destructor
    H5AttributeObject::~H5AttributeObject() { }

    //=======implementation of assignment operators============================
    //implementation of copy assignment operator
    H5AttributeObject &
        H5AttributeObject::operator=(const H5AttributeObject &o)
    {
        if(this == &o) return *this;

        H5NamedObject::operator=(o);

        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of copy conversion operator
    H5AttributeObject &H5AttributeObject::operator=(const H5Object &o)
    {
        if(this == &o) return *this;
        
        H5NamedObject::operator=(o);

        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of move assignment operator
    H5AttributeObject &
        H5AttributeObject::operator=(H5AttributeObject &&o)
    {
        if(this == &o) return *this;     
        
        H5NamedObject::operator=(std::move(o));

        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of move conversion operator
    H5AttributeObject &H5AttributeObject::operator=(H5Object &&o)
    {
        if(this == &o) return *this;

        H5NamedObject::operator=(std::move(o));
        return *this;
    }

    //=======implementation of attribute management methods====================
    //implementation of the attribute open method
    H5Attribute H5AttributeObject::attr(const string &n) const 
    {
        if(H5Aexists(id(),n.c_str())<=0)
        {
            std::stringstream ss;
            ss<<"Object ["<<name()<<"] has no attribute ["<<n<<"]!";
            throw pni::io::nx::nxattribute_error(EXCEPTION_RECORD,ss.str()+
                    get_h5_error_string());
        }

        hid_t aid = H5Aopen(id(),n.c_str(),H5P_DEFAULT);
        if(aid < 0)
        {
            std::stringstream ss;
            ss<<"Error opening attribute ["<<n<<"] from object [";
            ss<<name()<<"]!";
            throw pni::io::nx::nxattribute_error(EXCEPTION_RECORD,ss.str()+
                    get_h5_error_string());
        }

        H5Attribute a(aid);
        return a;
    }

    //-------------------------------------------------------------------------
    //implementation of opening an attribute by index
    H5Attribute H5AttributeObject::attr(size_t i) const
    {
        if(i>=nattr())
        {
            std::stringstream ss;
            ss<<"Index ("<<i<<") exceeds number of attributes ("<<nattr();
            ss<<" on object ["<<name()<<"]!";
            throw index_error(EXCEPTION_RECORD,ss.str());
        }

        hid_t aid = H5Aopen_by_idx(id(),".",H5_INDEX_NAME,
                H5_ITER_INC,i,H5P_DEFAULT,H5P_DEFAULT);
        if(aid<0)
        {
            std::stringstream ss;
            ss<<"Error opening attribute with index ("<<i<<") on object ";
            ss<<"["<<name()<<"]!";
            throw pni::io::nx::nxattribute_error(EXCEPTION_RECORD,ss.str()+
                    get_h5_error_string());
        }

        H5Attribute a(aid);
        return a;
    }

    //-------------------------------------------------------------------------
    //get number of attributes
    size_t H5AttributeObject::nattr() const
    {
        H5O_info_t info;
        H5Oget_info(id(),&info);

        return info.num_attrs;
    }

    //-------------------------------------------------------------------------
    bool H5AttributeObject::has_attr(const string &n) const
    {
        htri_t ret = H5Aexists(id(),n.c_str());
        if(ret >0 ) return true;
        else if(ret == 0) return false;
        else
        {
            std::stringstream ss;
            ss<<"Error checking for existence of attribute ";
            ss<<"["<<n<<"] on object ["<<name()<<"]!";
            throw pni::io::nx::nxattribute_error(EXCEPTION_RECORD,ss.str()+
                    get_h5_error_string());
        }
    }

    //-------------------------------------------------------------------------
    void H5AttributeObject::del_attr(const string &n) const
    {
        herr_t err = H5Adelete(id(),n.c_str());
        if(err < 0)
        {
            std::stringstream ss;
            ss<<"Error deleteing attribute ["<<n<<"] from ";
            ss<<"object ["<<name()<<"]!";
            throw pni::io::nx::nxattribute_error(EXCEPTION_RECORD,ss.str()+
                    get_h5_error_string());
        }
    }

        
//end of namespace
}
}
}
}

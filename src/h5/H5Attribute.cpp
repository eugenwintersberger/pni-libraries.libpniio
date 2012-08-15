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
 *
 * Implementation of an HDF5 attribute object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "H5Attribute.hpp"
#include "H5Exceptions.hpp"


namespace pni{
namespace nx{
namespace h5{
    //===============private methods===========================================
    void H5Attribute::__set_space_type()
    {
        hid_t dspace_id = 0;
        hid_t dtype_id = 0;

        if(is_valid())
        {
            //obtain the IDs of the dataspace and the datatype used 
            //to create the attribute.
            dspace_id = H5Aget_space(id());
            dtype_id  = H5Aget_type(id());

            //we can use this Ids to create new H5Objects from which 
            //the datatype and the dataspace can be constructed.
            _dspace = H5Dataspace(dspace_id);
            _dtype  = H5Datatype(dtype_id);
        }
        else
        {
            _dspace = H5Dataspace();
            _dtype = H5Datatype();
        }
    }

    //===========constructors and destructors==================================
    //! implementation of the default constructor
    H5Attribute::H5Attribute():H5NamedObject(){ }

    //-------------------------------------------------------------------------
    //implementation of the copy constructor
    H5Attribute::H5Attribute(const H5Attribute &o):H5NamedObject(o)
    {
        //once the ID is set we can obtain the datatype and 
        //the data space
        __set_space_type();
    }

    //--------------------------------------------------------------------------
    //implementation of the move constructor
    H5Attribute::H5Attribute(H5Attribute &&o):
        H5NamedObject(std::move(o))
    {
        _dspace = std::move(o._dspace);
        _dtype  = std::move(o._dtype);
    }
    //-------------------------------------------------------------------------
    H5Attribute::H5Attribute(const hid_t &id):
        H5NamedObject(id)
    {
        __set_space_type();
    }

    //-----------------------------------------------------------------
    //implementation of the destructor
    H5Attribute::~H5Attribute()
    {
        _dspace.close();
        _dtype.close();

        if(is_valid()) H5Aclose(id());
        H5Object::id(0);
    }

    //===============implementation of assignment operators====================
    // implementation of copy assignment operator
    H5Attribute &H5Attribute::operator=(const H5Attribute &a)
    {
       if(this != &a)
       {
           H5NamedObject::operator=(a);
           __set_space_type();
       }
       return *this;
    }
    
    //-------------------------------------------------------------------------
    //implementation of move assignment operator
    H5Attribute &H5Attribute::operator=(H5Attribute &&o)
    {
        if(this != &o)
        {
            H5NamedObject::operator=(std::move(o));
            _dspace = std::move(o._dspace);
            _dtype  = std::move(o._dtype);
        }
        return *this;
    }

    //=========implementation of inquery methods===============================
    TypeID H5Attribute::type_id() const
    {
        return _dtype.type_id();
    }

    //-------------------------------------------------------------------------
    void H5Attribute::close()
    {
        _dspace.close();
        _dtype.close();

        if(is_valid()) H5Aclose(id());
        H5Object::id(0);
    }

    //-------------------------------------------------------------------------
    String H5Attribute::name() const
    {
        char name[1024];
        H5Aget_name(id(),1024,name);
        return String(name);
    }

    //-------------------------------------------------------------------------
    String H5Attribute::base() const
    {
        return String("");
    }

    //-------------------------------------------------------------------------
    String H5Attribute::path() const
    {
        return String("");
    }
    
    //-------------------------------------------------------------------------
    //implementation of write from String
    void H5Attribute::write(const String &s) const
    {
        //throw exception if the attribute is not scalar
        if(!_dspace.is_scalar())
            throw ShapeMissmatchError(EXCEPTION_RECORD,
                "Attribute ["+name()+"] is not scalar!");

        const char *ptr = s.c_str();

        hid_t element_type = H5Aget_type(id()); 

        herr_t err = H5Awrite(id(),element_type,&ptr);
        if(err < 0)
            throw H5AttributeError(EXCEPTION_RECORD, 
                    "Error writing attribute ["+name()+"]!");
    }

    //-------------------------------------------------------------------------
    //implementation to read to string
    void H5Attribute::read(String &s) const
    {
        if(!_dspace.is_scalar())
            throw ShapeMissmatchError(EXCEPTION_RECORD, 
                    "Attribute ["+name()+"] is not scalar!");
        
        hid_t element_type = H5Aget_type(id());

        char *ptr = nullptr;

        herr_t err = H5Aread(id(),element_type,&ptr);
        if(err<0)
            throw H5AttributeError(EXCEPTION_RECORD, 
                    "Error reading attribute ["+name()+"]!");

        if(ptr)
            s = String(ptr);
        else
            s = "";
    }
           

//end of namespace
}
}
}


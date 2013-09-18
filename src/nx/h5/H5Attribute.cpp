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

#include <pni/io/nx/h5/H5Group.hpp>
#include <pni/io/nx/h5/H5Dataset.hpp>
#include <pni/io/nx/h5/H5Attribute.hpp>


namespace pni{
namespace io{
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
        H5Object::reset_id();
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
    type_id_t H5Attribute::type_id() const
    {
        return _dtype.type_id();
    }

    //-------------------------------------------------------------------------
    void H5Attribute::close()
    {
        _dspace.close();
        _dtype.close();

        if(is_valid()) H5Aclose(id());
        H5Object::reset_id();
    }

    //-------------------------------------------------------------------------
    string H5Attribute::name() const
    {
        char name[1024];
        H5Aget_name(id(),1024,name);
        return string(name);
    }

    //-------------------------------------------------------------------------
    string H5Attribute::base() const 
    { 
        dbuffer<char> buffer;

        if(is_valid())
        {
            //first we need to retrieve the path to the parent object
            hsize_t bsize;
            bsize = H5Iget_name(id(),NULL,1)+1;
            buffer.allocate(bsize);

            H5Iget_name(id(),const_cast<char*>(buffer.ptr()),bsize);
            string parent(buffer.ptr());
            return parent;
        }
        return string();
    }

    //-------------------------------------------------------------------------
    string H5Attribute::path() const 
    { 
       return base()+"@"+name();
    }

    //-------------------------------------------------------------------------
    H5Object H5Attribute::parent() const
    {
        hid_t pid;

        //attempt to retrieve the parent object
        pid = H5Oopen(id(),".",H5P_DEFAULT);


        return H5Object(pid); 
    }
    
    //-------------------------------------------------------------------------
    //implementation of write from String
    void H5Attribute::write(const string *s) const
    {
        std::vector<const char*> ptrs(size());

        for(size_t i=0;i<size();i++) ptrs[i] = s[i].data();

        //get element type
        H5Datatype element_type(H5Aget_type(id())); 

        herr_t err = H5Awrite(id(),element_type.id(),(void *)ptrs.data());
        if(err < 0)
            throw pni::io::nx::nxattribute_error(EXCEPTION_RECORD, 
                    "Error writing attribute ["+name()+"]!\n\n"+
                    get_h5_error_string());
    }

    //-------------------------------------------------------------------------
    //implementation to read to string
    void H5Attribute::read(string *s) const
    {
        //get the type of the string data stored
        H5Datatype element_type(H5Aget_type(id()));

        //if the type is not a variable length string memory must be allocated
        //for each string in the attribute
        if(!H5Tis_variable_str(element_type.id()))
            _read_static_strings(s,element_type);
        else
            _read_vl_strings(s,element_type);

    }

    //-------------------------------------------------------------------------
    void H5Attribute::_read_vl_strings(string *s,H5Datatype &stype) const
    {
        size_t nstrings = size();

        //allocate a vector of pointers each holding an individual string
        std::vector<char*> str_pointers(nstrings);
            
        herr_t err = H5Aread(id(),stype.id(),(void *)str_pointers.data());
        if(err<0)
            throw pni::io::nx::nxattribute_error(EXCEPTION_RECORD, 
                    "Error reading attribute ["+name()+"]!\n\n"+
                    get_h5_error_string());

        //copy the strings
        for(size_t i = 0;i<nstrings;i++)
            s[i] = string(str_pointers[i]);

    }

    //-------------------------------------------------------------------------
    void H5Attribute::_read_static_strings(string *s,H5Datatype &stype) const
    {
        //total number of strings stored
        size_t nstrings = size(); 
        //determine the length of the strings
        size_t ssize    = H5Tget_size(stype.id());

        //allocate memory
        std::vector<char> str_data(nstrings*ssize);

        herr_t err = H5Aread(id(),stype.id(),(void *)str_data.data());
        if(err<0)
            throw pni::io::nx::nxattribute_error(EXCEPTION_RECORD, 
                    "Error reading attribute ["+name()+"]!\n\n"+
                    get_h5_error_string());

        //copy the strings
        for(size_t i = 0;i<nstrings;++i)
            s[i] = string(str_data.data()+i*ssize,ssize);

    }
           

//end of namespace
}
}
}
}

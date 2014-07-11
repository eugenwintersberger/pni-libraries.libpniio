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

#include <iostream>
#include <pni/io/nx/h5/H5Object.hpp>
#include <pni/io/nx/h5/h5_error_stack.hpp>
#include <pni/io/exceptions.hpp>
#include "../../deprecation_warning.hpp"

namespace pni{
namespace io{
namespace nx{
namespace h5{
    using pni::io::object_error;
    using pni::io::invalid_object_error;
    //=====================private member functions============================
    void H5Object::inc_ref()
    {
        if(H5Iinc_ref(_id)<0)
            throw object_error(EXCEPTION_RECORD,
                    "Increment of reference counter failed!\n\n"
                    +get_h5_error_string());

        //Failing to succesfully inrement the reference counter for an internal
        //object ID is a serious issue and justifies to throw an exception here.
    }

    //=================constrcutors and destructors============================
    H5Object::H5Object(const hid_t &sid) :_id(sid)
    {
        if(id()<0)
            throw object_error(EXCEPTION_RECORD,
                    "HDF5 object ID < 0, object creation failed!");
    }
    
    //-------------------------------------------------------------------------
    H5Object::H5Object() noexcept :_id(0) { }

    //-------------------------------------------------------------------------
    H5Object::H5Object(const H5Object &o) 
        :_id(o._id)
    {
        //need to increment the reference 
        //counter for this object as we do copy construction
        if(is_valid()) inc_ref();
    }

    //-------------------------------------------------------------------------
    H5Object::H5Object(H5Object &&o) noexcept
        :_id(o._id) 
    {
        o._id = 0;
        //since the id is removed from the original object we do not
        //have to care about the reference counter
    }
    
    //-------------------------------------------------------------------------
    H5Object::~H5Object()
    {
        if(is_valid()) 
            if(H5Oclose(id())<0)
                throw object_error(EXCEPTION_RECORD,
                    "Error closing object - HDF5 error was:\n\n"+
                    get_h5_error_string());

        //not being able to successfully destroy a valid object indicates a
        //serious problem - the exception should thus be thrown

        reset_id(); //reset the ID value to 0
    }   


    //================assignment operators=====================================
    //implementation of the copy assignment operator
    H5Object &H5Object::operator=(const H5Object &o)
    {
        if(this == &o) return *this;

        close(); //close the actual object
        _id = o._id;

        //if the original object is valid we have to increment 
        //the reference counter for this id
        if(is_valid()) inc_ref();

        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of the move assignment operator
    H5Object &H5Object::operator=(H5Object &&o)
    {
        if(this == &o) return *this;

        close(); //close the actual object
        _id = o._id;
        o._id = 0;

        //As this is a move operation we do not need to care
        //about the IDs reference. 

        return *this;
    }
   
    //=============basic manipulation methods==================================
    bool H5Object::is_valid() const 
    {
        htri_t value = H5Iis_valid(_id);
        
        if(value < 0)
            throw object_error(EXCEPTION_RECORD,
                    "Cannot determine object validity!\n\n"+
                    get_h5_error_string());

        if(value)
            return true;
        else 
            return false;

    }

    //-------------------------------------------------------------------------
    void H5Object::close() 
    {
        //if the ID is valid this will decrement the reference counter or close
        //the object if the counter becomes 0.
        if(is_valid()) 
            if(H5Oclose(_id)<0)
                throw object_error(EXCEPTION_RECORD,
                        "Error closing object - HDF5 error was:\n\n"+
                        get_h5_error_string());

        reset_id(); //in any case we have to reset the ID of the obejct
    }
    
    //-------------------------------------------------------------------------
    const hid_t &H5Object::id() const noexcept 
    { 
        return _id; 
    }

    //-------------------------------------------------------------------------
    H5ObjectType H5Object::object_type() const 
    {

        if(!is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,"Invalid HDF5 object!");

        H5I_type_t tid = H5Iget_type(_id);
        switch(tid)
        {
            case H5I_FILE: return H5ObjectType::FILE;
            case H5I_GROUP: return H5ObjectType::GROUP;
            case H5I_DATASET: return H5ObjectType::DATASET;
            case H5I_DATATYPE: return H5ObjectType::DATATYPE;
            case H5I_DATASPACE: return H5ObjectType::DATASPACE;
            case H5I_ATTR: return H5ObjectType::ATTRIBUTE;
            default: 
                throw type_error(EXCEPTION_RECORD,
                        "HDF5 object is of invalid type!");
        };
    }

    //-------------------------------------------------------------------------
    time_t H5Object::acc_time() const
    {
        REMOVE_FUNCTION(BOOST_CURRENT_FUNCTION);
        //TO BE REMOVED
        H5O_info_t info;

        herr_t err = H5Oget_info(id(),&info);
        if(err < 0)
            throw object_error(EXCEPTION_RECORD,
                    "Cannot obtain object info!\n\n"+get_h5_error_string());

        return info.atime;
    }
    
    //-------------------------------------------------------------------------
    time_t H5Object::mod_time() const
    {
        REMOVE_FUNCTION(BOOST_CURRENT_FUNCTION);
        //TO BE REMOVED
        H5O_info_t info;

        herr_t err = H5Oget_info(id(),&info);
        if(err < 0)
            throw object_error(EXCEPTION_RECORD,
                    "Cannot obtain object info!\n\n"+get_h5_error_string());

        return info.mtime;
    }
    
    //-------------------------------------------------------------------------
    time_t H5Object::chng_time() const
    {
        REMOVE_FUNCTION(BOOST_CURRENT_FUNCTION);
        //TO BE REMOVED
        H5O_info_t info;

        herr_t err = H5Oget_info(id(),&info);
        if(err < 0)
            throw object_error(EXCEPTION_RECORD,
                    "Cannot obtain object info!\n\n"+get_h5_error_string());

        return info.ctime;
    }

    //--------------------------------------------------------------------------
    time_t H5Object::birth_time() const
    {
        REMOVE_FUNCTION(BOOST_CURRENT_FUNCTION);
        //TO BE REMOVED
        H5O_info_t info;

        herr_t err = H5Oget_info(id(),&info);
        if(err < 0)
            throw object_error(EXCEPTION_RECORD,
                    "Cannot obtain object info!\n\n"+get_h5_error_string());

        return info.btime;
    }

    //-------------------------------------------------------------------------
    pni::io::nx::nxobject_type H5Object::nxobject_type() const
    {
        if(object_type() == H5ObjectType::GROUP) 
            return pni::io::nx::nxobject_type::NXGROUP;
        else if(object_type() == H5ObjectType::FILE)
            return pni::io::nx::nxobject_type::NXGROUP;
        else if(object_type() == H5ObjectType::DATASET)
            return pni::io::nx::nxobject_type::NXFIELD;
        else
            return pni::io::nx::nxobject_type::NXNONE;

    }

    //=============comparison operators========================================
    //implementation of equality check
    bool operator==(const H5Object &a,const H5Object &b)
    {
        H5O_info_t ia,ib;

        if((!a.is_valid()) || (!b.is_valid()))
            return false;
       
        //obtain HDF5 info structure of first object
        herr_t err = H5Oget_info(a.id(),&ia);
        if(err < 0)
            throw object_error(EXCEPTION_RECORD,
                    "Cannot obtain object info of first object!\n\n" + 
                    get_h5_error_string());

        //obtain HDF5 info structure of second object
        err = H5Oget_info(b.id(),&ib);
        if(err < 0)
            throw object_error(EXCEPTION_RECORD,
                    "Cannot obtain object info of second object!\n\n" + 
                    get_h5_error_string());

        //if the addresses in the file are equal return 
        //true
        if(ia.addr == ib.addr) return true;

        return false;

    }

    //-------------------------------------------------------------------------
    //implementation of inequality check
    bool operator!=(const H5Object &a,const H5Object &b)
    {
        if(a == b) return false;
        return true;
    }



//end of namespace
}
}
}
}

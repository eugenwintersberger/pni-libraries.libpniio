//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 14, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <iostream>
#include <pni/io/nx/h5/object_imp.hpp>
#include <pni/io/nx/h5/h5_error_stack.hpp>
#include <pni/io/exceptions.hpp>

namespace pni{
namespace io{
namespace nx{
namespace h5{

    using pni::io::object_error;
    using pni::io::invalid_object_error;

    //=====================private member functions============================
    void object_imp::inc_ref()
    {
        if(H5Iinc_ref(_id)<0)
            throw object_error(EXCEPTION_RECORD,
                    "Increment of reference counter failed!\n\n"
                    +get_h5_error_string());

        //Failing to succesfully inrement the reference counter for an internal
        //object ID is a serious issue and justifies to throw an exception here.
    }

    //=================constrcutors and destructors============================
    object_imp::object_imp(hid_t &&sid) :_id(sid)
    {
        if(id()<0)
            throw object_error(EXCEPTION_RECORD,
                    "HDF5 object ID < 0, object creation failed!");
    }
    
    //-------------------------------------------------------------------------
    object_imp::object_imp() noexcept :_id(0) { }

    //-------------------------------------------------------------------------
    object_imp::object_imp(const object_imp &o) 
        :_id(o._id)
    {
        //need to increment the reference 
        //counter for this object as we do copy construction
        if(is_valid()) inc_ref();
    }

    //-------------------------------------------------------------------------
    object_imp::object_imp(object_imp &&o) noexcept
        :_id(o._id) 
    {
        o._id = 0;
        //since the id is removed from the original object we do not
        //have to care about the reference counter
    }
    
    //-------------------------------------------------------------------------
    object_imp::~object_imp()
    {
        close();
    }   


    //================assignment operators=====================================
    //implementation of the copy assignment operator
    object_imp &object_imp::operator=(const object_imp &o)
    {
        if(this == &o) return *this;

        close(); //close the current object
        _id = o._id;

        //if the original object is valid we have to increment 
        //the reference counter for this id
        if(is_valid()) inc_ref();

        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of the move assignment operator
    object_imp &object_imp::operator=(object_imp &&o) noexcept
    {
        if(this == &o) return *this;

        //we use here swap to exchange the two IDs. As we assume that the object 
        //passed to this method will be destroyed anyhow (temporary) we do not 
        //have to explicitely destroy the object
        std::swap(_id,o._id);

        //As this is a move operation we do not need to care
        //about the IDs reference. 

        return *this;
    }
   
    //=============basic manipulation methods==================================
    bool object_imp::is_valid() const 
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
    void object_imp::close() 
    {
        //if the ID is valid this will decrement the reference counter or close
        //the object if the counter becomes 0.

        if(is_valid())
        {
            herr_t error_code;
            h5object_type type = get_hdf5_type(*this);

            if(type == h5object_type::DATASPACE)
                error_code = H5Sclose(id());
            else if(type == h5object_type::ATTRIBUTE)
                error_code = H5Aclose(id());
            else if(type == h5object_type::FILE)
                error_code = H5Fclose(id());
            else if(type == h5object_type::PLIST)
                error_code = H5Pclose(id());
            else
                error_code = H5Oclose(id());

            if(error_code<0)
                throw object_error(EXCEPTION_RECORD,"Error closing object!");
        }

        reset_id(); //in any case we have to reset the ID of the obejct
    }
    
    //-------------------------------------------------------------------------
    const hid_t &object_imp::id() const noexcept 
    { 
        return _id; 
    }

    //==================some private functions=================================
    bool check_type_equality(const object_imp &a,const object_imp &b)
    {
        htri_t result = H5Tequal(a.id(),b.id());
        if(result>0) return true;
        else if(result == 0) return false;
        else
            throw object_error(EXCEPTION_RECORD,
                    "Failure checking type equality!");
    }

    //-------------------------------------------------------------------------
    bool check_plist_equality(const object_imp &a,const object_imp &b)
    {
        htri_t result = H5Pequal(a.id(),b.id());
        if(result >0) return true;
        else if(result == 0) return false;
        else
            throw object_error(EXCEPTION_RECORD,
                    "Failure checking property list equality!");
    }

    //-------------------------------------------------------------------------
    bool check_object_equality(const object_imp &a,const object_imp &b)
    {
        H5O_info_t ia,ib;

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

    //=============comparison operators========================================
    //implementation of equality check
    bool operator==(const object_imp &a,const object_imp &b)
    {
        //if one of the object is not valid they are considered as in not-equal
        if((!a.is_valid()) || (!b.is_valid()))
            return false;

        //check for type - if objects have different type we immediately 
        //tell that they cannot be equal.
        if(get_hdf5_type(a)!=get_hdf5_type(b)) return false;
    
        if(get_hdf5_type(a)==h5object_type::DATATYPE)
            return check_type_equality(a,b);
        else if(get_hdf5_type(a) == h5object_type::PLIST)
            return check_plist_equality(a,b);
        else
            return check_object_equality(a,b); 

    }

    //-------------------------------------------------------------------------
    //implementation of inequality check
    bool operator!=(const object_imp &a,const object_imp &b)
    {
        if(a == b) return false;
        return true;
    }



//end of namespace
}
}
}
}

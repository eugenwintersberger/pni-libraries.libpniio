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
 * Implementation of a general HDF5 datatype object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "H5Datatype.hpp"
#include "H5DatatypeFactory.hpp"
#include "../nxexceptions.hpp"
#include "h5_error_stack.hpp"


namespace pni{
namespace io{
namespace nx{
namespace h5{
            
        
    //=============Implementation of constructors and destructors==============
    H5Datatype::H5Datatype():H5Object() { }

    //-------------------------------------------------------------------------
    H5Datatype::H5Datatype(const H5Datatype &o):H5Object(o){ }

    //-------------------------------------------------------------------------
    H5Datatype::H5Datatype(const H5Object &o):H5Object(o){ }

    //-------------------------------------------------------------------------
    H5Datatype::H5Datatype(H5Datatype &&o):H5Object(std::move(o)){ }

    //-------------------------------------------------------------------------
    H5Datatype::H5Datatype(H5Object &&o):H5Object(std::move(o)){ }

    //-------------------------------------------------------------------------
    H5Datatype::H5Datatype(const hid_t &tid):H5Object(tid){ }

    //-------------------------------------------------------------------------
    H5Datatype::~H5Datatype()
    {
        if(is_valid()) H5Tclose(id());
        H5Object::reset_id();
    }


    //=============Assignment operator=========================================
    //implementation of copy assignment operator
    H5Datatype &H5Datatype::operator=(const H5Datatype &o)
    {
        if(this != &o) H5Object::operator=(o);
        
        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of copy conversion assignment operator
    H5Datatype &H5Datatype::operator=(const H5Object &o)
    {
        if(this != &o) H5Object::operator=(o);

        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of move assignment operator
    H5Datatype &H5Datatype::operator=(H5Datatype &&o)
    {
        if(this != &o) H5Object::operator=(std::move(o));

        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of move conversion assignment operator
    H5Datatype &H5Datatype::operator=(H5Object &&o)
    {
        if(this != &o) H5Object::operator=(std::move(o));

        return *this;
    }

    //=================implementation of inquery methods=======================
    type_id_t H5Datatype::type_id() const
    {
        if(H5DatatypeFactory::create_type<type_id_t::UINT8>()==*this) 
            return type_id_t::UINT8;

        if(H5DatatypeFactory::create_type<type_id_t::INT8>() ==*this) 
            return type_id_t::INT8;

        if(H5DatatypeFactory::create_type<type_id_t::UINT16>()==*this) 
            return type_id_t::UINT16;
        if(H5DatatypeFactory::create_type<type_id_t::INT16>() ==*this) 
            return type_id_t::INT16;

        if(H5DatatypeFactory::create_type<type_id_t::UINT32>()==*this) 
            return type_id_t::UINT32;

        if(H5DatatypeFactory::create_type<type_id_t::INT32>() ==*this) 
            return type_id_t::INT32;
        
        if(H5DatatypeFactory::create_type<type_id_t::UINT64>()==*this) 
            return type_id_t::UINT64;

        if(H5DatatypeFactory::create_type<type_id_t::INT64>() ==*this) 
            return type_id_t::INT64;
        
        if(H5DatatypeFactory::create_type<type_id_t::FLOAT32>()==*this) 
            return type_id_t::FLOAT32;
        
        if(H5DatatypeFactory::create_type<type_id_t::FLOAT64>()==*this) 
            return type_id_t::FLOAT64;
        
        if(H5DatatypeFactory::create_type<type_id_t::FLOAT128>()==*this) 
            return type_id_t::FLOAT128;
        
        if(H5DatatypeFactory::create_type<type_id_t::COMPLEX32>()==*this) 
            return type_id_t::COMPLEX32;
        
        if(H5DatatypeFactory::create_type<type_id_t::COMPLEX64>()==*this) 
            return type_id_t::COMPLEX64;
        
        if(H5DatatypeFactory::create_type<type_id_t::COMPLEX128>()==*this) 
            return type_id_t::COMPLEX128;

        if(H5DatatypeFactory::create_type<type_id_t::BINARY>() == *this) 
            return type_id_t::BINARY;

        if(H5DatatypeFactory::create_type<type_id_t::STRING>() == *this) 
            return type_id_t::STRING;

        if(H5DatatypeFactory::create_type<type_id_t::BOOL>() == *this)
            return type_id_t::BOOL;

        return type_id_t::NONE;
        
    }

    //-------------------------------------------------------------------------
    void H5Datatype::close()
    {
        if(is_valid()) H5Tclose(id());
        H5Object::reset_id(); //call the parent funtion in order to reset the 
                           //id to zero.
    }


    //==========implementation of comparison operators=========================

    //! equality comparison
    bool operator==(const H5Datatype &a,const H5Datatype &b)
    {
        htri_t res = H5Tequal(a.id(),b.id());
        if(res > 0) return true;
        if(res == 0) return false;

        if(res < 0)
            throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD,
                    "Cannot compare types!\n\n" + get_h5_error_string());

        return false;
    }

    //-------------------------------------------------------------------------
    //! inequality 
    bool operator!=(const H5Datatype &a,const H5Datatype &b)
    {
        if(a==b) return false;

        return true;
    }

//end of namespace
}
}
}
}

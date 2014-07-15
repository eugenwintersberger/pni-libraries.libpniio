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

#include <pni/io/nx/h5/h5datatype.hpp>
#include <pni/io/nx/h5/H5DatatypeFactory.hpp>
#include <pni/io/nx/nxexceptions.hpp>
#include <pni/io/nx/h5/h5_error_stack.hpp>

#include <map>
#include <unordered_map>


namespace pni{
namespace io{
namespace nx{
namespace h5{

    //map for basic numeric types
    const static std::map<type_id_t,h5datatype> __base_type_map = 
    {
     {type_id_t::UINT8,h5datatype(h5object(H5Tcopy(H5T_NATIVE_UINT8)))},
     {type_id_t::INT8,h5datatype(h5object(H5Tcopy(H5T_NATIVE_INT8)))},
     {type_id_t::UINT16,h5datatype(h5object(H5Tcopy(H5T_NATIVE_UINT16)))},
     {type_id_t::INT16,h5datatype(h5object(H5Tcopy(H5T_NATIVE_INT16)))},
     {type_id_t::UINT32,h5datatype(h5object(H5Tcopy(H5T_NATIVE_UINT32)))},
     {type_id_t::INT32,h5datatype(h5object(H5Tcopy(H5T_NATIVE_INT32)))},
     {type_id_t::UINT64,h5datatype(h5object(H5Tcopy(H5T_NATIVE_UINT64)))},
     {type_id_t::INT64,h5datatype(h5object(H5Tcopy(H5T_NATIVE_INT64)))},
     {type_id_t::FLOAT32,h5datatype(h5object(H5Tcopy(H5T_NATIVE_FLOAT)))},
     {type_id_t::FLOAT64,h5datatype(h5object(H5Tcopy(H5T_NATIVE_DOUBLE)))},
     {type_id_t::FLOAT128,h5datatype(h5object(H5Tcopy(H5T_NATIVE_LDOUBLE)))}
    };

    template<typename T> struct complex_struct
    {
        T r;
        T i;
    };

    //possible exceptions: object_error
    template<typename CT> h5datatype create_complex()
    {
        typedef typename CT::value_type base_type;
        typedef complex_struct<base_type> comp_type;
        type_id_t tid = type_id_map<base_type>::type_id;
        h5datatype h5_base_type = __base_type_map.at(tid);

        //throw object_error if this fails
        h5datatype type(h5object(H5Tcreate(H5T_COMPOUND,sizeof(comp_type))));

        if(H5Tinsert(type.object().id(),"r",HOFFSET(comp_type,r),
                    h5_base_type.object().id())<0)
            throw object_error(EXCEPTION_RECORD,
                    "Error creating complex type!\n\n"+get_h5_error_string());

        if(H5Tinsert(type.object().id(),"i",HOFFSET(comp_type,i),
                     h5_base_type.object().id())<0)
            throw object_error(EXCEPTION_RECORD,
                    "Error creating complex type!\n\n"+get_h5_error_string());

        return type;
    }

    h5datatype create_bool()
    {
        h5datatype type(h5object(H5Tcopy(H5T_NATIVE_UINT8)));
        H5Tset_precision(type.object().id(),1);
        return type;
    }

    //----------------create string and binary types--------------------
    //throws object_error
    h5datatype create_string()
    {
        string estr = "Error creating STRING type!";

        h5datatype type(h5object(H5Tcopy(H5T_C_S1)));

        if(H5Tset_strpad(type.object().id(),H5T_STR_NULLTERM)<0)
            throw object_error(EXCEPTION_RECORD,
                    estr+"\n\n"+get_h5_error_string());

        if(H5Tset_cset(type.object().id(),H5T_CSET_UTF8)<0)
            throw object_error(EXCEPTION_RECORD,
                    estr+"\n\n"+get_h5_error_string());

        //always use variable strings 
        if(H5Tset_size(type.object().id(),H5T_VARIABLE)<0)
            throw object_error(EXCEPTION_RECORD,
                    estr+"\n\n"+get_h5_error_string());

        return type;
    }

    //-------------------------------------------------------------------------
    h5datatype create_binary()
    {
        return h5datatype(h5object(H5Tcreate(H5T_OPAQUE,1)));
    }

    //------------------------------------------------------------------------
    const static std::map<type_id_t,h5datatype> __id_2_type_map = 
    {
     {type_id_t::UINT8,h5datatype(h5object(H5Tcopy(H5T_NATIVE_UINT8)))},
     {type_id_t::INT8,h5datatype(h5object(H5Tcopy(H5T_NATIVE_INT8)))},
     {type_id_t::UINT16,h5datatype(h5object(H5Tcopy(H5T_NATIVE_UINT16)))},
     {type_id_t::INT16,h5datatype(h5object(H5Tcopy(H5T_NATIVE_INT16)))},
     {type_id_t::UINT32,h5datatype(h5object(H5Tcopy(H5T_NATIVE_UINT32)))},
     {type_id_t::INT32,h5datatype(h5object(H5Tcopy(H5T_NATIVE_INT32)))},
     {type_id_t::UINT64,h5datatype(h5object(H5Tcopy(H5T_NATIVE_UINT64)))},
     {type_id_t::INT64,h5datatype(h5object(H5Tcopy(H5T_NATIVE_INT64)))},
     {type_id_t::FLOAT32,h5datatype(h5object(H5Tcopy(H5T_NATIVE_FLOAT)))},
     {type_id_t::FLOAT64,h5datatype(h5object(H5Tcopy(H5T_NATIVE_DOUBLE)))},
     {type_id_t::FLOAT128,h5datatype(h5object(H5Tcopy(H5T_NATIVE_LDOUBLE)))},
     {type_id_t::COMPLEX32,create_complex<complex32>()},
     {type_id_t::COMPLEX64,create_complex<complex64>()},
     {type_id_t::COMPLEX128,create_complex<complex128>()},
     {type_id_t::BOOL,create_bool()},
     {type_id_t::STRING,create_string()},
     {type_id_t::BINARY,create_binary()}
    };

    const h5datatype &get_type(type_id_t id)
    {
        return __id_2_type_map.at(id);
    }

    h5datatype make_type(type_id_t id)
    {
        return get_type(id);
    }
            
        
    //=============Implementation of constructors and destructors==============
    h5datatype::h5datatype() noexcept 
        :_object() 
    { }

    //-------------------------------------------------------------------------
    h5datatype::h5datatype(const h5datatype &o)
        :_object(o._object)
    { }

    //-------------------------------------------------------------------------
    h5datatype::h5datatype(h5object &&o) 
        :_object(std::move(o))
    {
        if(get_hdf5_type(_object)!=h5object_type::DATATYPE)
            throw type_error(EXCEPTION_RECORD,
                    "Object passed is not an HDF5 datatype!");
    }

    //-------------------------------------------------------------------------
    h5datatype::h5datatype(h5datatype &&o) noexcept
        :_object(std::move(o._object))
    { 
    }

    //=============Assignment operator=========================================
    //implementation of copy assignment operator
    h5datatype &h5datatype::operator=(const h5datatype &o)
    {
        if(this != &o) _object = o._object;
        
        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of move assignment operator
    h5datatype &h5datatype::operator=(h5datatype &&o)
    {
        if(this != &o) _object = std::move(o._object);

        return *this;
    }

    //-------------------------------------------------------------------------
    const h5object &h5datatype::object() const noexcept
    {
        return _object;
    }

    //=================implementation of inquery methods=======================
    type_id_t type_id(const h5datatype &o) 
    {
        for(const auto &p: __id_2_type_map)
            if(p.second == o) return p.first;
    
    }

    
    //==========implementation of comparison operators=========================

    //! equality comparison
    bool operator==(const h5datatype &a,const h5datatype &b)
    {
        return a.object() == b.object();
    }

    //-------------------------------------------------------------------------
    //! inequality 
    bool operator!=(const h5datatype &a,const h5datatype &b)
    {
        if(a==b) return false;

        return true;
    }


//end of namespace
}
}
}
}

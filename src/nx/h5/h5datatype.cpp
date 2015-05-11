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
#include <pni/io/nx/h5/h5_error_stack.hpp>
#include <vector>

#include "string_utils.hpp"


namespace pni{
namespace io{
namespace nx{
namespace h5{
    
    using namespace pni::core;
    
    typedef std::pair<type_id_t,h5datatype> id_type_pair_t;
    
    typedef std::vector<id_type_pair_t> id_type_pairs_t;
    
    //------------------------------------------------------------------------
    //map for basic numeric types
    const static std::map<type_id_t,h5datatype> __base_type_map = 
    {
     {type_id_t::UINT8,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_UINT8)))},
     {type_id_t::INT8,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_INT8)))},
     {type_id_t::UINT16,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_UINT16)))},
     {type_id_t::INT16,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_INT16)))},
     {type_id_t::UINT32,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_UINT32)))},
     {type_id_t::INT32,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_INT32)))},
     {type_id_t::UINT64,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_UINT64)))},
     {type_id_t::INT64,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_INT64)))},
     {type_id_t::FLOAT32,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_FLOAT)))},
     {type_id_t::FLOAT64,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_DOUBLE)))},
     {type_id_t::FLOAT128,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_LDOUBLE)))}
    };

    //------------------------------------------------------------------------
    //template struct for complex data type creation
    template<typename T> struct complex_struct
    {
        T r;
        T i;
    };

    //------------------------------------------------------------------------
    //possible exceptions: object_error
    template<typename CT> h5datatype create_complex()
    {
        typedef typename CT::value_type base_type;
        typedef complex_struct<base_type> comp_type;
        type_id_t tid = type_id_map<base_type>::type_id;
        h5datatype h5_base_type = __base_type_map.at(tid);

        //throw object_error if this fails
        h5datatype type(object_imp(H5Tcreate(H5T_COMPOUND,sizeof(comp_type))));

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

    //------------------------------------------------------------------------
    h5datatype create_bool()
    {
        h5datatype type(object_imp(H5Tcopy(H5T_NATIVE_UINT8)));
        H5Tset_precision(type.object().id(),1);
        return type;
    }

    //----------------create string and binary types--------------------
    //throws object_error
    h5datatype create_string()
    {
        string estr = "Error creating STRING type!";

        h5datatype type(object_imp(H5Tcopy(H5T_C_S1)));

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
    
    h5datatype create_static_string()
    {
        string estr = "Error creating STRING type!";

        h5datatype type(object_imp(H5Tcopy(H5T_C_S1)));

        if(H5Tset_strpad(type.object().id(),H5T_STR_NULLTERM)<0)
            throw object_error(EXCEPTION_RECORD,
                    estr+"\n\n"+get_h5_error_string());

        /*
        if(H5Tset_cset(type.object().id(),H5T_CSET_UTF8)<0)
            throw object_error(EXCEPTION_RECORD,
                    estr+"\n\n"+get_h5_error_string());
                    * */
                            
        return type;
    }

    //-------------------------------------------------------------------------
    h5datatype create_binary()
    {
        return h5datatype(object_imp(H5Tcreate(H5T_OPAQUE,1)));
    }

    //------------------------------------------------------------------------
    const static std::map<type_id_t,h5datatype> __id_2_type_map = 
    {
     {type_id_t::UINT8,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_UINT8)))},
     {type_id_t::INT8,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_INT8)))},
     {type_id_t::UINT16,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_UINT16)))},
     {type_id_t::INT16,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_INT16)))},
     {type_id_t::UINT32,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_UINT32)))},
     {type_id_t::INT32,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_INT32)))},
     {type_id_t::UINT64,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_UINT64)))},
     {type_id_t::INT64,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_INT64)))},
     {type_id_t::FLOAT32,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_FLOAT)))},
     {type_id_t::FLOAT64,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_DOUBLE)))},
     {type_id_t::FLOAT128,h5datatype(object_imp(H5Tcopy(H5T_NATIVE_LDOUBLE)))},
     {type_id_t::COMPLEX32,create_complex<complex32>()},
     {type_id_t::COMPLEX64,create_complex<complex64>()},
     {type_id_t::COMPLEX128,create_complex<complex128>()},
     {type_id_t::BOOL,create_bool()},
     {type_id_t::STRING,create_string()},
     {type_id_t::BINARY,create_binary()}
    };
    
#define CREATE_DTYPE(native_type)\
    h5datatype(object_imp(H5Tcopy(native_type)))
    
    const static id_type_pairs_t id_type_pairs = 
    {
        id_type_pair_t{type_id_t::UINT8,   CREATE_DTYPE(H5T_NATIVE_UINT8)},
        id_type_pair_t{type_id_t::INT8,    CREATE_DTYPE(H5T_NATIVE_INT8)},
        id_type_pair_t{type_id_t::UINT16,  CREATE_DTYPE(H5T_NATIVE_UINT16)},
        id_type_pair_t{type_id_t::INT16,   CREATE_DTYPE(H5T_NATIVE_INT16)},
        id_type_pair_t{type_id_t::UINT32,  CREATE_DTYPE(H5T_NATIVE_UINT32)},
        id_type_pair_t{type_id_t::INT32,   CREATE_DTYPE(H5T_NATIVE_INT32)},
        id_type_pair_t{type_id_t::UINT64,  CREATE_DTYPE(H5T_NATIVE_UINT64)},
        id_type_pair_t{type_id_t::INT64,   CREATE_DTYPE(H5T_NATIVE_INT64)},
        id_type_pair_t{type_id_t::FLOAT32, CREATE_DTYPE(H5T_NATIVE_FLOAT)},
        id_type_pair_t{type_id_t::FLOAT64, CREATE_DTYPE(H5T_NATIVE_DOUBLE)},
        id_type_pair_t{type_id_t::FLOAT128,CREATE_DTYPE(H5T_NATIVE_LDOUBLE)},
        id_type_pair_t{type_id_t::COMPLEX32, create_complex<complex32>()},
        id_type_pair_t{type_id_t::COMPLEX64, create_complex<complex64>()},
        id_type_pair_t{type_id_t::COMPLEX128,create_complex<complex128>()},
        id_type_pair_t{type_id_t::BOOL,  create_bool()},
        id_type_pair_t{type_id_t::STRING,create_string()},
        id_type_pair_t{type_id_t::STRING,create_static_string()},
        id_type_pair_t{type_id_t::BINARY,create_binary()}
    };

    //------------------------------------------------------------------------
    const h5datatype &get_type(type_id_t id)
    {
        auto istart = id_type_pairs.begin();
        auto iend   = id_type_pairs.end();
        
        auto result = std::find_if(istart,iend,[&id](const id_type_pair_t &p)
                                   { return p.first == id; });
                                   
        if(result == iend)
            throw type_error(EXCEPTION_RECORD,
                "PNI type does not have a corresponding HDF5 data type!");
                
        return result->second;        
    }

    //-------------------------------------------------------------------------
    h5datatype make_type(type_id_t id)
    {
        return get_type(id);
    }
            
        
    //=============Implementation of constructors and destructors==============
    h5datatype::h5datatype() noexcept 
        :_object() 
    { }

    //-------------------------------------------------------------------------
    h5datatype::h5datatype(object_imp &&o) 
        :_object(std::move(o))
    {
        if(get_hdf5_type(_object)!=h5object_type::DATATYPE)
            throw type_error(EXCEPTION_RECORD,
                    "Object passed is not an HDF5 datatype!");
    }

    //-------------------------------------------------------------------------
    const object_imp &h5datatype::object() const noexcept
    {
        return _object;
    }

    //=================implementation of inquery methods=======================
    type_id_t type_id(const h5datatype &o) 
    {
        if(!o.object().is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Datatype object not valid - cannot fetch type id!");
                    
        auto istart = id_type_pairs.begin();
        auto istop  = id_type_pairs.end();
        
        auto result = std::find_if(istart,istop,[&o](const id_type_pair_t &p)
                                   { return p.second == o; });
                                   
        if(result == istop)
            throw type_error(EXCEPTION_RECORD,"HDF5 type is unkown!");
            
        return result->first;
    }
    
    

    //==========implementation of comparison operators=========================

    //! equality comparison
    bool operator==(const h5datatype &a,const h5datatype &b)
    {
        //string type are always considered to be equal - we have to 
        //take some special measures anyhow to deal with static and 
        //variable length strings
        if(is_string_type(a) && is_string_type(b)) return true;
        
        //if we are not dealing with string types we can savely use the 
        //standard procedure of type comparison.
        htri_t result = H5Tequal(a.object().id(),b.object().id());
        if(result > 0 )
            return true;
        else if(result == 0)
            return false;
        else
            throw object_error(EXCEPTION_RECORD,
                    "Failuer comparing two data type!");
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

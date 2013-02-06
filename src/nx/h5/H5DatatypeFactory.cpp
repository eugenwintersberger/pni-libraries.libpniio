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
 * Implementation of a datatype factory.
 *
 * Created on: Feb 9, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "H5DatatypeFactory.hpp"
#include <sstream>

#include "../nxexceptions.hpp"
#include "h5_error_stack.hpp"

namespace pni{
namespace io{
namespace nx{
namespace h5{

#define STR(x) # x

#define CREATE_TYPE(hdftype)\
            hid_t t = H5Tcopy(hdftype);\
            if(t<0){\
                std::stringstream ss;\
                ss<<"Error creating ";\
                ss<<STR(hdftype);\
                ss<<" type!";\
                throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD,ss.str());\
            }\
            return H5Datatype(t)

#define CREATE_TYPE_METHODS(type,id,h5type)\
    template<> H5Datatype H5DatatypeFactory::create_type<type>()\
    {\
        CREATE_TYPE(h5type);\
    }\
    template<> H5Datatype H5DatatypeFactory::create_type<id>()\
    {\
        return create_type<type>();\
    }

#define CREATE_TYPE_GET_METHOD(type,id,h5type)\
    template<> const H5Datatype &H5DatatypeFactory::get_type<type>() const\
    {\
        return h5type;\
    }\
    template<> const H5Datatype &H5DatatypeFactory::get_type<id>() const\
    {\
        return h5type;\
    }

    //-------------------create boolean data type------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<bool>()
    {
        //we need to create a special bool type here as there is nothing like
        //this in HDF5. The reason is that HDF5 is implemented in C which does
        //not posses any native bool type. We use a single bit unsigned integer
        //value to describe boolean data. This should make boolean values
        //identifiable even from the native HDF5 API.

        hid_t tid = H5Tcopy(H5T_NATIVE_UINT8);
        H5Tset_precision(tid,1);
        return H5Datatype(tid);
    }

    //---------------------create boolean data type----------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<type_id_t::BOOL>()
    {
        return create_type<bool>();
    }
          
    //------------create integer data types------------------------------------
    CREATE_TYPE_METHODS(uint8,type_id_t::UINT8,H5T_NATIVE_UINT8)
    CREATE_TYPE_METHODS(int8,type_id_t::INT8,H5T_NATIVE_INT8)
    CREATE_TYPE_METHODS(uint16,type_id_t::UINT16,H5T_NATIVE_UINT16)
    CREATE_TYPE_METHODS(int16,type_id_t::INT16,H5T_NATIVE_INT16)
    CREATE_TYPE_METHODS(uint32,type_id_t::UINT32,H5T_NATIVE_UINT32)
    CREATE_TYPE_METHODS(int32,type_id_t::INT32,H5T_NATIVE_INT32)
    CREATE_TYPE_METHODS(uint64,type_id_t::UINT64,H5T_NATIVE_UINT64)
    CREATE_TYPE_METHODS(int64,type_id_t::INT64,H5T_NATIVE_INT64)
    CREATE_TYPE_METHODS(float32,type_id_t::FLOAT32,H5T_NATIVE_FLOAT)
    CREATE_TYPE_METHODS(float64,type_id_t::FLOAT64,H5T_NATIVE_DOUBLE)
    CREATE_TYPE_METHODS(float128,type_id_t::FLOAT128,H5T_NATIVE_LDOUBLE)

    //-------------------create double types-----------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<complex32>()
    {
        string estr = "Cannot create COMPLEX_32 type!";
        hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(__struct_complex_32));
        if(tid<0)
            throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD,
                    estr+"\n\n"+get_h5_error_string());

        if(H5Tinsert(tid,"r",HOFFSET(__struct_complex_32,r),H5T_NATIVE_FLOAT)<0)
            throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD,
                    estr+"\n\n"+get_h5_error_string());
        
        if(H5Tinsert(tid,"i",HOFFSET(__struct_complex_32,i),H5T_NATIVE_FLOAT)<0)
            throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD,
                    estr+"\n\n"+get_h5_error_string());

        return H5Datatype(tid);
    }
  
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<type_id_t::COMPLEX32>()
    {
        return create_type<complex32>();
    }

    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<complex64>()
    {
        string estr = "Error creating COMPLEX_64 type!";
        hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(__struct_complex_64));
        if(tid<0)
            throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD,
                    estr+"\n\n"+get_h5_error_string());

        if(H5Tinsert(tid,"r",HOFFSET(__struct_complex_64,r),H5T_NATIVE_DOUBLE)<0)
            throw pni::io::nx::nxbackend_error((EXCEPTION_RECORD,
                        estr+"\n\n"+get_h5_error_string());

        if(H5Tinsert(tid,"i",HOFFSET(__struct_complex_64,i),H5T_NATIVE_DOUBLE)<0)
            throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD,
                estr+"\n\n"+get_h5_error_string());

        return H5Datatype(tid);
    }

    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<type_id_t::COMPLEX64>()
    {
        return create_type<complex64>();
    }

    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<complex128>()
    {
        string estr = "Error creating COMPLEX_128 type!";

        hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(__struct_complex_128));
        if(tid<0)
            throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD,
                    estr+"\n\n"+get_h5_error_string());
        
        if(H5Tinsert(tid,"r",HOFFSET(__struct_complex_128,r),H5T_NATIVE_LDOUBLE)<0)
            throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD,
                    estr+"\n\n"+get_h5_error_string());
        
        if(H5Tinsert(tid,"i",HOFFSET(__struct_complex_128,i),H5T_NATIVE_LDOUBLE)<0)
            throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD,
                    estr+"\n\n"+get_h5_error_string());

        return H5Datatype(tid);
    }
   
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<type_id_t::COMPLEX128>()
    {
        return create_type<complex128>();
    }

    //----------------create string and binary types--------------------
    template<> H5Datatype H5DatatypeFactory::create_type<string>()
    {
        hid_t tid;
        string estr = "Error creating STRING type!";

        tid = H5Tcopy(H5T_C_S1);
        if(tid<0) 
            throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD,
                    estr+"\n\n"+get_h5_error_string()); 

        if(H5Tset_strpad(tid,H5T_STR_NULLTERM)<0)
            throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD,
                    estr+"\n\n"+get_h5_error_string());

        if(H5Tset_cset(tid,H5T_CSET_UTF8)<0)
            throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD,
                    estr+"\n\n"+get_h5_error_string());

        //always use variable strings 
        if(H5Tset_size(tid,H5T_VARIABLE)<0)
            throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD,
                    estr+"\n\n"+get_h5_error_string());

        return H5Datatype(tid);
    }
   
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<type_id_t::STRING>()
    {
        return create_type<string>();
    }
   
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<binary>()
    {
        string estr = "Error creating binary type!";
        hid_t t = H5Tcreate(H5T_OPAQUE,1);
        if(t<0)
            throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD,
                    estr+"\n\n"+get_h5_error_string()); 

        return H5Datatype(t);
    }
   
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<type_id_t::BINARY>()
    {
        return create_type<binary>();
    }

    //-------------------------------------------------------------------------
    H5DatatypeFactory::H5DatatypeFactory():
        _bool_t(H5DatatypeFactory::create_type<bool>()),
        _uint8_t(H5DatatypeFactory::create_type<uint8>()),
        _int8_t(H5DatatypeFactory::create_type<int8>()),
        _uint16_t(H5DatatypeFactory::create_type<uint16>()),
        _int16_t(H5DatatypeFactory::create_type<int16>()),
        _uint32_t(H5DatatypeFactory::create_type<uint32>()),
        _int32_t(H5DatatypeFactory::create_type<int32>()),
        _uint64_t(H5DatatypeFactory::create_type<uint64>()),
        _int64_t(H5DatatypeFactory::create_type<int64>()),
        _float32_t(H5DatatypeFactory::create_type<float32>()),
        _float64_t(H5DatatypeFactory::create_type<float64>()),
        _float128_t(H5DatatypeFactory::create_type<float128>()),
        _cmplx32_t(H5DatatypeFactory::create_type<complex32>()),
        _cmplx64_t(H5DatatypeFactory::create_type<complex64>()),
        _cmplx128_t(H5DatatypeFactory::create_type<complex128>()),
        _string_t(H5DatatypeFactory::create_type<string>()),
        _binary_t(H5DatatypeFactory::create_type<binary>())
    { }

    //-------------------------------------------------------------------------
    H5DatatypeFactory::~H5DatatypeFactory()
    {
        _bool_t.close();   
        _uint8_t.close();  
        _int8_t.close();   
        _uint16_t.close(); 
        _int16_t.close();  
        _uint32_t.close(); 
        _int32_t.close();  
        _uint64_t.close(); 
        _int64_t.close();  

        _float32_t.close(); 
        _float64_t.close(); 
        _float128_t.close(); 
        
        _cmplx32_t.close(); 
        _cmplx64_t.close(); 
        _cmplx128_t.close(); 

        _string_t.close(); 
        _binary_t.close(); 
    }

    //-------------------------------------------------------------------------
    CREATE_TYPE_GET_METHOD(bool,type_id_t::BOOL,_bool_t)
    CREATE_TYPE_GET_METHOD(uint8,type_id_t::UINT8,_uint8_t)
    CREATE_TYPE_GET_METHOD(int8,type_id_t::INT8,_int8_t)
    CREATE_TYPE_GET_METHOD(uint16,type_id_t::UINT16,_uint16_t)
    CREATE_TYPE_GET_METHOD(int16,type_id_t::INT16,_int16_t)
    CREATE_TYPE_GET_METHOD(uint32,type_id_t::UINT32,_uint32_t)
    CREATE_TYPE_GET_METHOD(int32,type_id_t::INT32,_int32_t)
    CREATE_TYPE_GET_METHOD(uint64,type_id_t::UINT64,_uint64_t)
    CREATE_TYPE_GET_METHOD(int64,type_id_t::INT64,_int64_t)
    CREATE_TYPE_GET_METHOD(float32,type_id_t::FLOAT32,_float32_t)
    CREATE_TYPE_GET_METHOD(float64,type_id_t::FLOAT64,_float64_t)
    CREATE_TYPE_GET_METHOD(float128,type_id_t::FLOAT128,_float128_t)
    CREATE_TYPE_GET_METHOD(complex32,type_id_t::COMPLEX32,_cmplx32_t)
    CREATE_TYPE_GET_METHOD(complex64,type_id_t::COMPLEX64,_cmplx64_t)
    CREATE_TYPE_GET_METHOD(complex128,type_id_t::COMPLEX128,_cmplx128_t)
    CREATE_TYPE_GET_METHOD(string,type_id_t::STRING,_string_t)
    CREATE_TYPE_GET_METHOD(binary,type_id_t::BINARY,_binary_t)


//end of namespace
}
}
}
}

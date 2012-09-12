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
 * Implementation of a datatype factory.
 *
 * Created on: Feb 9, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "H5DatatypeFactory.hpp"
#include <sstream>

namespace pni{
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
                throw H5DataTypeError(EXCEPTION_RECORD,ss.str());\
            }\
            return H5Datatype(t);

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
    template<> H5Datatype H5DatatypeFactory::create_type<Bool>()
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
    template<> H5Datatype H5DatatypeFactory::create_type<TypeID::BOOL>()
    {
        return create_type<Bool>();
    }
          
    //------------create integer data types------------------------------------
    CREATE_TYPE_METHODS(UInt8,TypeID::UINT8,H5T_NATIVE_UINT8);
    CREATE_TYPE_METHODS(Int8,TypeID::INT8,H5T_NATIVE_INT8);
    CREATE_TYPE_METHODS(UInt16,TypeID::UINT16,H5T_NATIVE_UINT16);
    CREATE_TYPE_METHODS(Int16,TypeID::INT16,H5T_NATIVE_INT16);
    CREATE_TYPE_METHODS(UInt32,TypeID::UINT32,H5T_NATIVE_UINT32);
    CREATE_TYPE_METHODS(Int32,TypeID::INT32,H5T_NATIVE_INT32);
    CREATE_TYPE_METHODS(UInt64,TypeID::UINT64,H5T_NATIVE_UINT64);
    CREATE_TYPE_METHODS(Int64,TypeID::INT64,H5T_NATIVE_INT64);
    CREATE_TYPE_METHODS(Float32,TypeID::FLOAT32,H5T_NATIVE_FLOAT);
    CREATE_TYPE_METHODS(Float64,TypeID::FLOAT64,H5T_NATIVE_DOUBLE);
    CREATE_TYPE_METHODS(Float128,TypeID::FLOAT128,H5T_NATIVE_LDOUBLE);

    //-------------------create double types-----------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<Complex32>()
    {
        String estr = "Cannot create COMPLEX_32 type!";
        hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(__struct_complex_32));
        if(tid<0)
            throw H5DataTypeError(EXCEPTION_RECORD,estr);

        if(H5Tinsert(tid,"r",HOFFSET(__struct_complex_32,r),H5T_NATIVE_FLOAT)<0)
            throw H5DataTypeError(EXCEPTION_RECORD,estr);
        
        if(H5Tinsert(tid,"i",HOFFSET(__struct_complex_32,i),H5T_NATIVE_FLOAT)<0)
            throw H5DataTypeError(EXCEPTION_RECORD,estr);

        return H5Datatype(tid);
    }
  
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<TypeID::COMPLEX32>()
    {
        return create_type<Complex32>();
    }

    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<Complex64>()
    {
        String estr = "Error creating COMPLEX_64 type!";
        hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(__struct_complex_64));
        if(tid<0)
            throw H5DataTypeError(EXCEPTION_RECORD,estr);

        if(H5Tinsert(tid,"r",HOFFSET(__struct_complex_64,r),H5T_NATIVE_DOUBLE)<0)
            throw H5DataTypeError(EXCEPTION_RECORD,estr);

        if(H5Tinsert(tid,"i",HOFFSET(__struct_complex_64,i),H5T_NATIVE_DOUBLE)<0)
            throw H5DataTypeError(EXCEPTION_RECORD,estr);

        return H5Datatype(tid);
    }

    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<TypeID::COMPLEX64>()
    {
        return create_type<Complex64>();
    }

    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<Complex128>()
    {
        String estr = "Error creating COMPLEX_128 type!";

        hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(__struct_complex_128));
        if(tid<0)
            throw H5DataTypeError(EXCEPTION_RECORD,estr);
        
        if(H5Tinsert(tid,"r",HOFFSET(__struct_complex_128,r),H5T_NATIVE_LDOUBLE)<0)
            throw H5DataTypeError(EXCEPTION_RECORD,estr);
        
        if(H5Tinsert(tid,"i",HOFFSET(__struct_complex_128,i),H5T_NATIVE_LDOUBLE)<0)
            throw H5DataTypeError(EXCEPTION_RECORD,estr);
        return H5Datatype(tid);
    }
   
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<TypeID::COMPLEX128>()
    {
        return create_type<Complex128>();
    }

    //----------------create string and binary types--------------------
    template<> H5Datatype H5DatatypeFactory::create_type<String>()
    {
        hid_t tid;
        String estr = "Error creating STRING type!";

        tid = H5Tcopy(H5T_C_S1);
        if(tid<0) throw H5DataTypeError(EXCEPTION_RECORD,estr); 

        if(H5Tset_strpad(tid,H5T_STR_NULLTERM)<0)
            throw H5DataTypeError(EXCEPTION_RECORD,estr);

        if(H5Tset_cset(tid,H5T_CSET_UTF8)<0)
            throw H5DataTypeError(EXCEPTION_RECORD,estr);

        //always use variable strings 
        if(H5Tset_size(tid,H5T_VARIABLE)<0)
            throw H5DataTypeError(EXCEPTION_RECORD,estr);

        return H5Datatype(tid);
    }
   
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<TypeID::STRING>()
    {
        return create_type<String>();
    }
   
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<Binary>()
    {
        String estr = "Error creating binary type!";
        hid_t t = H5Tcreate(H5T_OPAQUE,1);
        if(t<0)
            throw H5DataTypeError(EXCEPTION_RECORD,estr); 

        return H5Datatype(t);
    }
   
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<TypeID::BINARY>()
    {
        return create_type<Binary>();
    }

    //-------------------------------------------------------------------------
    H5DatatypeFactory::H5DatatypeFactory():
        _bool_t(H5DatatypeFactory::create_type<Bool>()),
        _uint8_t(H5DatatypeFactory::create_type<UInt8>()),
        _int8_t(H5DatatypeFactory::create_type<Int8>()),
        _uint16_t(H5DatatypeFactory::create_type<UInt16>()),
        _int16_t(H5DatatypeFactory::create_type<Int16>()),
        _uint32_t(H5DatatypeFactory::create_type<UInt32>()),
        _int32_t(H5DatatypeFactory::create_type<Int32>()),
        _uint64_t(H5DatatypeFactory::create_type<UInt64>()),
        _int64_t(H5DatatypeFactory::create_type<Int64>()),
        _float32_t(H5DatatypeFactory::create_type<Float32>()),
        _float64_t(H5DatatypeFactory::create_type<Float64>()),
        _float128_t(H5DatatypeFactory::create_type<Float128>()),
        _cmplx32_t(H5DatatypeFactory::create_type<Complex32>()),
        _cmplx64_t(H5DatatypeFactory::create_type<Complex64>()),
        _cmplx128_t(H5DatatypeFactory::create_type<Complex128>()),
        _string_t(H5DatatypeFactory::create_type<String>()),
        _binary_t(H5DatatypeFactory::create_type<Binary>())
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
    CREATE_TYPE_GET_METHOD(Bool,TypeID::BOOL,_bool_t);
    CREATE_TYPE_GET_METHOD(UInt8,TypeID::UINT8,_uint8_t);
    CREATE_TYPE_GET_METHOD(Int8,TypeID::INT8,_int8_t);
    CREATE_TYPE_GET_METHOD(UInt16,TypeID::UINT16,_uint16_t);
    CREATE_TYPE_GET_METHOD(Int16,TypeID::INT16,_int16_t);
    CREATE_TYPE_GET_METHOD(UInt32,TypeID::UINT32,_uint32_t);
    CREATE_TYPE_GET_METHOD(Int32,TypeID::INT32,_int32_t);
    CREATE_TYPE_GET_METHOD(UInt64,TypeID::UINT64,_uint64_t);
    CREATE_TYPE_GET_METHOD(Int64,TypeID::INT64,_int64_t);
    CREATE_TYPE_GET_METHOD(Float32,TypeID::FLOAT32,_float32_t);
    CREATE_TYPE_GET_METHOD(Float64,TypeID::FLOAT64,_float64_t);
    CREATE_TYPE_GET_METHOD(Float128,TypeID::FLOAT128,_float128_t);
    CREATE_TYPE_GET_METHOD(Complex32,TypeID::COMPLEX32,_cmplx32_t);
    CREATE_TYPE_GET_METHOD(Complex64,TypeID::COMPLEX64,_cmplx64_t);
    CREATE_TYPE_GET_METHOD(Complex128,TypeID::COMPLEX128,_cmplx128_t);
    CREATE_TYPE_GET_METHOD(String,TypeID::STRING,_string_t);
    CREATE_TYPE_GET_METHOD(Binary,TypeID::BINARY,_binary_t);


//end of namespace
}
}
}

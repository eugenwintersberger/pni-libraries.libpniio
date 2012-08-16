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
    template<> H5Datatype H5DatatypeFactory::create_type<UInt8>()
    {
        CREATE_TYPE(H5T_NATIVE_UINT8);
    }

    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<TypeID::UINT8>()
    {
        return create_type<UInt8>();
    }

    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<Int8>()
    {
        CREATE_TYPE(H5T_NATIVE_INT8);
    }

    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<TypeID::INT8>()
    {
        return create_type<Int8>();
    }

    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<UInt16>()
    {
        CREATE_TYPE(H5T_NATIVE_UINT16);
    }
   
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<TypeID::UINT16>()
    {
        return create_type<UInt16>();
    }

    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<Int16>()
    {
        CREATE_TYPE(H5T_NATIVE_INT16);
    }
   
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<TypeID::INT16>()
    {
        return create_type<Int16>();
    }

    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<UInt32>()
    {
        CREATE_TYPE(H5T_NATIVE_UINT32);
    }
   
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<TypeID::UINT32>()
    {
        return create_type<UInt32>();
    }

    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<Int32>()
    {
        CREATE_TYPE(H5T_NATIVE_INT32);
    }
   
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<TypeID::INT32>()
    {
        return create_type<Int32>();
    }
   
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<UInt64>()
    {
        CREATE_TYPE(H5T_NATIVE_UINT64);
    }
   
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<TypeID::UINT64>()
    {
        return create_type<UInt64>();
    }

    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<Int64>()
    {
        CREATE_TYPE(H5T_NATIVE_INT64);
    }

    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<TypeID::INT64>()
    {
        return create_type<Int64>();
    }
    //---------------create floating point types-------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<Float32>()
    {
        CREATE_TYPE(H5T_NATIVE_FLOAT);
    }
   
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<TypeID::FLOAT32>()
    {
        return create_type<Float32>();
    }

    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<Float64>()
    {
        CREATE_TYPE(H5T_NATIVE_DOUBLE);
    }
   
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<TypeID::FLOAT64>()
    {
        return create_type<Float64>();
    }

    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<Float128>()
    {
        CREATE_TYPE(H5T_NATIVE_LDOUBLE);
    }
   
    //-------------------------------------------------------------------------
    template<> H5Datatype H5DatatypeFactory::create_type<TypeID::FLOAT128>()
    {
        return create_type<Float128>();
    }

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

//end of namespace
}
}
}

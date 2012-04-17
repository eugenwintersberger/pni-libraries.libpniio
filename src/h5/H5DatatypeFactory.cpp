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

namespace pni{
    namespace nx{
        namespace h5{
          
            //------------create integer data types---------------
            template<>
                H5Datatype H5DatatypeFactory::create_type<UInt8>()
            {
                return H5Datatype(H5Tcopy(H5T_NATIVE_UINT8));
            }

            template<>
                H5Datatype H5DatatypeFactory::create_type<TypeID::UINT8>()
            {
                return create_type<UInt8>();
            }

            template<>
                H5Datatype H5DatatypeFactory::create_type<Int8>()
            {
                return H5Datatype(H5Tcopy(H5T_NATIVE_INT8));
            }

            template<>
                H5Datatype H5DatatypeFactory::create_type<TypeID::INT8>()
            {
                return create_type<Int8>();
            }

            template<>
                H5Datatype H5DatatypeFactory::create_type<UInt16>()
            {
                return H5Datatype(H5Tcopy(H5T_NATIVE_UINT16));
            }
            
            template<>
                H5Datatype H5DatatypeFactory::create_type<TypeID::UINT16>()
            {
                return create_type<UInt16>();
            }

            template<>
                H5Datatype H5DatatypeFactory::create_type<Int16>()
            {
                return H5Datatype(H5Tcopy(H5T_NATIVE_INT16));
            }
            
            template<>
                H5Datatype H5DatatypeFactory::create_type<TypeID::INT16>()
            {
                return create_type<Int16>();
            }

            template<>
                H5Datatype H5DatatypeFactory::create_type<UInt32>()
            {
                return H5Datatype(H5Tcopy(H5T_NATIVE_UINT32));
            }
            
            template<>
                H5Datatype H5DatatypeFactory::create_type<TypeID::UINT32>()
            {
                return create_type<UInt32>();
            }

            template<>
                H5Datatype H5DatatypeFactory::create_type<Int32>()
            {
                return H5Datatype(H5Tcopy(H5T_NATIVE_INT32));
            }
            
            template<>
                H5Datatype H5DatatypeFactory::create_type<TypeID::INT32>()
            {
                return create_type<Int32>();
            }
            
            template<>
                H5Datatype H5DatatypeFactory::create_type<UInt64>()
            {
                return H5Datatype(H5Tcopy(H5T_NATIVE_UINT64));
            }
            
            template<>
                H5Datatype H5DatatypeFactory::create_type<TypeID::UINT64>()
            {
                return create_type<UInt64>();
            }

            template<>
                H5Datatype H5DatatypeFactory::create_type<Int64>()
            {
                return H5Datatype(H5Tcopy(H5T_NATIVE_INT64));
            }

            template<>
                H5Datatype H5DatatypeFactory::create_type<TypeID::INT64>()
            {
                return create_type<Int64>();
            }
            //---------------create floating point types------------------------
            template<>
                H5Datatype H5DatatypeFactory::create_type<Float32>()
            {
                return H5Datatype(H5Tcopy(H5T_NATIVE_FLOAT));
            }
            
            template<>
                H5Datatype H5DatatypeFactory::create_type<TypeID::FLOAT32>()
            {
                return create_type<Float32>();
            }

            template<>
                H5Datatype H5DatatypeFactory::create_type<Float64>()
            {
                return H5Datatype(H5Tcopy(H5T_NATIVE_DOUBLE));
            }
            
            template<>
                H5Datatype H5DatatypeFactory::create_type<TypeID::FLOAT64>()
            {
                return create_type<Float64>();
            }

            template<>
                H5Datatype H5DatatypeFactory::create_type<Float128>()
            {
                return H5Datatype(H5Tcopy(H5T_NATIVE_LDOUBLE));
            }
            
            template<>
                H5Datatype H5DatatypeFactory::create_type<TypeID::FLOAT128>()
            {
                return create_type<Float128>();
            }

            //-------------------create double types----------------------------
            template<>
                H5Datatype H5DatatypeFactory::create_type<Complex32>()
            {
                hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(__struct_complex_32));
                H5Tinsert(tid,"r",HOFFSET(__struct_complex_32,r),H5T_NATIVE_FLOAT);
                H5Tinsert(tid,"i",HOFFSET(__struct_complex_32,i),H5T_NATIVE_FLOAT);
                return H5Datatype(tid);
            }
           
            template<>
                H5Datatype H5DatatypeFactory::create_type<TypeID::COMPLEX32>()
            {
                return create_type<Complex32>();
            }

            template<>
                H5Datatype H5DatatypeFactory::create_type<Complex64>()
            {
                hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(__struct_complex_64));
                H5Tinsert(tid,"r",HOFFSET(__struct_complex_64,r),H5T_NATIVE_DOUBLE);
                H5Tinsert(tid,"i",HOFFSET(__struct_complex_64,i),H5T_NATIVE_DOUBLE);
                return H5Datatype(tid);
            }

            template<>
                H5Datatype H5DatatypeFactory::create_type<TypeID::COMPLEX64>()
            {
                return create_type<Complex64>();
            }
            template<>
                H5Datatype H5DatatypeFactory::create_type<Complex128>()
            {
                hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(__struct_complex_128));
                H5Tinsert(tid,"r",HOFFSET(__struct_complex_128,r),H5T_NATIVE_LDOUBLE);
                H5Tinsert(tid,"i",HOFFSET(__struct_complex_128,i),H5T_NATIVE_LDOUBLE);
                return H5Datatype(tid);
            }
            
            template<>
                H5Datatype H5DatatypeFactory::create_type<TypeID::COMPLEX128>()
            {
                return create_type<Complex128>();
            }

            //----------------create string and binary types--------------------
            template<>
                H5Datatype H5DatatypeFactory::create_type<String>()
            {
                hid_t tid;

                tid = H5Tcopy(H5T_C_S1);
                H5Tset_strpad(tid,H5T_STR_NULLTERM);
                H5Tset_cset(tid,H5T_CSET_UTF8);
                //always use variable strings 
	            H5Tset_size(tid,H5T_VARIABLE);

                return H5Datatype(tid);
            }
            
            template<>
                H5Datatype H5DatatypeFactory::create_type<TypeID::STRING>()
            {
                return create_type<String>();
            }
            
            template<>
                H5Datatype H5DatatypeFactory::create_type<Binary>()
            {
                return H5Datatype(H5Tcreate(H5T_OPAQUE,1));
            }
            
            template<>
                H5Datatype H5DatatypeFactory::create_type<TypeID::BINARY>()
            {
                return create_type<Binary>();
            }

        }
    }
}

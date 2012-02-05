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
 * Implementation of a general HDF5 datatype object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "H5Datatype.hpp"
#include "H5Exceptions.hpp"


namespace pni{
    namespace nx{
        namespace h5{
            //=========Implementation of private methods=======================
            template<> hid_t H5Datatype::_create_complex_type<Complex32>(){
                hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(_struct_complex_32));
                H5Tinsert(tid,"r",HOFFSET(_struct_complex_32,r),H5T_NATIVE_FLOAT);
                H5Tinsert(tid,"i",HOFFSET(_struct_complex_32,i),H5T_NATIVE_FLOAT);

                return tid;
            }

            //------------------------------------------------------------------------------
            template<> hid_t H5Datatype::_create_complex_type<Complex64>(){
                hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(_struct_complex_64));
                H5Tinsert(tid,"r",HOFFSET(_struct_complex_64,r),H5T_NATIVE_DOUBLE);
                H5Tinsert(tid,"i",HOFFSET(_struct_complex_64,i),H5T_NATIVE_DOUBLE);

                return tid;
            }

            //------------------------------------------------------------------------------
            template<> hid_t H5Datatype::_create_complex_type<Complex128>(){
                hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(_struct_complex_128));
                H5Tinsert(tid,"r",HOFFSET(_struct_complex_128,r),H5T_NATIVE_LDOUBLE);
                H5Tinsert(tid,"i",HOFFSET(_struct_complex_128,i),H5T_NATIVE_LDOUBLE);
                return tid;
            }
            
            //------------------------------------------------------------------------------
            hid_t H5Datatype::__get_type_from_id(const TypeID &tid){
                EXCEPTION_SETUP("hid_t H5Datatype::"
                        "__get_type_from_id(const TypeID &tid)");
                switch(tid){
                    //create standard data types
                    case TypeID::UINT8: 
                        return H5Tcopy(H5T_NATIVE_UCHAR);
                    case TypeID::INT8:  
                        return H5Tcopy(H5T_NATIVE_CHAR);
                    case TypeID::UINT16: 
                        return H5Tcopy(H5T_NATIVE_USHORT);
                    case TypeID::INT16: 
                        return H5Tcopy(H5T_NATIVE_SHORT);
                    case TypeID::UINT32: 
                        return H5Tcopy(H5T_NATIVE_UINT);
                    case TypeID::INT32:
                        return H5Tcopy(H5T_NATIVE_INT);
                    case TypeID::UINT64:
                        return H5Tcopy(H5T_NATIVE_ULONG);
                    case TypeID::INT64:
                        return H5Tcopy(H5T_NATIVE_LONG);
                    case TypeID::FLOAT32:
                        return H5Tcopy(H5T_NATIVE_FLOAT);
                    case TypeID::FLOAT64:
                        return H5Tcopy(H5T_NATIVE_DOUBLE);
                    case TypeID::FLOAT128:
                        return H5Tcopy(H5T_NATIVE_LDOUBLE);
                
                    //create complex data types
                    case TypeID::COMPLEX32:
                        return _create_complex_type<Complex32>();
                    case TypeID::COMPLEX64:
                        return _create_complex_type<Complex64>();
                    case TypeID::COMPLEX128:
                        return _create_complex_type<Complex128>();

                    //create special data types
                    case TypeID::STRING:
                        return _create_string_type();
                    case TypeID::BINARY:
                        return H5Tcreate(H5T_OPAQUE,1);
                    default:
                        EXCEPTION_INIT(H5DataTypeError,"Unkown type id!");
                        EXCEPTION_THROW();
                }
            }
            
            
            //------------------------------------------------------------------------------
            hid_t H5Datatype::_create_string_type(){
                EXCEPTION_SETUP("hid_t H5TypeFactory::_create_string_type()");
                hid_t tid;

                tid = H5Tcopy(H5T_C_S1);
                H5Tset_strpad(tid,H5T_STR_NULLTERM);
                H5Tset_cset(tid,H5T_CSET_UTF8);
                //always use variable strings 
	            H5Tset_size(tid,H5T_VARIABLE);

                if(H5Iis_valid(tid)<=0){
                    EXCEPTION_INIT(H5DataTypeError,"Cannot create string type!");
                    EXCEPTION_THROW();
                }

                return tid;

            }
        
            //=============Implementation of constructors and destructors======
            H5Datatype::H5Datatype():H5Object()
            {
                //here we do nothing
            }

            H5Datatype::H5Datatype(const H5Datatype &o):H5Object(o){

            }

            H5Datatype::H5Datatype(const H5Object &o):H5Object(o){
            }

            H5Datatype::H5Datatype(H5Datatype &&o):H5Object(std::move(o)){
            }

            H5Datatype::H5Datatype(H5Object &&o):H5Object(std::move(o)){
            }

            H5Datatype::H5Datatype(const TypeID &tid){
                hid_t hid = __get_type_from_id(tid);
                this->id(hid);
                
            }

            H5Datatype::H5Datatype(const hid_t &tid):H5Object(tid){
            }

            template<> H5Datatype H5Datatype::create<UInt8>(){
                return H5Datatype(H5Tcopy(H5T_NATIVE_UCHAR));
            }

            template<> H5Datatype H5Datatype::create<Int8>(){
                return H5Datatype(H5Tcopy(H5T_NATIVE_CHAR));
            }

            template<> H5Datatype H5Datatype::create<UInt16>(){
                return H5Datatype(H5Tcopy(H5T_NATIVE_USHORT));
            }

            template<> H5Datatype H5Datatype::create<Int16>(){
                return H5Datatype(H5Tcopy(H5T_NATIVE_SHORT));
            }

            template<> H5Datatype H5Datatype::create<UInt32>(){
                return H5Datatype(H5Tcopy(H5T_NATIVE_UINT));
            }

            template<> H5Datatype H5Datatype::create<Int32>(){
                return H5Datatype(H5Tcopy(H5T_NATIVE_INT));
            }

            template<> H5Datatype H5Datatype::create<UInt64>(){
                return H5Datatype(H5Tcopy(H5T_NATIVE_ULONG));
            }

            template<> H5Datatype H5Datatype::create<Int64>(){
                return H5Datatype(H5Tcopy(H5T_NATIVE_LONG));
            }

            template<> H5Datatype H5Datatype::create<Float32>(){
                return H5Datatype(H5Tcopy(H5T_NATIVE_FLOAT));
            }

            template<> H5Datatype H5Datatype::create<Float64>(){
                return H5Datatype(H5Tcopy(H5T_NATIVE_DOUBLE));
            }

            template<> H5Datatype H5Datatype::create<Float128>(){
                return H5Datatype(H5Tcopy(H5T_NATIVE_LDOUBLE));
            }

            template<> H5Datatype H5Datatype::create<Complex32>(){
                return H5Datatype(_create_complex_type<Complex32>());
            }

            template<> H5Datatype H5Datatype::create<Complex64>(){
                return H5Datatype(_create_complex_type<Complex64>());
            }

            template<> H5Datatype H5Datatype::create<Complex128>(){
                return H5Datatype(_create_complex_type<Complex128>());
            }

            template<> H5Datatype H5Datatype::create<String>(){
                return H5Datatype(_create_string_type());
            }

            H5Datatype::~H5Datatype(){
                if(is_valid()) H5Tclose(id());
            }


            //=============Assignment operator=================================
            //implementation of copy assignment operator
            H5Datatype &H5Datatype::operator=(const H5Datatype &o){
                if(this != &o){
                    H5Object::operator=(o);
                }
                return *this;
            }

            //------------------------------------------------------------------
            //implementation of copy conversion assignment operator
            H5Datatype &H5Datatype::operator=(const H5Object &o){
                if(this != &o){
                    H5Object::operator=(o);
                }
                return *this;
            }

            //------------------------------------------------------------------
            //implementation of move assignment operator
            H5Datatype &H5Datatype::operator=(H5Datatype &&o){
                if(this != &o){
                    H5Object::operator=(std::move(o));
                }
                return *this;
            }

            //------------------------------------------------------------------
            //implementation of move conversion assignment operator
            H5Datatype &H5Datatype::operator=(H5Object &&o){
                if(this != &o){
                    H5Object::operator=(std::move(o));
                }
                return *this;
            }

            //=============implementation of inquery methods===================
            TypeID H5Datatype::type_id() const{
                if(H5Datatype(TypeID::UINT8)==*this) return TypeID::UINT8;
                if(H5Datatype(TypeID::INT8) ==*this) return TypeID::INT8;

                if(H5Datatype(TypeID::UINT16)==*this) return TypeID::UINT16;
                if(H5Datatype(TypeID::INT16) ==*this) return TypeID::INT16;

                if(H5Datatype(TypeID::UINT32)==*this) return TypeID::UINT32;
                if(H5Datatype(TypeID::INT32) ==*this) return TypeID::INT32;
                
                if(H5Datatype(TypeID::UINT64)==*this) return TypeID::UINT64;
                if(H5Datatype(TypeID::INT64) ==*this) return TypeID::INT64;
                
                if(H5Datatype(TypeID::FLOAT32)==*this) return TypeID::FLOAT32;
                if(H5Datatype(TypeID::FLOAT32) ==*this) return TypeID::FLOAT32;
                
                if(H5Datatype(TypeID::FLOAT64)==*this) return TypeID::FLOAT64;
                if(H5Datatype(TypeID::FLOAT64) ==*this) return TypeID::FLOAT64;
                
                if(H5Datatype(TypeID::FLOAT128)==*this) return TypeID::FLOAT128;
                if(H5Datatype(TypeID::FLOAT128) ==*this) return TypeID::FLOAT128;
                
                if(H5Datatype(TypeID::COMPLEX32)==*this) return TypeID::COMPLEX32;
                if(H5Datatype(TypeID::COMPLEX32) ==*this) return TypeID::COMPLEX32;
                
                if(H5Datatype(TypeID::COMPLEX64)==*this) return TypeID::COMPLEX64;
                if(H5Datatype(TypeID::COMPLEX64) ==*this) return TypeID::COMPLEX64;
                
                if(H5Datatype(TypeID::COMPLEX128)==*this) return TypeID::COMPLEX128;
                if(H5Datatype(TypeID::COMPLEX128) ==*this) return TypeID::COMPLEX128;

                if(H5Datatype(TypeID::BINARY) == *this) return TypeID::BINARY;
                if(H5Datatype(TypeID::STRING) == *this) return TypeID::STRING;

                return TypeID::NONE;
                
            }

            //-----------------------------------------------------------------
            void H5Datatype::close(){
                if(is_valid()) H5Tclose(id());
            }


            //==========implementation of comparison operators=================

            //! equality comparison
            bool operator==(const H5Datatype &a,const H5Datatype &b){
                EXCEPTION_SETUP("bool operator=="
                        "(const H5Datatype &a,const H5Datatype &b)");

                htri_t res = H5Tequal(a.id(),b.id());
                if(res > 0) return true;
                if(res == 0) return false;

                if(res < 0){
                    EXCEPTION_INIT(H5DataTypeError,"Cannot compare types!");
                    EXCEPTION_THROW();
                }
                return false;
            }

            //! inequality 
            bool operator!=(const H5Datatype &a,const H5Datatype &b){
                if(a==b) return false;

                return true;
            }

        //end of namespace
        }
    }
}

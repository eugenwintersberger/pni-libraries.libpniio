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
 * H5TypeFactory.cpp
 *
 *  Created on: Jun 27, 2011
 *      Author: Eugen Wintersberger
 */


#include "H5TypeFactory.hpp"
#include "H5Exceptions.hpp"


namespace pni{
namespace nx{
namespace h5{


//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::createType<Int8>() const {
	return H5Tcopy(_int8_type);
}

//------------------------------------------------------------------------------
template<> const hid_t &H5TypeFactory::getType<Int8>() const {
	return _int8_type;
}

//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::createType<UInt8>() const {
	return H5Tcopy(_uint8_type);
}

//------------------------------------------------------------------------------
template<> const hid_t &H5TypeFactory::getType<UInt8>() const {
	return _uint8_type;
}

//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::createType<Int16>() const {
	return H5Tcopy(_int16_type);
}

//------------------------------------------------------------------------------
template<> const hid_t &H5TypeFactory::getType<Int16>() const {
	return _int16_type;
}

//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::createType<UInt16>() const {
	return H5Tcopy(_uint16_type);
}

//------------------------------------------------------------------------------
template<> const hid_t &H5TypeFactory::getType<UInt16>() const {
	return _uint16_type;
}

//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::createType<Int32>() const {
	return H5Tcopy(_int32_type);
}

//------------------------------------------------------------------------------
template<> const hid_t &H5TypeFactory::getType<Int32>() const {
	return _int32_type;
}

//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::createType<UInt32>() const {
	return H5Tcopy(_uint32_type);
}

//------------------------------------------------------------------------------
template<> const hid_t &H5TypeFactory::getType<UInt32>() const {
	return _uint32_type;
}

//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::createType<Int64>() const {
	return H5Tcopy(_int64_type);
}

//------------------------------------------------------------------------------
template<> const hid_t &H5TypeFactory::getType<Int64>() const {
	return _int64_type;
}

//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::createType<UInt64>() const {
	return H5Tcopy(_uint64_type);
}

//------------------------------------------------------------------------------
template<> const hid_t &H5TypeFactory::getType<UInt64>() const {
	return _uint64_type;
}

//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::createType<Float32>() const{
	return H5Tcopy(_float32_type);
}

//------------------------------------------------------------------------------
template<> const hid_t &H5TypeFactory::getType<Float32>() const {
	return _float32_type;
}

//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::createType<Float64>() const {
	return H5Tcopy(_float64_type);
}

//------------------------------------------------------------------------------
template<> const hid_t &H5TypeFactory::getType<Float64>() const {
	return _float64_type;
}

//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::createType<Float128>() const {
	return H5Tcopy(_float128_type);
}

//------------------------------------------------------------------------------
template<> const hid_t &H5TypeFactory::getType<Float128>() const {
	return _float128_type;
}

//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::createType<Complex32>() const {
	return H5Tcopy(_complex32_type);
}

//------------------------------------------------------------------------------
template<> const hid_t &H5TypeFactory::getType<Complex32>() const {
	return _complex32_type;
}

//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::createType<Complex64>() const {
	return H5Tcopy(_complex64_type);
}

//------------------------------------------------------------------------------
template<> const hid_t &H5TypeFactory::getType<Complex64>() const {
	return _complex64_type;
}

//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::createType<Complex128>() const {
	return H5Tcopy(_complex128_type);
}

//------------------------------------------------------------------------------
template<> const hid_t &H5TypeFactory::getType<Complex128>() const {
	return _complex128_type;
}

//------------------------------------------------------------------------------
template<> const hid_t &H5TypeFactory::getType<String>() const {
	return _string_type;
}

//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::createType<String>() const {
	return H5Tcopy(_string_type);
}

//------------------------------------------------------------------------------
hid_t H5TypeFactory::createBinaryType() const {
	return H5Tcopy(_binary_type);
}

//------------------------------------------------------------------------------
const hid_t &H5TypeFactory::getBinaryType() const {
	return _binary_type;
}

//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::_create_complex_type<Complex32>(){
	hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(_struct_complex_32));
	H5Tinsert(tid,"r",HOFFSET(_struct_complex_32,r),getType<Float32>());
	H5Tinsert(tid,"i",HOFFSET(_struct_complex_32,i),getType<Float32>());

	return tid;
}

//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::_create_complex_type<Complex64>(){
	hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(_struct_complex_64));
	H5Tinsert(tid,"r",HOFFSET(_struct_complex_64,r),getType<Float64>());
	H5Tinsert(tid,"i",HOFFSET(_struct_complex_64,i),getType<Float64>());

	return tid;
}

//------------------------------------------------------------------------------
template<> hid_t H5TypeFactory::_create_complex_type<Complex128>(){
	hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(_struct_complex_128));
	H5Tinsert(tid,"r",HOFFSET(_struct_complex_128,r),getType<Float128>());
	H5Tinsert(tid,"i",HOFFSET(_struct_complex_128,i),getType<Float128>());
	return tid;
}

//------------------------------------------------------------------------------
hid_t H5TypeFactory::_create_string_type(){
	hid_t tid;

	tid = H5Tcopy(H5T_C_S1);
	H5Tset_strpad(tid,H5T_STR_NULLTERM);
	H5Tset_cset(tid,H5T_CSET_UTF8);

	if(H5Iis_valid(tid)) return tid;

	return -1;

}


//------------------------------------------------------------------------------
H5TypeFactory::H5TypeFactory() {
	//create some native simple data types
	_int8_type = H5Tcopy(H5T_NATIVE_CHAR);
	_uint8_type = H5Tcopy(H5T_NATIVE_UCHAR);
	_int16_type = H5Tcopy(H5T_NATIVE_SHORT);
	_uint16_type = H5Tcopy(H5T_NATIVE_USHORT);
	_int32_type = H5Tcopy(H5T_NATIVE_INT);
	_uint32_type = H5Tcopy(H5T_NATIVE_UINT);
	_int64_type = H5Tcopy(H5T_NATIVE_LONG);
	_uint64_type = H5Tcopy(H5T_NATIVE_ULONG);
	_float32_type = H5Tcopy(H5T_NATIVE_FLOAT);
	_float64_type = H5Tcopy(H5T_NATIVE_DOUBLE);
	_float128_type = H5Tcopy(H5T_NATIVE_LDOUBLE);

	_binary_type = H5Tcreate(H5T_OPAQUE,1);

	//creating the complex data types (this is a little more complex)
	_complex32_type = _create_complex_type<Complex32>();
	_complex64_type = _create_complex_type<Complex64>();
	_complex128_type = _create_complex_type<Complex128>();

	//need to create the prototype for the string type
	_string_type = _create_string_type();

}

//------------------------------------------------------------------------------
H5TypeFactory::~H5TypeFactory() {
	//close all data types
	if(H5Iis_valid(_int8_type)) H5Tclose(_int8_type);
	if(H5Iis_valid(_uint8_type)) H5Tclose(_uint8_type);
	if(H5Iis_valid(_int16_type)) H5Tclose(_int16_type);
	if(H5Iis_valid(_uint16_type)) H5Tclose(_uint16_type);
	if(H5Iis_valid(_int32_type)) H5Tclose(_int32_type);
	if(H5Iis_valid(_uint32_type)) H5Tclose(_uint32_type);
	if(H5Iis_valid(_int64_type)) H5Tclose(_int64_type);
	if(H5Iis_valid(_uint64_type)) H5Tclose(_uint64_type);
	if(H5Iis_valid(_float32_type)) H5Tclose(_float32_type);
	if(H5Iis_valid(_float64_type)) H5Tclose(_float64_type);
	if(H5Iis_valid(_float128_type)) H5Tclose(_float128_type);
	if(H5Iis_valid(_complex32_type)) H5Tclose(_complex32_type);
	if(H5Iis_valid(_complex64_type)) H5Tclose(_complex64_type);
	if(H5Iis_valid(_complex128_type)) H5Tclose(_complex128_type);
	if(H5Iis_valid(_string_type)) H5Tclose(_string_type);
	if(H5Iis_valid(_binary_type)) H5Tclose(_binary_type);
}

//------------------------------------------------------------------------------
hid_t H5TypeFactory::createTypeFromObject(const NumericObject &o) const{
	EXCEPTION_SETUP("hid_t H5TypeFactory::createTypeFromObject(const NumericObject &o)");

	return createTypeFromID(o.getTypeID());
}

//------------------------------------------------------------------------------
const hid_t &H5TypeFactory::getTypeFromObject(const NumericObject &o)const {
	EXCEPTION_SETUP("hid_t H5TypeFactory::getTypeFromObject(const NumericObject &o)");

	return getTypeFromID(o.getTypeID());
}

//------------------------------------------------------------------------------
const hid_t &H5TypeFactory::getTypeFromID(PNITypeID id) const{
	EXCEPTION_SETUP("hid_t H5TypeFactory::getTypeFromID(PNITypeID id)");
	switch (id) {
	case PNITypeID::UINT8: return getType<UInt8> ();
	case PNITypeID::INT8:  return getType<Int8> ();
	case PNITypeID::INT16: return getType<Int16> ();
	case PNITypeID::UINT16: return getType<UInt16> ();
	case PNITypeID::INT32:  return getType<Int32> ();
	case PNITypeID::UINT32: return getType<UInt32> ();
	case PNITypeID::INT64:  return getType<Int64> ();
	case PNITypeID::UINT64: return getType<UInt64> ();
	case PNITypeID::FLOAT32: return getType<Float32> ();
	case PNITypeID::FLOAT64: return getType<Float64> ();
	case PNITypeID::FLOAT128:  return getType<Float128> ();
	case PNITypeID::COMPLEX32:  return getType<Complex32> ();
	case PNITypeID::COMPLEX64:	 return getType<Complex64> ();
	case PNITypeID::COMPLEX128: return getType<Complex128> ();
	case PNITypeID::STRING: return getType<String> ();
	case PNITypeID::BINARY: return getBinaryType();
	default:
		EXCEPTION_INIT(H5DataTypeError,"Unknown type ID!");
		EXCEPTION_THROW();
		return -1;
	}
}

//------------------------------------------------------------------------------
hid_t H5TypeFactory::createTypeFromID(PNITypeID id) const{
	EXCEPTION_SETUP("hid_t H5TypeFactory::createTypeFromID(PNITypeID id)");
	switch (id) {
	case PNITypeID::UINT8:      return createType<UInt8> ();
	case PNITypeID::INT8:       return createType<Int8> ();
	case PNITypeID::INT16:      return createType<Int16> ();
	case PNITypeID::UINT16:     return createType<UInt16> ();
	case PNITypeID::INT32:      return createType<Int32> ();
	case PNITypeID::UINT32:     return createType<UInt32> ();
	case PNITypeID::INT64:      return createType<Int64> ();
	case PNITypeID::UINT64:     return createType<UInt64> ();
	case PNITypeID::FLOAT32:    return createType<Float32> ();
	case PNITypeID::FLOAT64:    return createType<Float64> ();
	case PNITypeID::FLOAT128:   return createType<Float128> ();
	case PNITypeID::COMPLEX32:  return createType<Complex32> ();
	case PNITypeID::COMPLEX64:  return createType<Complex64> ();
	case PNITypeID::COMPLEX128: return createType<Complex128> ();
	case PNITypeID::STRING: return createType<String>();
	case PNITypeID::BINARY: return createBinaryType();
	default:
		EXCEPTION_INIT(H5DataTypeError,"Unknown type ID!");
		EXCEPTION_THROW();
		return -1;
	}
}

//end of namespace
}
}
}


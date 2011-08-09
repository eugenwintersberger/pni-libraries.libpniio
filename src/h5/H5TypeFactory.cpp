/*
 * H5TypeFactory.cpp
 *
 *  Created on: Jun 27, 2011
 *      Author: eugen
 */

#include "H5TypeFactory.hpp"

namespace pni{
namespace nx{
namespace h5{



template<> hid_t H5TypeFactory::createType<Int8>() const {
	return H5Tcopy(_int8_type);
}

template<> hid_t H5TypeFactory::getType<Int8>() const {
	return _int8_type;
}

template<> hid_t H5TypeFactory::createType<UInt8>() const {
	return H5Tcopy(_uint8_type);
}

template<> hid_t H5TypeFactory::getType<UInt8>() const {
	return _uint8_type;
}

template<> hid_t H5TypeFactory::createType<Int16>() const {
	return H5Tcopy(_int16_type);
}

template<> hid_t H5TypeFactory::getType<Int16>() const {
	return _int16_type;
}

template<> hid_t H5TypeFactory::createType<UInt16>() const {
	return H5Tcopy(_uint16_type);
}

template<> hid_t H5TypeFactory::getType<UInt16>() const {
	return _uint16_type;
}

template<> hid_t H5TypeFactory::createType<Int32>() const {
	return H5Tcopy(_int32_type);
}

template<> hid_t H5TypeFactory::getType<Int32>() const {
	return _int32_type;
}

template<> hid_t H5TypeFactory::createType<UInt32>() const {
	return H5Tcopy(_uint32_type);
}

template<> hid_t H5TypeFactory::getType<UInt32>() const {
	return _uint32_type;
}

template<> hid_t H5TypeFactory::createType<Int64>() const {
	return H5Tcopy(_int64_type);
}

template<> hid_t H5TypeFactory::getType<Int64>() const {
	return _int64_type;
}

template<> hid_t H5TypeFactory::createType<UInt64>() const {
	return H5Tcopy(_uint64_type);
}

template<> hid_t H5TypeFactory::getType<UInt64>() const {
	return _uint64_type;
}

template<> hid_t H5TypeFactory::createType<Float32>() const{
	return H5Tcopy(_float32_type);
}

template<> hid_t H5TypeFactory::getType<Float32>() const {
	return _float32_type;
}

template<> hid_t H5TypeFactory::createType<Float64>() const {
	return H5Tcopy(_float64_type);
}

template<> hid_t H5TypeFactory::getType<Float64>() const {
	return _float64_type;
}

template<> hid_t H5TypeFactory::createType<Float128>() const {
	return H5Tcopy(_float128_type);
}

template<> hid_t H5TypeFactory::getType<Float128>() const {
	return _float128_type;
}

template<> hid_t H5TypeFactory::createType<Complex32>() const {
	return H5Tcopy(_complex32_type);
}

template<> hid_t H5TypeFactory::getType<Complex32>() const {
	return _complex32_type;
}

template<> hid_t H5TypeFactory::createType<Complex64>() const {
	return H5Tcopy(_complex64_type);
}

template<> hid_t H5TypeFactory::getType<Complex64>() const {
	return _complex64_type;
}

template<> hid_t H5TypeFactory::createType<Complex128>() const {
	return H5Tcopy(_complex128_type);
}

template<> hid_t H5TypeFactory::getType<Complex128>() const {
	return _complex128_type;
}

template<> hid_t H5TypeFactory::_create_complex_type<Complex32>(){
	hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(_struct_complex_32));
	H5Tinsert(tid,"r",HOFFSET(_struct_complex_32,r),getType<Float32>());
	H5Tinsert(tid,"i",HOFFSET(_struct_complex_32,i),getType<Float32>());

	return tid;
}

template<> hid_t H5TypeFactory::_create_complex_type<Complex64>(){
	hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(_struct_complex_64));
	H5Tinsert(tid,"r",HOFFSET(_struct_complex_64,r),getType<Float64>());
	H5Tinsert(tid,"i",HOFFSET(_struct_complex_64,i),getType<Float64>());

	return tid;
}

template<> hid_t H5TypeFactory::_create_complex_type<Complex128>(){
	hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(_struct_complex_128));
	H5Tinsert(tid,"r",HOFFSET(_struct_complex_128,r),getType<Float128>());
	H5Tinsert(tid,"i",HOFFSET(_struct_complex_128,i),getType<Float128>());

	return tid;
}

hid_t H5TypeFactory::createStringType(UInt64 size){
	hid_t tid;

	tid = H5Tcopy(H5T_C_S1);
	H5Tset_size(tid,size);
	H5Tset_strpad(tid,H5T_STR_NULLTERM);
	H5Tset_cset(tid,H5T_CSET_UTF8);

	if(H5Iis_valid(tid)) return tid;

	return -1;

}


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

	//creating the complex data types (this is a little more complex)
	_complex32_type = _create_complex_type<Complex32>();
	_complex64_type = _create_complex_type<Complex64>();
	_complex128_type = _create_complex_type<Complex128>();

}

H5TypeFactory::~H5TypeFactory() {
	//close all data types
	H5Tclose(_int8_type);
	H5Tclose(_uint8_type);
	H5Tclose(_int16_type);
	H5Tclose(_uint16_type);
	H5Tclose(_int32_type);
	H5Tclose(_uint32_type);
	H5Tclose(_int64_type);
	H5Tclose(_uint64_type);
	H5Tclose(_float32_type);
	H5Tclose(_float64_type);
	H5Tclose(_float128_type);
	H5Tclose(_complex32_type);
	H5Tclose(_complex64_type);
	H5Tclose(_complex128_type);
}

hid_t H5TypeFactory::createTypeFromObject(const NumericObject::sptr o){
	switch(o->getTypeID()){
	case UINT8: return createType<UInt8>();
	case INT8: return createType<Int8>();
	case INT16: return createType<Int16>();
	case INT32: return createType<Int32>();
	case UINT16: return createType<UInt16>();
	case UINT32: return createType<UInt32>();
	case INT64: return createType<Int64>();
	case UINT64: return createType<UInt64>();
	case FLOAT32: return createType<Float32>();
	case FLOAT64: return createType<Float64>();
	case FLOAT128: return createType<Float128>();
	case COMPLEX32: return createType<Complex32>();
	case COMPLEX64: return createType<Complex64>();
	case COMPLEX128: return createType<Complex128>();
	default:
		std::cerr<<"Cannot map PNI Type to HDF5 type!"<<std::endl;
		//raise an exception here
	}
	return -1;
}

hid_t H5TypeFactory::getTypeFromObject(const NumericObject::sptr o){
	std::cerr<<o->getTypeID()<<std::endl;
	switch(o->getTypeID()){
	case UINT8: return getType<UInt8>();
	case INT8: return getType<Int8>();
	case INT16: return getType<Int16>();
	case UINT16: return getType<UInt16>();
	case INT32: return getType<Int32>();
	case UINT32: return getType<UInt32>();
	case INT64: return getType<Int64>();
	case UINT64: return getType<UInt64>();
	case FLOAT32: return getType<Float32>();
	case FLOAT64: return getType<Float64>();
	case FLOAT128: return getType<Float128>();
	case COMPLEX32: return getType<Complex32>();
	case COMPLEX64: return getType<Complex64>();
	case COMPLEX128: return getType<Complex128>();
	default:
		std::cerr<<"Cannot map PNI Type to HDF5 type!"<<std::endl;
		//raise an exception here
	}
	return -1;
}

hid_t H5TypeFactory::getTypeFromID(PNITypeID id){
	switch (id) {
	case UINT8: return getType<UInt8> ();
	case INT8:  return getType<Int8> ();
	case INT16: return getType<Int16> ();
	case UINT16: return getType<UInt16> ();
	case INT32:  return getType<Int32> ();
	case UINT32: return getType<UInt32> ();
	case INT64:  return getType<Int64> ();
	case UINT64: return getType<UInt64> ();
	case FLOAT32: return getType<Float32> ();
	case FLOAT64: return getType<Float64> ();
	case FLOAT128:  return getType<Float128> ();
	case COMPLEX32:  return getType<Complex32> ();
	case COMPLEX64:	 return getType<Complex64> ();
	case COMPLEX128: return getType<Complex128> ();
	default:
		std::cerr << "Cannot map PNI Type to HDF5 type!" << std::endl;
		//raise an exception here
	}
	return -1;
}

hid_t H5TypeFactory::createTypeFromID(PNITypeID id){
	switch (id) {
	case UINT8:      return createType<UInt8> ();
	case INT8:       return createType<Int8> ();
	case INT16:      return createType<Int16> ();
	case UINT16:     return createType<UInt16> ();
	case INT32:      return createType<Int32> ();
	case UINT32:     return createType<UInt32> ();
	case INT64:      return createType<Int64> ();
	case UINT64:     return createType<UInt64> ();
	case FLOAT32:    return createType<Float32> ();
	case FLOAT64:    return createType<Float64> ();
	case FLOAT128:   return createType<Float128> ();
	case COMPLEX32:  return createType<Complex32> ();
	case COMPLEX64:  return createType<Complex64> ();
	case COMPLEX128: return createType<Complex128> ();
	default:
		std::cerr << "Cannot map PNI Type to HDF5 type!" << std::endl;
		//raise an exception here
	}
	return -1;
}

//end of namespace
}
}
}


/*
 * H5TypeFactory.cpp
 *
 *  Created on: Jun 27, 2011
 *      Author: eugen
 */

#include "H5TypeFactory.hpp"

namespace nx{
namespace h5{


template<> hid_t H5TypeFactory::createType<pni::utils::Int8>() const {
	return H5Tcopy(_int8_type);
}

template<> hid_t H5TypeFactory::getType<pni::utils::Int8>() const {
	return _int8_type;
}

template<> hid_t H5TypeFactory::createType<pni::utils::UInt8>() const {
	return H5Tcopy(_uint8_type);
}

template<> hid_t H5TypeFactory::getType<pni::utils::UInt8>() const {
	return _uint8_type;
}

template<> hid_t H5TypeFactory::createType<pni::utils::Int16>() const {
	return H5Tcopy(_int16_type);
}

template<> hid_t H5TypeFactory::getType<pni::utils::Int16>() const {
	return _int16_type;
}

template<> hid_t H5TypeFactory::createType<pni::utils::UInt16>() const {
	return H5Tcopy(_uint16_type);
}

template<> hid_t H5TypeFactory::getType<pni::utils::UInt16>() const {
	return _uint16_type;
}

template<> hid_t H5TypeFactory::createType<pni::utils::Int32>() const {
	return H5Tcopy(_int32_type);
}

template<> hid_t H5TypeFactory::getType<pni::utils::Int32>() const {
	return _int32_type;
}

template<> hid_t H5TypeFactory::createType<pni::utils::UInt32>() const {
	return H5Tcopy(_uint32_type);
}

template<> hid_t H5TypeFactory::getType<pni::utils::UInt32>() const {
	return _uint32_type;
}

template<> hid_t H5TypeFactory::createType<pni::utils::Int64>() const {
	return H5Tcopy(_int64_type);
}

template<> hid_t H5TypeFactory::getType<pni::utils::Int64>() const {
	return _int64_type;
}

template<> hid_t H5TypeFactory::createType<pni::utils::UInt64>() const {
	return H5Tcopy(_uint64_type);
}

template<> hid_t H5TypeFactory::getType<pni::utils::UInt64>() const {
	return _uint64_type;
}

template<> hid_t H5TypeFactory::createType<pni::utils::Float32>() const{
	return H5Tcopy(_float32_type);
}

template<> hid_t H5TypeFactory::getType<pni::utils::Float32>() const {
	return _float32_type;
}

template<> hid_t H5TypeFactory::createType<pni::utils::Float64>() const {
	return H5Tcopy(_float64_type);
}

template<> hid_t H5TypeFactory::getType<pni::utils::Float64>() const {
	return _float64_type;
}

template<> hid_t H5TypeFactory::createType<pni::utils::Float128>() const {
	return H5Tcopy(_float128_type);
}

template<> hid_t H5TypeFactory::getType<pni::utils::Float128>() const {
	return _float128_type;
}

template<> hid_t H5TypeFactory::createType<pni::utils::Complex32>() const {
	return H5Tcopy(_complex32_type);
}

template<> hid_t H5TypeFactory::getType<pni::utils::Complex32>() const {
	return _complex32_type;
}

template<> hid_t H5TypeFactory::createType<pni::utils::Complex64>() const {
	return H5Tcopy(_complex64_type);
}

template<> hid_t H5TypeFactory::getType<pni::utils::Complex64>() const {
	return _complex64_type;
}

template<> hid_t H5TypeFactory::createType<pni::utils::Complex128>() const {
	return H5Tcopy(_complex128_type);
}

template<> hid_t H5TypeFactory::getType<pni::utils::Complex128>() const {
	return _complex128_type;
}

template<> hid_t H5TypeFactory::_create_complex_type<pni::utils::Complex32>(){
	hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(_struct_complex_32));
	H5Tinsert(tid,"r",HOFFSET(_struct_complex_32,r),getType<pni::utils::Float32>());
	H5Tinsert(tid,"i",HOFFSET(_struct_complex_32,i),getType<pni::utils::Float32>());

	return tid;
}

template<> hid_t H5TypeFactory::_create_complex_type<pni::utils::Complex64>(){
	hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(_struct_complex_64));
	H5Tinsert(tid,"r",HOFFSET(_struct_complex_64,r),getType<pni::utils::Float64>());
	H5Tinsert(tid,"i",HOFFSET(_struct_complex_64,i),getType<pni::utils::Float64>());

	return tid;
}

template<> hid_t H5TypeFactory::_create_complex_type<pni::utils::Complex128>(){
	hid_t tid = H5Tcreate(H5T_COMPOUND,sizeof(_struct_complex_128));
	H5Tinsert(tid,"r",HOFFSET(_struct_complex_128,r),getType<pni::utils::Float128>());
	H5Tinsert(tid,"i",HOFFSET(_struct_complex_128,i),getType<pni::utils::Float128>());

	return tid;
}

hid_t H5TypeFactory::createStringType(pni::utils::UInt64 size){
	hid_t tid;

	tid = H5Tcopy(H5T_C_S1);
	H5Tset_size(tid,size);
	H5Tset_strpad(tid,H5T_STR_NULLTERM);
	H5Tset_cset(tid,H5T_CSET_UTF8);

	return tid;

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
	_complex32_type = _create_complex_type<pni::utils::Complex32>();
	_complex64_type = _create_complex_type<pni::utils::Complex64>();
	_complex128_type = _create_complex_type<pni::utils::Complex128>();

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

hid_t H5TypeFactory::createTypeFromObject(const pni::utils::NumericObject::sptr o){
	switch(o->getTypeID()){
	case pni::utils::UINT8: return createType<pni::utils::UInt8>();
	case pni::utils::INT8: return createType<pni::utils::Int8>();
	case pni::utils::INT16: return createType<pni::utils::Int16>();
	case pni::utils::UINT16: return createType<pni::utils::UInt16>();
	case pni::utils::INT32: return createType<pni::utils::Int32>();
	case pni::utils::UINT32: return createType<pni::utils::UInt32>();
	case pni::utils::INT64: return createType<pni::utils::Int64>();
	case pni::utils::UINT64: return createType<pni::utils::UInt64>();
	case pni::utils::FLOAT32: return createType<pni::utils::Float32>();
	case pni::utils::FLOAT64: return createType<pni::utils::Float64>();
	case pni::utils::FLOAT128: return createType<pni::utils::Float128>();
	case pni::utils::COMPLEX32: return createType<pni::utils::Complex32>();
	case pni::utils::COMPLEX64: return createType<pni::utils::Complex64>();
	case pni::utils::COMPLEX128: return createType<pni::utils::Complex128>();
	default:
		std::cerr<<"Cannot map PNI Type to HDF5 type!"<<std::endl;
		//raise an exception here
	}
	return 0;
}

hid_t H5TypeFactory::getTypeFromObject(const pni::utils::NumericObject::sptr o){
	std::cerr<<o->getTypeID()<<std::endl;
	switch(o->getTypeID()){
	case pni::utils::UINT8: return getType<pni::utils::UInt8>();
	case pni::utils::INT8: return getType<pni::utils::Int8>();
	case pni::utils::INT16: return getType<pni::utils::Int16>();
	case pni::utils::UINT16: return getType<pni::utils::UInt16>();
	case pni::utils::INT32: return getType<pni::utils::Int32>();
	case pni::utils::UINT32: return getType<pni::utils::UInt32>();
	case pni::utils::INT64: return getType<pni::utils::Int64>();
	case pni::utils::UINT64: return getType<pni::utils::UInt64>();
	case pni::utils::FLOAT32: return getType<pni::utils::Float32>();
	case pni::utils::FLOAT64: return getType<pni::utils::Float64>();
	case pni::utils::FLOAT128: return getType<pni::utils::Float128>();
	case pni::utils::COMPLEX32: return getType<pni::utils::Complex32>();
	case pni::utils::COMPLEX64: return getType<pni::utils::Complex64>();
	case pni::utils::COMPLEX128: return getType<pni::utils::Complex128>();
	default:
		std::cerr<<"Cannot map PNI Type to HDF5 type!"<<std::endl;
		//raise an exception here
	}
	return 0;
}

hid_t H5TypeFactory::getTypeFromID(pni::utils::PNITypeID id){
	switch (id) {
	case pni::utils::UINT8:
		return getType<pni::utils::UInt8> ();
	case pni::utils::INT8:
		return getType<pni::utils::Int8> ();
	case pni::utils::INT16:
		return getType<pni::utils::Int16> ();
	case pni::utils::UINT16:
		return getType<pni::utils::UInt16> ();
	case pni::utils::INT32:
		return getType<pni::utils::Int32> ();
	case pni::utils::UINT32:
		return getType<pni::utils::UInt32> ();
	case pni::utils::INT64:
		return getType<pni::utils::Int64> ();
	case pni::utils::UINT64:
		return getType<pni::utils::UInt64> ();
	case pni::utils::FLOAT32:
		return getType<pni::utils::Float32> ();
	case pni::utils::FLOAT64:
		return getType<pni::utils::Float64> ();
	case pni::utils::FLOAT128:
		return getType<pni::utils::Float128> ();
	case pni::utils::COMPLEX32:
		return getType<pni::utils::Complex32> ();
	case pni::utils::COMPLEX64:
		return getType<pni::utils::Complex64> ();
	case pni::utils::COMPLEX128:
		return getType<pni::utils::Complex128> ();
	default:
		std::cerr << "Cannot map PNI Type to HDF5 type!" << std::endl;
		//raise an exception here
	}
	return 0;
}

hid_t H5TypeFactory::createTypeFromID(pni::utils::PNITypeID id){
	switch (id) {
	case pni::utils::UINT8:
		return createType<pni::utils::UInt8> ();
	case pni::utils::INT8:
		return createType<pni::utils::Int8> ();
	case pni::utils::INT16:
		return createType<pni::utils::Int16> ();
	case pni::utils::UINT16:
		return createType<pni::utils::UInt16> ();
	case pni::utils::INT32:
		return createType<pni::utils::Int32> ();
	case pni::utils::UINT32:
		return createType<pni::utils::UInt32> ();
	case pni::utils::INT64:
		return createType<pni::utils::Int64> ();
	case pni::utils::UINT64:
		return createType<pni::utils::UInt64> ();
	case pni::utils::FLOAT32:
		return createType<pni::utils::Float32> ();
	case pni::utils::FLOAT64:
		return createType<pni::utils::Float64> ();
	case pni::utils::FLOAT128:
		return createType<pni::utils::Float128> ();
	case pni::utils::COMPLEX32:
		return createType<pni::utils::Complex32> ();
	case pni::utils::COMPLEX64:
		return createType<pni::utils::Complex64> ();
	case pni::utils::COMPLEX128:
		return createType<pni::utils::Complex128> ();
	default:
		std::cerr << "Cannot map PNI Type to HDF5 type!" << std::endl;
		//raise an exception here
	}
	return 0;
}

//end of namespace
}
}


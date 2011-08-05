/*
 * NXFieldH5Implementation.cpp
 *
 *  Created on: Jul 3, 2011
 *      Author: eugen
 */

#include "NXFieldH5Implementation.hpp"
#include "H5Exceptions.hpp"
#include "H5Utilities.hpp"

namespace pni{
namespace nx{
namespace h5{

using namespace nx::h5;

NXFieldH5Implementation::NXFieldH5Implementation() {
	_id = 0;
	_space_id = 0;
	_type_id = 0;
}

NXFieldH5Implementation::NXFieldH5Implementation(const NXFieldH5Implementation &i){
	EXCEPTION_SETUP("NXFieldH5Implementation::NXFieldH5Implementation"
			                 "(const NXFieldH5Implementation &i)");

	if(i._id != 0){
		_id = H5Dopen2(i._pid,i._name.c_str(),H5P_DEFAULT);
		if(_id<0){
			EXCEPTION_INIT(H5DataSetError,"Error opening data-set "
					                "["+i._name+"] in copy constructor!");
			EXCEPTION_THROW();
		}
	}else{
		_id = 0;
	}

	_name = i._name;
	_pid = i._pid;
	_space_id = H5Scopy(i._space_id);
	if(_space_id<0){
		EXCEPTION_INIT(H5DataSpaceError,"Error copying data-space "
				                "for data-set ["+i._name+"] in copy constructor!");
		H5Dclose(_id);
		EXCEPTION_THROW();
	}
	_type_id = H5Tcopy(i._type_id);
	if(_type_id < 0){
		EXCEPTION_INIT(H5DataTypeError,"Error copying data-type "
				               "for data-set ["+i._name+"] in copy constructor!");
		H5Dclose(_id);
		H5Sclose(_space_id);
		EXCEPTION_THROW();
	}
}

NXFieldH5Implementation::~NXFieldH5Implementation() {
	_pid = 0;
	_name.clear();
	close();
}

NXFieldH5Implementation &NXFieldH5Implementation::operator=(const NXFieldH5Implementation &o){
	EXCEPTION_SETUP("NXFieldH5Implementation &NXFieldH5Implementation::operator="
					"(const NXFieldH5Implementation &o)");

	if ( this != &o ){
		_pid = o._pid;
		_name = o._name;

		_id = H5Dopen2(o._pid,o._name.c_str(),H5P_DEFAULT);
		if(_id < 0){
			EXCEPTION_INIT(H5DataSetError,"Error opening data-set "
					                "["+o._name+"] in assignment operator!");
			EXCEPTION_THROW();
		}
		_space_id = H5Scopy(o._space_id);
		if(_space_id < 0){
			EXCEPTION_INIT(H5DataSpaceError,"Error copying "
									"data-space for data-set ["+o._name+"] in "
									"assignment operator!");
			H5Dclose(_id);
			EXCEPTION_THROW();
		}
		_type_id = H5Tcopy(o._type_id);
		if(_type_id < 0){
			EXCEPTION_INIT(H5DataTypeError,"Error copying data-type "
					                "for data-set ["+o._name+"] in assignment "
					                "operator!");
			H5Sclose(_space_id);
			H5Dclose(_id);
			EXCEPTION_THROW();
		}
	}

	return *this;
}

void NXFieldH5Implementation::close(){
	if(H5Iis_valid(_id)) H5Dclose(_id);
	if(H5Iis_valid(_space_id)) H5Sclose(_space_id);
	if(H5Iis_valid(_type_id)) H5Tclose(_type_id);
}

void NXFieldH5Implementation::write(const void *ptr){
	EXCEPTION_SETUP("void NXFieldH5Implementation::write(const void *ptr)");
	herr_t err;

	err = H5Dwrite(_id,_type_id,H5S_ALL,H5S_ALL,H5P_DEFAULT,ptr);
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error writing data to field "
												   "["+_name+"]!");
		EXCEPTION_THROW();
	}
}


void NXFieldH5Implementation::read(void *ptr) const{
	EXCEPTION_SETUP("void NXFieldH5Implementation::read(void *ptr)");
	herr_t err;

	err = H5Dread(_id,_type_id,H5S_ALL,H5S_ALL,H5P_DEFAULT,ptr);
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error reading data from field ["+_name+"]!");
		EXCEPTION_THROW();
	}
}


UInt32 NXFieldH5Implementation::getRank() const{
	return H5Sget_simple_extent_ndims(_space_id);
}

UInt32 NXFieldH5Implementation::getDimension(UInt32 i)const {
	EXCEPTION_SETUP("UInt32 NXFieldH5Implementation::getDimension(UInt32 i)");
	ssize_t rank = H5Sget_simple_extent_ndims(_space_id);
	UInt32 dim;

	if(i>=rank){
		EXCEPTION_INIT(H5DataSpaceError,"Dimension index out of bounds!");
		EXCEPTION_THROW();
	}

	hsize_t *dims = new hsize_t[rank];
	if(dims==NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for dimensions buffer!");
		EXCEPTION_THROW();
	}
	H5Sget_simple_extent_dims(_space_id,dims,NULL);

	dim = dims[i];
	delete [] dims;

	return dim;
}

UInt32 *NXFieldH5Implementation::getDimensions()const {
	EXCEPTION_SETUP("UInt32 NXFieldH5Implementation::getDimension(UInt32 i)");
	ssize_t rank = H5Sget_simple_extent_ndims(_space_id);
	UInt32 *retdims;


	hsize_t *dims = new hsize_t[rank];
	if(dims == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for dimensions buffer!");
		EXCEPTION_THROW();
	}
	retdims = new UInt32[rank];
	if(retdims == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for output buffer!");
		if(dims != NULL) delete [] dims;
		EXCEPTION_THROW();
	}
	H5Sget_simple_extent_dims(_space_id,dims,NULL);

	//copy dimensions to the ouput buffer
	for(UInt32 i=0;i<rank;i++) retdims[i] = (UInt32)dims[i];

	delete [] dims;

	return retdims;
}

void NXFieldH5Implementation::getShape(ArrayShape &s) const{
	H5Utilities::DataSpace2ArrayShape(_space_id,s);
}

PNITypeID NXFieldH5Implementation::getTypeID() const {
	return H5Utilities::H5Type2PNITypeCode(_type_id);
}

bool NXFieldH5Implementation::isScalar() const {
	if((H5Sget_simple_extent_type(_space_id)==H5S_SCALAR)
				&&(H5Tget_class(_type_id)!=H5T_STRING)){
			return true;
		}
		return false;
}

bool NXFieldH5Implementation::isArray() const {
	if(H5Sget_simple_extent_type(_space_id)==H5S_SIMPLE) return true;

	return false;
}

bool NXFieldH5Implementation::isString() const {
	if((H5Sget_simple_extent_type(_space_id)==H5S_SCALAR)
			&&(H5Tget_class(_type_id)==H5T_STRING)){
		return true;
	}
	return false;

}

UInt64 NXFieldH5Implementation::getSize() const{
	if(isArray()){
		return (UInt64)H5Sget_simple_extent_npoints(_space_id);
	}else if (isString()){
		return H5Tget_size(_type_id);
	}else if (isScalar()){
		return 1;
	}

	return 0;
}


//end of namespace
}
}
}

/*
 * NXFieldH5Implementation.cpp
 *
 *  Created on: Jul 3, 2011
 *      Author: eugen
 */

#include "NXFieldH5Implementation.hpp"
#include "H5Exceptions.hpp"

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

void NXFieldH5Implementation::write(ScalarObject &s){
	EXCEPTION_SETUP("void NXFieldH5Implementation::write(ScalarObject &s)");
	herr_t err;

	err = H5Dwrite(_id,_type_id,H5S_ALL,H5S_ALL,H5P_DEFAULT,s.getVoidPtr());
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error writing data to field "
				                                   "["+_name+"]!");
		EXCEPTION_THROW();
	}
}

void NXFieldH5Implementation::write(ArrayObject &s){
	EXCEPTION_SETUP("void NXFieldH5Implementation::write(ArrayObject &s)");
	herr_t err;

	err = H5Dwrite(_id,_type_id,H5S_ALL,H5S_ALL,H5P_DEFAULT,s.getBuffer()->getVoidPtr());
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error writing data to field ["+_name+"]!");
		EXCEPTION_THROW();
	}
}

void NXFieldH5Implementation::write(String &s){
	EXCEPTION_SETUP("void NXFieldH5Implementation::write(pni::utils::String &s)");
	herr_t err;

	err = H5Dwrite(_id,_type_id,H5S_ALL,H5S_ALL,H5P_DEFAULT,s.c_str());
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error writing data to field ["+_name+"]!");
		EXCEPTION_THROW();
	}
}

void NXFieldH5Implementation::read(ScalarObject &s){
	EXCEPTION_SETUP("void NXFieldH5Implementation::read(ScalarObject &s)");
	herr_t err;

	err = H5Dread(_id,_type_id,H5S_ALL,H5S_ALL,H5P_DEFAULT,s.getVoidPtr());
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error reading data from field ["+_name+"]!");
		EXCEPTION_THROW();
	}
}

void NXFieldH5Implementation::read(ArrayObject &s){
	EXCEPTION_SETUP("void NXFieldH5Implementation::read(ArrayObject &s)");
	herr_t err;

	err = H5Dread(_id,_type_id,H5S_ALL,H5S_ALL,H5P_DEFAULT,s.getBuffer()->getVoidPtr());
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error reading data from field ["+_name+"]!");
		EXCEPTION_THROW();
	}
}

void NXFieldH5Implementation::read(String &s){
	EXCEPTION_SETUP("void NXFieldH5Implementation::read(String &s)");
	herr_t err;

	//clear previous string data and resize the string buffer
	s.clear();
	s.resize(H5Tget_size(_type_id));

	err = H5Dread(_id,_type_id,H5S_ALL,H5S_ALL,H5P_DEFAULT,(void *)s.c_str());
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
	retdims = new UInt32[rank];
	H5Sget_simple_extent_dims(_space_id,dims,NULL);

	//copy dimensions to the ouput buffer
	for(UInt32 i=0;i<rank;i++) retdims[i] = (UInt32)dims[i];

	delete [] dims;

	return retdims;
}

UInt64 NXFieldH5Implementation::getSize() const{
	return 0;
}


//end of namespace
}
}
}

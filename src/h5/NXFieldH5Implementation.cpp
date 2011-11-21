/*
 * NXFieldH5Implementation.cpp
 *
 *  Created on: Jul 3, 2011
 *      Author: eugen
 */

#include "NXFieldH5Implementation.hpp"
#include "H5Exceptions.hpp"
#include "H5Utilities.hpp"

#include<cstdlib>
#include<cstring>
#include<cstdio>

namespace pni{
namespace nx{
namespace h5{

using namespace pni::nx::h5;

//------------------------------------------------------------------------------
//Implementation of the default constructor
NXFieldH5Implementation::NXFieldH5Implementation():NXObjectH5Implementation() {
	EXCEPTION_SETUP("NXFieldH5Implementation::NXFieldH5Implementation():NXObjectH5Implementation()");
	_space_id = 0;
	_type_id = 0;
	_elem_offset = nullptr;
	_elem_count = nullptr;
	_resize_buffer = nullptr;
	_elem_mem_space = 0;
}

//------------------------------------------------------------------------------
//Implementation of the copy constructor
NXFieldH5Implementation::NXFieldH5Implementation(const NXFieldH5Implementation &o)
                        :NXObjectH5Implementation(o){
	_space_id = 0;
	_type_id = 0;
	_elem_mem_space = 0;
	_elem_offset = nullptr;
	_elem_count = nullptr;
	_resize_buffer = nullptr;

	_get_dataset_parameters(getId());
}

//------------------------------------------------------------------------------
//Implementation of the move constructor
NXFieldH5Implementation::NXFieldH5Implementation(NXFieldH5Implementation &&o){
	//express move constructor in terms of move assignment
	*this = std::move(o);
}

//------------------------------------------------------------------------------
NXFieldH5Implementation::~NXFieldH5Implementation() {
	close();
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::_get_dataset_parameters(hid_t id){
	EXCEPTION_SETUP("void NXFieldH5Implementation::_get_dataset_parameters(hid_t id)");

	//obtain the data space of the total data set
	_space_id = H5Dget_space(getId());
	if(_space_id < 0){
		EXCEPTION_INIT(H5DataSpaceError,"Cannot obtain data-space from "
				       "data-set ["+getName()+"]!");
		EXCEPTION_THROW();
	}
	H5Utilities::DataSpace2ArrayShape(_space_id,_space_shape);

	//obtain the data type of the object
	_type_id = H5Dget_type(getId());
	if(_type_id < 0){
		EXCEPTION_INIT(H5DataTypeError,"Cannot obtain data-type from "
				       "data-set ["+getName()+"]!");
		EXCEPTION_THROW();
	}

	//now we have to set up the element parameters
	_elem_shape.setRank(_space_shape.getRank()-1);
	for(UInt64 i=1;i<_space_shape.getRank();i++) _elem_shape.setDimension(i-1,_space_shape.getDimension(i));

	//allocate memory for the offset and counts buffer of the local
	//element selection
	if(_elem_offset) delete [] _elem_offset;
	_elem_offset = nullptr;

	if(_elem_count) delete [] _elem_count;
	_elem_count = nullptr;

	_elem_count = new hsize_t[_space_shape.getRank()];
	if(!_elem_count){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate [count] buffer for element selection!");
		EXCEPTION_THROW();
	}

	_elem_offset = new hsize_t[_space_shape.getRank()];
	if(!_elem_offset){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate [offset] buffer for element selection!");
		EXCEPTION_THROW();
	}

	//need to set the appropriate values
	_elem_count[0] = 1;
	for(unsigned int i=0;i<_elem_shape.getRank();i++) _elem_count[i+1] = _elem_shape.getDimension(i);
	for(unsigned int i=0;i<_space_shape.getRank();i++) _elem_offset[i] = 0;

	//finally wee need the memory space for a selection

	H5Utilities::ArrayShape2DataSpace(_elem_shape,_elem_mem_space);


	//setting up the resize buffer
	if(_resize_buffer) delete [] _resize_buffer;
	_resize_buffer = nullptr;
	_resize_buffer = new hsize_t [_space_shape.getRank()];
	if(!_resize_buffer){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate resize buffer!");
		EXCEPTION_THROW();
	}

	for(UInt32 i=0;i<_space_shape.getRank();i++) _resize_buffer[i] = _space_shape.getDimension(i);

}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::_increment_growth_dimension(){
	EXCEPTION_SETUP("void NXFieldH5Implementation::_increment_growth_dimension()");

	//resize the dataset by one
	_resize_buffer[0]++;
	//extend the dataset
	if(H5Dset_extent(getId(),_resize_buffer)<0){
		EXCEPTION_INIT(H5DataSetError,"Resizing of dataset ["+getName()+"] failed!");
		EXCEPTION_THROW();
	}

	//this has no influence on the member size so we can leave this
	//unchanged
	H5Sclose(_space_id);
	_space_id = H5Dget_space(getId());

	_space_shape.setDimension(0,_space_shape.getDimension(0)+1);
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::setId(const hid_t &id){
	EXCEPTION_SETUP("void NXFieldH5Implementation::setId(const hid_t &id)");
	//first set the ID using the base class implementation
	NXObjectH5Implementation::setId(id);

	//--------------now we have to do some additional stuff---------------------
	//this se have to check if this is now really correct
	_get_dataset_parameters(id);

}

//------------------------------------------------------------------------------
NXFieldH5Implementation &NXFieldH5Implementation::operator=(const NXFieldH5Implementation &o){
	EXCEPTION_SETUP("NXFieldH5Implementation &NXFieldH5Implementation::operator="
					"(const NXFieldH5Implementation &o)");

	if ( this != &o ){
		(NXObjectH5Implementation &)(*this) = (NXObjectH5Implementation &)o;
		_get_dataset_parameters(o.getId());
	}

	return *this;
}

//------------------------------------------------------------------------------
//Implementation of move assignment
NXFieldH5Implementation &NXFieldH5Implementation::operator=(NXFieldH5Implementation &&o){
	EXCEPTION_SETUP("NXFieldH5Implementation &NXFieldH5Implementation::operator=(NXFieldH5Implementation &&o)");

	if(this != &o){
		(NXObjectH5Implementation &)(*this) = std::move((NXObjectH5Implementation &)o);
		//_get_dataset_parameters(getId());


		//copy everything from the original object
		_elem_offset = o._elem_offset;
		o._elem_offset = nullptr;

		_elem_count = o._elem_count;
		o._elem_count = nullptr;

		_resize_buffer = o._resize_buffer;
		o._resize_buffer = nullptr;

		_space_id = o._space_id;
		o._space_id = 0;

		_type_id = o._type_id;
		o._type_id = 0;

		_elem_mem_space = o._elem_mem_space;
		o._elem_mem_space = 0;

		_elem_shape = o._elem_shape;
		_space_shape = o._elem_shape;
		std::cout<<o._space_shape<<std::endl;
		std::cout<<_space_shape<<std::endl;
		std::cout<<o._elem_shape<<std::endl;
		std::cout<<_elem_shape<<std::endl;
		o._space_shape.setRank(0);
		o._elem_shape.setRank(0);

	}

	return *this;
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::close(){
	if(H5Iis_valid(_space_id)) H5Sclose(_space_id);
	if(H5Iis_valid(_type_id)) H5Tclose(_type_id);
	if(H5Iis_valid(_elem_mem_space)) H5Sclose(_elem_mem_space);

	if(_elem_offset) delete [] _elem_offset;
	_elem_offset = nullptr;
	if(_elem_count) delete [] _elem_count;
	_elem_count = nullptr;
	if(_resize_buffer) delete [] _resize_buffer;
	_resize_buffer = nullptr;

	NXObjectH5Implementation::close();
	_space_shape.setRank(0);
	_elem_shape.setRank(0);
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::append(const NumericObject &o){
	EXCEPTION_SETUP("void NXFieldH5Implementation::append(const ScalarObject &s)");
	herr_t err;
	hid_t elem_type;

	//get the appropriate memory type
	elem_type = H5TFactory.getTypeFromID(o.getTypeID());

	//increment the field along its growth dimension
	_increment_growth_dimension();

	//set the offset for the selection to the last index in the container
	_elem_offset[0] = getDimension(0)-1;

	//set the selection and write data
	H5Sselect_hyperslab(_space_id,H5S_SELECT_SET,_elem_offset,NULL,_elem_count,NULL);
	err = H5Dwrite(getId(),elem_type,_elem_mem_space,_space_id,H5P_DEFAULT,o.getVoidPtr());
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error writing data to field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::append(const String &s){
	EXCEPTION_SETUP("void NXFieldH5Implementation::append(const String &s)");
	herr_t err;
	hid_t elem_type;

	elem_type = H5Dget_type(getId());
	//extend field along growth dimension
	_increment_growth_dimension();
	_elem_offset[0] = getDimension(0)-1;

	const char *ptr = s.c_str();

	H5Sselect_hyperslab(_space_id,H5S_SELECT_SET,_elem_offset,NULL,_elem_count,NULL);
	err = H5Dwrite(getId(),elem_type,_elem_mem_space,_space_id,H5P_DEFAULT,&ptr);
	if(err<0){

	}
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::insert(const UInt64 &i,const NumericObject &o){
	EXCEPTION_SETUP("void NXFieldH5Implementation::insert(const UInt64 &i,const NumericObject &o)");
	herr_t err = 0;

	if(i>=getDimension(0)){
		EXCEPTION_INIT(IndexError,"Element index exceeds than growth dimension!");
		EXCEPTION_THROW();
	}

	hid_t elem_type = H5TFactory.getTypeFromID(o.getTypeID());
	_elem_offset[0] = i;

	//set the selection and write data
	H5Sselect_hyperslab(_space_id,H5S_SELECT_SET,_elem_offset,NULL,_elem_count,NULL);
	err = H5Dwrite(getId(),elem_type,_elem_mem_space,_space_id,H5P_DEFAULT,o.getVoidPtr());
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error writing data to field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::insert(const UInt64 &i,const String &s){
	EXCEPTION_SETUP("void NXFieldH5Implementation::insert(const UInt64 &i,const String &s)");
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::get(const UInt64 &i,NumericObject &o){
	EXCEPTION_SETUP("void NXFieldH5Implementation::get(const UInt64 &i,NumericObject &o)");

	if(i>=getDimension(0)){
		EXCEPTION_INIT(IndexError,"Element index exceeds container size!");
		EXCEPTION_THROW();
	}

	hid_t elem_type = H5TFactory.getTypeFromID(o.getTypeID());
	_elem_offset[0] = i;
	herr_t err = 0;

	//set the selection and write data
	H5Sselect_hyperslab(_space_id,H5S_SELECT_SET,_elem_offset,NULL,_elem_count,NULL);
	err = H5Dread(getId(),elem_type,_elem_mem_space,_space_id,H5P_DEFAULT,o.getVoidPtr());
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error reading data from field ["+getName()+"]!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::get(const UInt64 &i,String &s){
	EXCEPTION_SETUP("void NXFieldH5Implementation::get(const UInt64 &i,String &s)");

	if(i>=getDimension(0)){
		EXCEPTION_INIT(IndexError,"Element index exceeds container size!");
		EXCEPTION_THROW();
	}

	hid_t elem_type = H5Dget_type(getId());
	_elem_offset[0] = i;
	herr_t err = 0;
	hid_t xfer_plist = H5Pcreate(H5P_DATASET_XFER);

	//select data element
	H5Sselect_hyperslab(_space_id,H5S_SELECT_SET,_elem_offset,NULL,_elem_count,NULL);

	//need to determine the amount of memory required to store the data
	char *ptr = nullptr;

	err = H5Dread(getId(),elem_type,_elem_mem_space,_space_id,xfer_plist,&ptr);
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error reading data from field ["+getName()+"]!");
		EXCEPTION_THROW();
	}

	//reset selection - this is needed in order to make H5Dvlen_reclaim
	//work without producing segmentation faults
	H5Sselect_none(_space_id);

	//copy content of the pointer to the string object
	s = String(ptr);

	//reclaim memory from HDF5 library.
	H5Dvlen_reclaim(elem_type,_space_id,xfer_plist,&ptr);

}

//------------------------------------------------------------------------------
UInt32 NXFieldH5Implementation::getRank() const{
	EXCEPTION_SETUP("UInt32 NXFieldH5Implementation::getRank() const");

	return _space_shape.getRank();
}

//------------------------------------------------------------------------------
UInt32 NXFieldH5Implementation::getDimension(UInt32 i)const {
	EXCEPTION_SETUP("UInt32 NXFieldH5Implementation::getDimension(UInt32 i)");
	UInt32 dim=0;

	dim =  _space_shape.getDimension(i);

	return dim;
}

//------------------------------------------------------------------------------

const ArrayShape &NXFieldH5Implementation::getShape() const {
	return _space_shape;
}

//------------------------------------------------------------------------------
UInt32 NXFieldH5Implementation::getElementRank() const {
	return _elem_shape.getRank();
}

//------------------------------------------------------------------------------
UInt32 NXFieldH5Implementation::getElementDimension(UInt32 i) const{
	EXCEPTION_SETUP("UInt32 NXFieldH5Implementation::getElementDimension(UInt32 i) const");
	UInt32 d=0;

	try{
		d = _elem_shape.getDimension(i);
	}catch(...){
		EXCEPTION_INIT(IndexError,"Error obtaining element dimension!");
		EXCEPTION_THROW();
	}

	return d;
}

//------------------------------------------------------------------------------
UInt64 NXFieldH5Implementation::getElementSize() const{
	return _elem_shape.getSize();
}

//------------------------------------------------------------------------------
const ArrayShape &NXFieldH5Implementation::getElementShape() const{
	return _elem_shape;
}

//------------------------------------------------------------------------------
PNITypeID NXFieldH5Implementation::getTypeID() const {
	return H5Utilities::H5Type2PNITypeCode(_type_id);
}

//------------------------------------------------------------------------------
bool NXFieldH5Implementation::isScalar() const {
	if((H5Sget_simple_extent_type(_space_id)==H5S_SIMPLE)&&
			(_space_shape.getRank()==1)
				&&(H5Tget_class(_type_id)!=H5T_STRING)){
			return true;
	}
	return false;
}

//------------------------------------------------------------------------------
bool NXFieldH5Implementation::isArray() const {
	if((H5Sget_simple_extent_type(_space_id)==H5S_SIMPLE)&&(_space_shape.getRank()>1)) return true;

	return false;
}

//------------------------------------------------------------------------------
bool NXFieldH5Implementation::isString() const {
	if(H5Tget_class(_type_id)==H5T_STRING){
		return true;
	}
	return false;

}

//------------------------------------------------------------------------------
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

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

//============Implementation of private methods=================================
//allocate the buffers
void NXFieldH5Implementation::_allocate_buffers(size_t frank){
	EXCEPTION_SETUP("void NXFieldH5Implementation::_allocate_buffers()");
	//free buffers if necessary
	_free_buffers();

	_offset = new hsize_t[frank];
	if(!_offset){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate offset buffer!");
		EXCEPTION_THROW();
	}

	_count  = new hsize_t[frank];
	if(!_count){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate count buffer!");
		_free_buffers();
		EXCEPTION_THROW();
	}

	_resize = new hsize_t[frank];
	if(!_resize){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate resize buffer!");
		_free_buffers();
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::_free_buffers(){
	if(_offset) delete [] _offset;
	if(_count) delete [] _count;
	if(_resize) delete [] _resize;

	_offset = nullptr;
	_count = nullptr;
	_resize = nullptr;
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::_get_dataset_objects(hid_t id){
	EXCEPTION_SETUP("void NXFieldH5Implementation::_get_dataset_parameters(hid_t id)");

	hid_t dataset = get_id();

	//obtain the data space of the dataset on the file
	_filespace = H5Dget_space(dataset);
	if(_filespace < 0){
		EXCEPTION_INIT(H5DataSpaceError,"Cannot obtain data-space from "
				       "data-set ["+name()+"]!");
		EXCEPTION_THROW();
	}

	//construct the shape object for the file
	H5Utilities::dataspace_to_shape(_filespace,_fileshape);

	//obtain the data type of the object
	_type = H5Dget_type(dataset);
	if(_type < 0){
		EXCEPTION_INIT(H5DataTypeError,"Cannot obtain data-type from "
				       "data-set ["+name()+"]!");
		EXCEPTION_THROW();
	}

	//now we have to set up the element parameters
	_elemshape.rank(_fileshape.rank()-1);
	for(size_t i=1;i<_fileshape.rank();i++){
		_elemshape.dim(i-1,_fileshape.dim(i));
	}


	//allocate memory for the offset and counts buffer of the local
	//element selection
	_allocate_buffers(_fileshape.rank());

	//need to set the appropriate values
	_count[0] = 1;
	for(size_t i=0;i<_fileshape.rank();i++){
		if(i==0){
			_count[i] = 1;
		}else{
			_count[i] = _elemshape.dim(i-1);
		}
		_offset[i] = 0;
		_resize[i] = _fileshape.dim(i);
	}

	//finally wee need the memory space for a selection
	H5Utilities::shape_to_dataspace(_elemshape,_elemspace);
}

//============Implementation of protected methods===============================
void NXFieldH5Implementation::_resize_dataset(size_t increment){
	EXCEPTION_SETUP("void NXFieldH5Implementation::_increment_growth_dimension()");

	hid_t dataset = get_id();  //fetch dataset id

	_resize[0] += increment;  //inrement the resize buffer

	//extend the dataset
	if(H5Dset_extent(dataset,_resize)<0){
		EXCEPTION_INIT(H5DataSetError,"Resizing of dataset ["+name()+"] failed!");
		EXCEPTION_THROW();
	}

	//this has no influence on the member size so we can leave this
	//unchanged
	H5Sclose(_filespace);
	_filespace = H5Dget_space(get_id());

	_fileshape.dim(0,_fileshape.dim(0)+increment);
}


//============Implementation of constructors and destructors====================
//Implementation of the default constructor
NXFieldH5Implementation::NXFieldH5Implementation():NXObjectH5Implementation() {
	EXCEPTION_SETUP("NXFieldH5Implementation::NXFieldH5Implementation():NXObjectH5Implementation()");
	_type = 0;
	_filespace = 0;
	_elemspace = 0;
	_offset = nullptr;
	_count = nullptr;
	_resize = nullptr;
}

//------------------------------------------------------------------------------
//Implementation of the copy constructor
NXFieldH5Implementation::NXFieldH5Implementation(const NXFieldH5Implementation &o)
                        :NXObjectH5Implementation(o){
	_type = 0;
	_filespace = 0;
	_elemspace = 0;
	_offset = nullptr;
	_count = nullptr;
	_resize = nullptr;

	_get_dataset_objects(get_id());
}

//------------------------------------------------------------------------------
//Implementation of the copy conversion operator
NXFieldH5Implementation::NXFieldH5Implementation(const NXObjectH5Implementation &o)
:NXObjectH5Implementation(){
	_type = 0;
	_filespace = 0;
	_elemspace = 0;
	_offset = nullptr;
	_count = nullptr;
	_resize = nullptr;

	_get_dataset_objects(get_id());
}

//------------------------------------------------------------------------------
//Implementation of the move constructor
NXFieldH5Implementation::NXFieldH5Implementation(NXFieldH5Implementation &&o){
	//express move constructor in terms of move assignment
	*this = std::move(o);
}

//------------------------------------------------------------------------------
//Implementation of the move conversion constructor
NXFieldH5Implementation::NXFieldH5Implementation(NXObjectH5Implementation &&o){
	*this = std::move(o);
}

//------------------------------------------------------------------------------
NXFieldH5Implementation::~NXFieldH5Implementation() {
	close();
}




//============Implementation of assignment operators============================
//Implementation of copy assignment
NXFieldH5Implementation &NXFieldH5Implementation::operator=(const NXFieldH5Implementation &o){
	EXCEPTION_SETUP("NXFieldH5Implementation &NXFieldH5Implementation::operator="
					"(const NXFieldH5Implementation &o)");

	if ( this != &o ){
		(NXObjectH5Implementation &)(*this) = (NXObjectH5Implementation &)o;
		_get_dataset_objects(o.get_id());
	}

	return *this;
}

//------------------------------------------------------------------------------
//Implementation of the copy conversion assignment
NXFieldH5Implementation &NXFieldH5Implementation::operator=(const NXObjectH5Implementation &o){
	if(this != &o){
		(NXObjectH5Implementation &)(*this) = o;
		_get_dataset_objects(get_id());
	}
	return *this;
}

//------------------------------------------------------------------------------
//Implementation of move assignment
NXFieldH5Implementation &NXFieldH5Implementation::operator=(NXFieldH5Implementation &&o){
	EXCEPTION_SETUP("NXFieldH5Implementation &NXFieldH5Implementation::operator=(NXFieldH5Implementation &&o)");

	if(this != &o){
		//use move assignment of the Object implementation to move the objects
		//id
		(NXObjectH5Implementation &)(*this) = std::move((NXObjectH5Implementation &)o);

		//copy everything from the original object
		_offset = o._offset;
		o._offset = nullptr;

		_count = o._count;
		o._count = nullptr;

		_resize = o._resize;
		o._resize = nullptr;

		_filespace = o._filespace;
		o._filespace = 0;

		_type = o._type;
		o._type = 0;

		_elemspace = o._elemspace;
		o._elemspace = 0;

		_elemshape = o._elemshape;
		_fileshape = o._fileshape;

		o._fileshape.rank(0);
		o._elemshape.rank(0);

	}

	return *this;
}

//------------------------------------------------------------------------------
//Implementation of move conversion assignment
NXFieldH5Implementation &NXFieldH5Implementation::operator=(NXObjectH5Implementation &&o){
	if(this != &o){
		(NXObjectH5Implementation &)(*this) = std::move(o);

		//the source object has no other attributes - we can now simple
		//fetch the additional information
		_get_dataset_objects(get_id());
	}

	return *this;
}

//================Implementation of general purpose methods=====================

//------------------------------------------------------------------------------
void NXFieldH5Implementation::close(){
	if(H5Iis_valid(_filespace)) H5Sclose(_filespace);
	if(H5Iis_valid(_type)) H5Tclose(_type);
	if(H5Iis_valid(_elemspace)) H5Sclose(_elemspace);

	_free_buffers();

	NXObjectH5Implementation::close();
	_fileshape.rank(0);
	_elemshape.rank(0);
}

//------------------------------------------------------------------------------

const Shape &NXFieldH5Implementation::shape() const {
	return _fileshape;
}

//------------------------------------------------------------------------------
const Shape &NXFieldH5Implementation::element_shape() const{
	return _elemshape;
}

//------------------------------------------------------------------------------
TypeID NXFieldH5Implementation::type_id() const {
	return H5Utilities::h5type_to_pni_type_id(_type);
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::id(const hid_t &id){
	EXCEPTION_SETUP("void NXFieldH5Implementation::setId(const hid_t &id)");
	//first set the ID using the base class implementation
	NXObjectH5Implementation::set_id(id);

	//--------------now we have to do some additional stuff---------------------
	//this se have to check if this is now really correct
	_get_dataset_objects(id);

}



//end of namespace
}
}
}

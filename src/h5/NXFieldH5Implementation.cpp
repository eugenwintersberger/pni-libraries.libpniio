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

using namespace pni::nx::h5;

//------------------------------------------------------------------------------
NXFieldH5Implementation::NXFieldH5Implementation():NXObjectH5Implementation() {
	_space_id = 0;
	_type_id = 0;
	//we can always create a new property list which will be used as a central
	//storage for all kind of options.
	_creation_plist = H5Pcreate(H5P_DATASET_CREATE);

	_offset = NULL;
	_count = NULL;
}

//------------------------------------------------------------------------------
NXFieldH5Implementation::~NXFieldH5Implementation() {
	close();
	_free_selection_buffers();
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::create(const String &n,const NXObjectH5Implementation &o){
	EXCEPTION_SETUP("void NXFieldH5Implementation::create(const String &n,const NXObjectH5Implementation &o)");

	hid_t pid = o.getId();
	hid_t id;

	id = H5Dcreate2(pid,n.c_str(),_type_id,_space_id,H5P_DEFAULT,_creation_plist,H5P_DEFAULT);
	if(id<0){
		EXCEPTION_INIT(H5DataSetError,"Creation of dataset "+String(n)+"failed!");
		EXCEPTION_THROW();
	}

	setId(id);

	_allocate_selection_buffers(getRank());
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::_allocate_selection_buffers(UInt32 n){
	EXCEPTION_SETUP("void NXFieldH5Implementation::_allocate_selection_buffers(UInt32 n)");
	_free_selection_buffers();

	_offset = new hsize_t[n];
	if(_offset == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for offset buffer!");
		EXCEPTION_THROW();
	}

	_count = new hsize_t[n];
	if(_count == NULL){
		_free_selection_buffers();
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for count buffer!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::_free_selection_buffers(){
	if(_offset == NULL) delete [] _offset;
	if(_count == NULL) delete [] _count;

	_offset = NULL;
	_count = NULL;
}

//------------------------------------------------------------------------------
NXFieldH5Implementation &NXFieldH5Implementation::operator=(const NXFieldH5Implementation &o){
	EXCEPTION_SETUP("NXFieldH5Implementation &NXFieldH5Implementation::operator="
					"(const NXFieldH5Implementation &o)");

	if ( this != &o ){
		(NXObjectH5Implementation &)(*this) = (NXObjectH5Implementation &)o;

		if(isOpen()){  //need to obtain here the data type, data space
			//get the data space
			_space_id = H5Dget_space(getId());
			if(_space_id < 0){
				EXCEPTION_INIT(H5DataSpaceError,"Cannot obtain data-space from "
						       "data-set ["+getName()+"]!");
				EXCEPTION_THROW();
			}

			//get the data type
			_type_id = H5Dget_type(getId());
			if(_type_id < 0){
				EXCEPTION_INIT(H5DataTypeError,"Cannot obtain data-type from "
						       "data-set ["+getName()+"]!");
				EXCEPTION_THROW();
			}

			//get the creation property list
			_creation_plist = H5Dget_create_plist(getId());
			if(_creation_plist<0){
				EXCEPTION_INIT(H5PropertyListError,"Cannot obtain creation property "
						       "list fom data-set ["+getName()+"]!");
				EXCEPTION_THROW();
			}
		}else{
			_space_id = 0;
			_type_id = 0;
			_creation_plist = o._creation_plist;
		}
	}

	return *this;
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::open(const String &n,NXObjectH5Implementation &imp){
	EXCEPTION_SETUP("void NXFieldH5Implementation::open(const String &n)");

	hid_t pid = imp.getId();
	hid_t id;
	id = H5Dopen(pid,n.c_str());
	if(id<0){
		EXCEPTION_INIT(H5DataSetError,"Error opening field ["+String(n)+"]!");
		EXCEPTION_THROW();
	}

	if(isOpen()) close();
	setId(id);

	//fetch all other informatoin
	_type_id = H5Dget_type(id);
	_space_id = H5Dget_space(id);
	_creation_plist = H5Dget_create_plist(id);
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::setChunkedLayout(){
	EXCEPTION_SETUP("void NXFieldH5Implementation::setChunkedLayout()");


	if((!isOpen())&&(H5Iis_valid(_creation_plist))){
		if((H5Pset_layout(_creation_plist,H5D_CHUNKED))<0){
			EXCEPTION_INIT(H5PropertyListError,"Cannot set field layout to chunked!");
			EXCEPTION_THROW();
		}
	}
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::setChunkSize(UInt32 rank,const UInt32 *dims){
	EXCEPTION_SETUP("void NXFieldH5Implementation::setChunkSize(int rank,hsize_t *dims)");

	int r = (int)rank;
	hsize_t *d = NULL;

	d = new hsize_t[rank];
	if(d == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for chunk dimensions!");
		EXCEPTION_THROW();
	}
	for(UInt32 i=0;i<rank;i++) d[i] = dims[i];

	if(!(isOpen())&&(H5Iis_valid(_creation_plist))){
		if((H5Pset_chunk(_creation_plist,r,d))<0){
			EXCEPTION_INIT(H5PropertyListError,"Cannot set chunk size!");
			if(d != NULL) delete [] d;
			EXCEPTION_THROW();
		}
	}

	if(d!=NULL) delete [] d;
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::setChunkSize(const ArrayShape &s){
	EXCEPTION_SETUP("void NXFieldH5Implementation::setChunkSize(const ArrayShape &s)");

	int r = 0;
	hsize_t *d = NULL;

	r = s.getRank();
	d = new hsize_t[r];
	if(d == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for chunk dimensions!");
		EXCEPTION_THROW();
	}

	for(UInt32 i=0;i<s.getRank();i++) d[i] = s.getDimension(i);

	if(!(isOpen()) && (H5Iis_valid(_creation_plist))){
		if((H5Pset_chunk(_creation_plist,r,d))<0){
			EXCEPTION_INIT(H5PropertyListError,"Cannot set chunk size!");
			EXCEPTION_THROW();
		}
	}

	if(d!=NULL) delete [] d;
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::close(){
	if(H5Iis_valid(_space_id)) H5Sclose(_space_id);
	if(H5Iis_valid(_type_id)) H5Tclose(_type_id);
	if(H5Iis_valid(_creation_plist)) H5Pclose(_creation_plist);
	NXObjectH5Implementation::close();
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::write(const void *ptr){
	EXCEPTION_SETUP("void NXFieldH5Implementation::write(const void *ptr)");
	herr_t err;

	err = H5Dwrite(getId(),_type_id,H5S_ALL,H5S_ALL,H5P_DEFAULT,ptr);
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error writing data to field "
												   "["+getName()+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::read(void *ptr) const{
	EXCEPTION_SETUP("void NXFieldH5Implementation::read(void *ptr)");
	herr_t err;

	err = H5Dread(getId(),_type_id,H5S_ALL,H5S_ALL,H5P_DEFAULT,ptr);
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error reading data from field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
UInt32 NXFieldH5Implementation::getRank() const{
	EXCEPTION_SETUP("UInt32 NXFieldH5Implementation::getRank() const");

	if(H5Iis_valid(_space_id)){
		return H5Sget_simple_extent_ndims(_space_id);
	}else{
		EXCEPTION_INIT(H5DataSpaceError,"Cannot obtain rank from data-space of field ["+getName()+"!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
UInt32 NXFieldH5Implementation::getDimension(UInt32 i)const {
	EXCEPTION_SETUP("UInt32 NXFieldH5Implementation::getDimension(UInt32 i)");
	ssize_t rank = getRank();
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

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
void NXFieldH5Implementation::getShape(ArrayShape &s) const{
	H5Utilities::DataSpace2ArrayShape(_space_id,s);
}

//------------------------------------------------------------------------------
PNITypeID NXFieldH5Implementation::getTypeID() const {
	return H5Utilities::H5Type2PNITypeCode(_type_id);
}

//------------------------------------------------------------------------------
bool NXFieldH5Implementation::isScalar() const {
	if((H5Sget_simple_extent_type(_space_id)==H5S_SCALAR)
				&&(H5Tget_class(_type_id)!=H5T_STRING)){
			return true;
		}
		return false;
}

//------------------------------------------------------------------------------
bool NXFieldH5Implementation::isArray() const {
	if(H5Sget_simple_extent_type(_space_id)==H5S_SIMPLE) return true;

	return false;
}

//------------------------------------------------------------------------------
bool NXFieldH5Implementation::isString() const {
	if((H5Sget_simple_extent_type(_space_id)==H5S_SCALAR)
			&&(H5Tget_class(_type_id)==H5T_STRING)){
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

//------------------------------------------------------------------------------
void NXFieldH5Implementation::setDataSpace(UInt32 rank,const UInt32 *dims){
	EXCEPTION_SETUP("void NXFieldH5Implementation::setDataSpace(int rank,hsize_t *dims)");

	int r = rank;
	hsize_t *d = new hsize_t[rank];
	for(UInt32 i = 0;i<rank;i++) d[i] = dims[i];

	if(H5Iis_valid(_space_id)) H5Tclose(_space_id);

	_space_id = H5Screate_simple(r,d,NULL);
	if(_space_id < 0){
		EXCEPTION_INIT(H5DataSpaceError,"Cannot create simple data-space!");
		EXCEPTION_THROW();
	}

	delete [] d;

}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::setDataSpace(const ArrayShape &s){
	EXCEPTION_SETUP("void NXFieldH5Implementation::setDataSpace(const ArrayShape &s)");

	int r = s.getRank();
	hsize_t *d = NULL;
	d = new hsize_t[r];
	if(d == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for data space dimensions!");
		EXCEPTION_THROW();
	}

	if(H5Iis_valid(_space_id)) H5Tclose(_space_id);

	_space_id = H5Screate_simple(r,d,NULL);
	if(_space_id < 0){
		EXCEPTION_INIT(H5DataSpaceError,"Cannot create simple data-space!");
		EXCEPTION_THROW();
	}

	if(d!=NULL) delete [] d;
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::setDataSpace(){
	EXCEPTION_SETUP("void NXFieldH5Implementation::setDataSpace()");

	if(H5Iis_valid(_space_id)) H5Tclose(_space_id);

	_space_id =H5Screate(H5S_SCALAR);
	if(_space_id<0){
		EXCEPTION_INIT(H5DataSpaceError,"Cannot create scalar data space!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::setDataType(PNITypeID tid){
	EXCEPTION_SETUP("void NXFieldH5Implementation::setDataType(hid_t type_id)");

	//close the type object if it already exists
	if(H5Iis_valid(_type_id)) H5Tclose(_type_id);

	_type_id = H5TFactory.createTypeFromID(tid);
	if(_type_id < 0){
		EXCEPTION_INIT(H5DataTypeError,"Type creation failed!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::setDataType(UInt64 size){
	EXCEPTION_SETUP("void NXFieldH5Implementation::setDataType(const String &n)");

	//close the type object if it already exists
	if(H5Iis_valid(_type_id)) H5Tclose(_type_id);

	_type_id = H5TFactory.createStringType(size);

	if(_type_id < 0){
		EXCEPTION_INIT(H5DataTypeError,"Type creation failed!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::setSelection(const Selection &s){
	EXCEPTION_SETUP("void NXFieldH5Implementation::setSelection(const Selection &s)");

	hsize_t *offset=NULL;
	hsize_t *stride = NULL;
	hsize_t *count = NULL;

	//allocate memory

}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::resetSelection(){
	EXCEPTION_SETUP("void NXFieldH5Implementation::resetSelection()");

	if(H5Iis_valid(_space_id)) H5Sselect_none(_space_id);
}


//end of namespace
}
}
}

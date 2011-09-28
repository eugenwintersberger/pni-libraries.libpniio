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
	EXCEPTION_SETUP("NXFieldH5Implementation::NXFieldH5Implementation():NXObjectH5Implementation()");
	_space_id = 0;
	_type_id = 0;
	_mem_space = 0;
	//we can always create a new property list which will be used as a central
	//storage for all kind of options.
	_creation_plist = H5Pcreate(H5P_DATASET_CREATE);
	_lcreate_plist = H5Pcreate(H5P_LINK_CREATE);
	H5Pset_create_intermediate_group(_lcreate_plist,1);
}

//------------------------------------------------------------------------------
NXFieldH5Implementation::~NXFieldH5Implementation() {
	close();
	_space_shape.setRank(0);
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
			_mem_space = H5Scopy(_space_id);
			H5Utilities::DataSpace2ArrayShape(_space_id,_space_shape);

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
			_space_shape.setRank(0);
			_mem_space = 0;
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
	_mem_space = H5Scopy(_space_id);
	H5Utilities::DataSpace2ArrayShape(_space_id,_space_shape);
	_creation_plist = H5Dget_create_plist(id);
	_lcreate_plist = H5Pcreate(H5P_LINK_CREATE);
	H5Pset_create_intermediate_group(_lcreate_plist,1);
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::close(){
	if(H5Iis_valid(_space_id)) H5Sclose(_space_id);
	if(H5Iis_valid(_type_id)) H5Tclose(_type_id);
	if(H5Iis_valid(_creation_plist)) H5Pclose(_creation_plist);
	if(H5Iis_valid(_lcreate_plist)) H5Pclose(_lcreate_plist);
	NXObjectH5Implementation::close();
	_space_shape.setRank(0);
}

//------------------------------------------------------------------------------
void NXFieldH5Implementation::write(const void *ptr){
	EXCEPTION_SETUP("void NXFieldH5Implementation::write(const void *ptr)");
	herr_t err;

	err = H5Dwrite(getId(),_type_id,_mem_space,_space_id,H5P_DEFAULT,ptr);
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

	err = H5Dread(getId(),_type_id,_mem_space,_space_id,H5P_DEFAULT,ptr);
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error reading data from field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
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
void NXFieldH5Implementation::getShape(ArrayShape &s) const{
	s = _space_shape;
}

const ArrayShape &NXFieldH5Implementation::getShape() const {
	return _space_shape;
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
void NXFieldH5Implementation::setDataSpace(const ArrayShape &s){
	EXCEPTION_SETUP("void NXFieldH5Implementation::setDataSpace(const ArrayShape &s)");

	int r = s.getRank();
	hsize_t *d = NULL;   //actual dimensions
	d = new hsize_t[r];
	if(d == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for data space dimensions!");
		EXCEPTION_THROW();
	}

	hsize_t *md = NULL; //maximum dimensions
	md = new hsize_t[r];
	if(d == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for data space maximum dimensions!");
		EXCEPTION_THROW();
	}

	for(UInt32 i=0;i<r;i++){
		d[i] = s.getDimension(i);
		md[i] = d[i];
	}
	//set the first dimension to unlimited
	md[0] = H5S_UNLIMITED;

	if(H5Iis_valid(_space_id)) H5Tclose(_space_id);

	_space_id = H5Screate_simple(r,d,md);
	if(_space_id < 0){
		EXCEPTION_INIT(H5DataSpaceError,"Cannot create simple data-space!");
		EXCEPTION_THROW();
	}

	//finally we need to set the chunk size

	if((H5Pset_layout(_creation_plist,H5D_CHUNKED))<0){
		EXCEPTION_INIT(H5PropertyListError,"Cannot set field layout to chunked!");
		EXCEPTION_THROW();
	}

	d[0] = 1;
	if((H5Pset_chunk(_creation_plist,r,d))<0){
		EXCEPTION_INIT(H5PropertyListError,"Cannot set chunk size!");
		EXCEPTION_THROW();
	}

	if(d!=NULL) delete [] d;
	if(md!=NULL) delete [] md;

	if(H5Iis_valid(_mem_space)) H5Sclose(_mem_space);
	_mem_space = H5Tcopy(_space_id);
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

	if(H5Iis_valid(_mem_space)) H5Sclose(_mem_space);
	_mem_space = H5Scopy(_mem_space);
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


void NXFieldH5Implementation::resetSelection(){
	EXCEPTION_SETUP("void NXFieldH5Implementation::resetSelection()");

	if(H5Iis_valid(_mem_space)) H5Sclose(_mem_space);
	_mem_space = H5Scopy(_space_id);

	//reset the selection from the data space of the field
	H5Sselect_none(_space_id);
}

void NXFieldH5Implementation::resize(const UInt64 &i){

}


//end of namespace
}
}
}

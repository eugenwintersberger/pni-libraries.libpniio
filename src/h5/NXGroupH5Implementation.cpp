/*
 * NXGroupH5Implementation.cpp
 *
 *  Created on: Jul 1, 2011
 *      Author: eugen
 */

extern "C"{
#include <hdf5.h>
}

#include <pni/utils/Exceptions.hpp>

#include "H5Exceptions.hpp"

#include "NXGroupH5Implementation.hpp"
#include "H5TypeFactory.hpp"

namespace pni{
namespace nx{
namespace h5{


NXGroupH5Implementation::NXGroupH5Implementation()
                        :NXObjectH5Implementation(){
	_id = 0;
	_gcreate_plist = H5Pcreate(H5P_LINK_CREATE);
	H5Pset_create_intermediate_group(_gcreate_plist,1);
}

NXGroupH5Implementation::NXGroupH5Implementation(const NXGroupH5Implementation &o){
	EXCEPTION_SETUP("NXGroupH5Implementation::NXGroupH5Implementation(const "
			        "NXGroupH5Implementation &o)");
	//the name of the object and its parent ID can be simply copied
	_name = o._name;
	_pid = o._pid;
	//need to solve the copy problem
	if(o._id == 0){
		_id = 0;
	}else{
		//we need to create a new handle to the group object refered to by
		_id = H5Gopen2(o._pid,o._name.c_str(),H5P_DEFAULT);
		if(_id<0){
			EXCEPTION_INIT(H5GroupError,"Cannot open group ["+o._name+"]!");
			EXCEPTION_THROW();
		}
	}
	_gcreate_plist = H5Pcopy(o._gcreate_plist);
}

NXGroupH5Implementation::~NXGroupH5Implementation() {
	//close a Group if it is no longer needed
	//clearly the parent ID must not be closed since it might be hold
	//by a different object
	if(H5Iis_valid(_id)) H5Gclose(_id);
	if(H5Iis_valid(_gcreate_plist)) H5Pclose(_gcreate_plist);
}

NXGroupH5Implementation &
NXGroupH5Implementation::operator=(const NXGroupH5Implementation &o){
	EXCEPTION_SETUP("NXGroupH5Implementation::operator=(const "
					"NXGroupH5Implementation &o)");
	if (this != &o){
		//here we have somehow the same problem as with the copy constructor

		if(o._id != 0){
			this->_id = H5Gopen2(o._pid,o._name.c_str(),H5P_DEFAULT);
			if(this->_id<0){
				EXCEPTION_INIT(H5GroupError,"Cannot open group ["+o._name+"]!");
				EXCEPTION_THROW();
			}
		}else{
			this->_id = 0;
		}

		this->_name = o._name;
		this->_pid = o._pid;
		this->_gcreate_plist = H5Pcopy(o._gcreate_plist);
		//need to do some error checking here
	}

	return *this;
}

void NXGroupH5Implementation::createGroup(const char *n,
		NXGroupH5Implementation &imp) {
	EXCEPTION_SETUP("void NXGroupH5Implementation::createGroup(const char *n,"
					"NXGroupH5Implementation &imp)");
	//we have to create a new r
	imp._pid = _id;
	imp._name = String(n);
	imp._id = H5Gcreate2(_id, n, _gcreate_plist, H5P_DEFAULT, H5P_DEFAULT);
	if(imp._id<0){
		EXCEPTION_INIT(H5GroupError,"Cannot create group "+String(n)+"!");
		EXCEPTION_THROW();
	}
	//check here for errors
}

void NXGroupH5Implementation::openGroup(const char *n,
		                                NXGroupH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::openGroup(const char *n,"
			        "NXGroupH5Implementation &imp)");
	imp._pid = _id;
	imp._name = pni::utils::String(n);
	imp._id = H5Gopen2(_id,n,H5P_DEFAULT);
	if(imp._id<0){
		EXCEPTION_INIT(H5GroupError,"Cannot open group ["+String(n)+"]!");
		EXCEPTION_THROW();
	}

}
void NXGroupH5Implementation::createField(const char *n, PNITypeID tid,
		                                  const ArrayShape &s,
										  NXFieldH5Implementation &imp){

	createField(n,tid,s.getRank(),s.getDimensions(),imp);
}

void NXGroupH5Implementation::createField(const char *n, PNITypeID tid,
		                                  const ArrayShape::sptr s,
		                                  NXFieldH5Implementation &imp){

	createField(n,tid,s->getRank(),s->getDimensions(),imp);
}

void NXGroupH5Implementation::openField(const char *n,
		                                NXFieldH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::openField(const char *n,"
			        "NXFieldH5Implementation &imp)");
	imp._pid = _id;
	imp._id = H5Dopen2(_id,n,H5P_DEFAULT);
	if(imp._id<0){
		EXCEPTION_INIT(H5DataSetError,"Cannot open HDF5 dataset ["+String(n)+"]!");
		imp._pid = 0;
		EXCEPTION_THROW();
	}

	//need to fetch the name
	imp._name = String(n);

	imp._type_id = H5Dget_type(imp._id);
	if(imp._type_id<0){
		EXCEPTION_INIT(H5DataTypeError,"Cannot obtain data type from dataset ["+String(n)+"]!");
		imp._name.clear();
		imp._pid = 0;
		H5Dclose(imp._id);
		EXCEPTION_THROW();
	}

	imp._space_id = H5Dget_space(imp._id);
	if(imp._space_id < 0){
		EXCEPTION_INIT(H5DataSpaceError,"Cannot obtain data space from dataset ["+String(n)+"]!");
		imp._name.clear();
		imp._pid = 0;
		H5Dclose(imp._id);
		H5Tclose(imp._type_id);
		EXCEPTION_THROW();
	}

}

void NXGroupH5Implementation::createField(const char *n, PNITypeID tid,
		                                  UInt32 rank, const UInt32 *dims,
			                              NXFieldH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::createField(const char *n, "
			        "PNITypeID tid,UInt32 rank, const UInt32 *dims,"
			        "NXFieldH5Implementation &imp)");
	hsize_t *ldims;


	imp._type_id = H5TFactory.createTypeFromID(tid);

	ldims = (hsize_t *)malloc(sizeof(hsize_t)*rank);
	if(ldims == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for dimension buffer!");
		H5Tclose(imp._type_id);
		EXCEPTION_THROW();
	}
	for(UInt64 i=0;i<rank;i++) ldims[i] = dims[i];

	imp._space_id = H5Screate_simple(rank,ldims,NULL);
	free(ldims);
	if(imp._space_id < 0){
		EXCEPTION_INIT(H5DataSpaceError,"Error creating data space for field ["+String(n)+"]!");
		H5Tclose(imp._type_id);
		EXCEPTION_THROW();
	}

	imp._id = H5Dcreate2(_id,n,imp._type_id,imp._space_id,H5P_DEFAULT,
			            H5P_DEFAULT,H5P_DEFAULT);
	if(imp._id < 0){
		EXCEPTION_INIT(H5DataSetError,"Error creating dataset for field ["+String(n)+"]!");
		H5Tclose(imp._type_id);
		H5Sclose(imp._space_id);
		EXCEPTION_THROW();
	}

	imp._pid = _id;
	imp._name = String(n);
}

void NXGroupH5Implementation::createField(const char *n, PNITypeID tid,
		                                  NXFieldH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::createField(const char *n, "
			        "PNITypeID tid,NXFieldH5Implementation &imp)");
	imp._type_id = H5TFactory.createTypeFromID(tid);

	imp._space_id = H5Screate(H5S_SCALAR);
	if(imp._space_id<0){
		EXCEPTION_INIT(H5DataSpaceError,"Error creating data space for field ["+String(n)+"]!");
		H5Tclose(imp._type_id);
		EXCEPTION_THROW();
	}

	imp._id = H5Dcreate2(_id,n,imp._type_id,imp._space_id,H5P_DEFAULT,
			             H5P_DEFAULT,H5P_DEFAULT);
	if(imp._id < 0){
		EXCEPTION_INIT(H5DataSetError,"Error creating data set for field ["+String(n)+"]!");
		H5Tclose(imp._type_id);
		H5Sclose(imp._space_id);
		EXCEPTION_THROW();
	}

	imp._pid = _id;
	imp._name = String(n);
}

void NXGroupH5Implementation::createStringField(const char *n, UInt64 size,
		                                        NXFieldH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::createStringField("
			        "const char *n, UInt64 size,NXFieldH5Implementation &imp)");

	imp._type_id = H5TFactory.createStringType(size);

	imp._space_id = H5Screate(H5S_SCALAR);
	if(imp._space_id<0){
		EXCEPTION_INIT(H5DataSpaceError,"Cannot create data space for field ["+String(n)+"]!");
		H5Tclose(imp._type_id);
		EXCEPTION_THROW();
	}

	imp._id = H5Dcreate2(_id,n,imp._type_id,imp._space_id,H5P_DEFAULT,
			             H5P_DEFAULT,H5P_DEFAULT);
	if(imp._id<0){
		EXCEPTION_INIT(H5DataSetError,"Cannot create data set for fiel ["+String(n)+"]!");
		H5Tclose(imp._type_id);
		H5Sclose(imp._space_id);
		EXCEPTION_THROW();
	}

	imp._pid = _id;
	imp._name = String(n);

}


void NXGroupH5Implementation::close(){
	if(H5Iis_valid(_id)) H5Gclose(_id);
}

//end of namespace
}
}
}

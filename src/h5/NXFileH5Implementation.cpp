/*
 * NXFileH5Implementation.cpp
 *
 *  Created on: Jun 30, 2011
 *      Author: eugen
 */

#include "NXFileH5Implementation.hpp"
#include "H5Exceptions.hpp"

namespace pni{
namespace nx{
namespace h5{


NXFileH5Implementation::NXFileH5Implementation() :NXGroupH5Implementation(){
	EXCEPTION_SETUP("NXFileH5Implementation::NXFileH5Implementation()");
}

NXFileH5Implementation::~NXFileH5Implementation() {
	close();
}

void NXFileH5Implementation::close(){
	//check for open objects in the file

	hid_t id = getId();

	if(H5Iis_valid(id)){
		//std::cerr<<"Open files:      "<<H5Fget_obj_count(_id,H5F_OBJ_FILE)<<std::endl;
		//std::cerr<<"Open data sets:  "<<H5Fget_obj_count(_id,H5F_OBJ_DATASET)<<std::endl;
		//std::cerr<<"Open groups:     "<<H5Fget_obj_count(_id,H5F_OBJ_GROUP)<<std::endl;
		//std::cerr<<"Open data type:  "<<H5Fget_obj_count(_id,H5F_OBJ_DATATYPE)<<std::endl;
		//std::cerr<<"Open attributes: "<<H5Fget_obj_count(_id,H5F_OBJ_ATTR)<<std::endl;
		H5Fflush(id,H5F_SCOPE_GLOBAL);
		H5Fclose(id);
	}
}

void NXFileH5Implementation::open(const char *n,bool readonly){
	EXCEPTION_SETUP("void NXFileH5Implementation::open(const char *n,bool readonly)");

	hid_t id;

	//check if the file is a valid HDF5 file
	if(!H5Fis_hdf5(n)){
		EXCEPTION_INIT(H5FileError,"File ["+String(n)+"] is not an HDF5 file!");
		EXCEPTION_THROW();
	}

	hid_t acc_plist = H5Pcreate(H5P_FILE_ACCESS);
	if(acc_plist<0){
		EXCEPTION_INIT(H5PropertyListError,"Cannot create file access property list for file ["+String(n)+"]!");
		close();
		EXCEPTION_THROW();
	}

	//open the file in the appropriate mode
	if(readonly){
		id = H5Fopen(n,H5F_ACC_RDONLY,acc_plist);
		if(id<0){
			EXCEPTION_INIT(H5FileError,"Error opening file "+String(n)+" in read only mode!");
			EXCEPTION_THROW();
		}
	}else{
		id = H5Fopen(n,H5F_ACC_RDWR,acc_plist);
		if(id<0){
			EXCEPTION_INIT(H5FileError,"Error opening file "+String(n)+" in read/write mode!");
			EXCEPTION_THROW();
		}
	}

	setId(id);

}

void NXFileH5Implementation::create(const char *n,bool overwrite,UInt64 ssize){
	EXCEPTION_SETUP("void NXFileH5Implementation::create(const char *n,bool overwrite)");
	hid_t id;

	//create property lists for file creation an access
	hid_t create_plist = H5Pcreate(H5P_FILE_CREATE);
	if(create_plist<0){
		EXCEPTION_INIT(H5PropertyListError,"Cannot create file creation property list for file ["+String(n)+"]!");
		EXCEPTION_THROW();
	}

	hid_t acc_plist = H5Pcreate(H5P_FILE_ACCESS);
	if(acc_plist<0){
		EXCEPTION_INIT(H5PropertyListError,"Cannot create file access property list for file ["+String(n)+"]!");
		close();
		EXCEPTION_THROW();
	}

	if(ssize > 0){
		//enable splitting
		H5Pset_fapl_family(acc_plist,ssize*1024*1024,H5P_DEFAULT);
	}

	if(overwrite){
		id = H5Fcreate(n,H5F_ACC_TRUNC,create_plist,acc_plist);
		if(id<0){
			EXCEPTION_INIT(H5FileError,"Error create file "+String(n)+" in overwrite mode!");
			close();
			EXCEPTION_THROW()
		}
	}else{
		id = H5Fcreate(n,H5F_ACC_EXCL,create_plist,acc_plist);
		if(id<0){
			EXCEPTION_INIT(H5FileError,"Error create file "+String(n)+" file most probably already exists - use overwrite!");
			close();
			EXCEPTION_THROW();
		}
	}

	setId(id);
}

void NXFileH5Implementation::flush(){
	H5Fflush(getId(),H5F_SCOPE_LOCAL);
}

//end of namespace
}
}
}


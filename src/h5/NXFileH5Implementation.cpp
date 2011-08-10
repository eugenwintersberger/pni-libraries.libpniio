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


NXFileH5Implementation::NXFileH5Implementation() {
	EXCEPTION_SETUP("NXFileH5Implementation::NXFileH5Implementation()");
	_id = 0;
	_pid = 0;


}

NXFileH5Implementation::~NXFileH5Implementation() {
	close();
}

void NXFileH5Implementation::close(){
	//check for open objects in the file


	//close the file
	if(H5Iis_valid(_create_plist)) H5Pclose(_create_plist);
	if(H5Iis_valid(_acc_plist)) H5Pclose(_acc_plist);

	if(H5Iis_valid(_id)){
		//std::cerr<<"Open files:      "<<H5Fget_obj_count(_id,H5F_OBJ_FILE)<<std::endl;
		//std::cerr<<"Open data sets:  "<<H5Fget_obj_count(_id,H5F_OBJ_DATASET)<<std::endl;
		//std::cerr<<"Open groups:     "<<H5Fget_obj_count(_id,H5F_OBJ_GROUP)<<std::endl;
		//std::cerr<<"Open data type:  "<<H5Fget_obj_count(_id,H5F_OBJ_DATATYPE)<<std::endl;
		//std::cerr<<"Open attributes: "<<H5Fget_obj_count(_id,H5F_OBJ_ATTR)<<std::endl;
		H5Fflush(_id,H5F_SCOPE_GLOBAL);
		H5Fclose(_id);
	}
}

void NXFileH5Implementation::open(const char *n,bool readonly){
	EXCEPTION_SETUP("void NXFileH5Implementation::open(const char *n,bool readonly)");

	//check if the file is a valid HDF5 file
	if(!H5Fis_hdf5(n)){
		EXCEPTION_INIT(H5FileError,"File ["+String(n)+" is not an HDF5 file!");
		EXCEPTION_THROW();
	}

	_acc_plist = H5Pcreate(H5P_FILE_ACCESS);
	if(_acc_plist<0){
		EXCEPTION_INIT(H5PropertyListError,"Cannot create file access property list for file ["+String(n)+"]!");
		close();
		EXCEPTION_THROW();
	}

	//open the file in the appropriate mode
	if(readonly){
		_id = H5Fopen(n,H5F_ACC_RDONLY,_acc_plist);
		if(_id<0){
			EXCEPTION_INIT(H5FileError,"Error opening file "+String(n)+" in read only mode!");
			EXCEPTION_THROW();
		}
	}else{
		_id = H5Fopen(n,H5F_ACC_RDWR,_acc_plist);
		if(_id<0){
			EXCEPTION_INIT(H5FileError,"Error opening file "+String(n)+" in read/write mode!");
			EXCEPTION_THROW();
		}
	}


	_create_plist = H5Fget_create_plist(_id);
	if(_create_plist<0){
		EXCEPTION_INIT(H5PropertyListError,"Cannot obtain creation property list from file ["+String(n)+"]!");
		close();
		EXCEPTION_THROW();
	}

}

void NXFileH5Implementation::create(const char *n,bool overwrite){
	EXCEPTION_SETUP("void NXFileH5Implementation::create(const char *n,bool overwrite)");

	//create property lists for file creation an access
	_create_plist = H5Pcreate(H5P_FILE_CREATE);
	if(_create_plist<0){
		EXCEPTION_INIT(H5PropertyListError,"Cannot create file creation property list for file ["+String(n)+"]!");
		EXCEPTION_THROW();
	}
	_acc_plist = H5Pcreate(H5P_FILE_ACCESS);
	if(_acc_plist<0){
		EXCEPTION_INIT(H5PropertyListError,"Cannot create file access property list for file ["+String(n)+"]!");
		close();
		EXCEPTION_THROW();
	}

	if(overwrite){
		_id = H5Fcreate(n,H5F_ACC_TRUNC,_create_plist,_acc_plist);
		if(_id<0){
			EXCEPTION_INIT(H5FileError,"Error create file "+String(n)+" in overwrite mode!");
			close();
			EXCEPTION_THROW()
		}
	}else{
		_id = H5Fcreate(n,H5F_ACC_EXCL,_create_plist,_acc_plist);
		if(_id<0){
			EXCEPTION_INIT(H5FileError,"Error create file "+String(n)+" file most probably already exists - use overwrite!");
			close();
			EXCEPTION_THROW();
		}
	}
}

void NXFileH5Implementation::flush(){
	H5Fflush(_id,H5F_SCOPE_LOCAL);
}

//end of namespace
}
}
}


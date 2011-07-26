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
	H5open();
	_id = 0;
	_pid = 0;
	//create property lists for file creation an access
	_create_plist = H5Pcreate(H5P_FILE_CREATE);
	_acc_plist = H5Pcreate(H5P_FILE_ACCESS);

}

NXFileH5Implementation::~NXFileH5Implementation() {
	//close the file if neccessary
	//we need some check here if the file is still open
	//in other words if close() has been already called or not
	//H5Fclose(_id);
	//close the property lists when implementation object
	//is destroyed
	close();
	if(H5Iis_valid(_create_plist)) H5Pclose(_create_plist);
	if(H5Iis_valid(_acc_plist)) H5Pclose(_acc_plist);
}

void NXFileH5Implementation::close(){
	//close the file
	if(H5Iis_valid(_id)){
		H5Fflush(_id,H5F_SCOPE_GLOBAL);
		H5Fclose(_id);
	}
}

void NXFileH5Implementation::open(const char *n,bool readonly){
	static String ExIssuer = "void NXFileH5Implementation::open(const char *n,bool readonly)";
	String ExDescription;
	//should first add a check here if the file is realy in HDF5 format

	//open the file in the appropriate mode
	if(readonly){
		_id = H5Fopen(n,H5F_ACC_RDONLY,_acc_plist);
	}else{
		_id = H5Fopen(n,H5F_ACC_RDWR,_acc_plist);
	}
	//now we have to set the _id to the root group


}

void NXFileH5Implementation::create(const char *n,bool overwrite){
	static String ExIssuer="void NXFileH5Implementation::create(const char *n,bool overwrite)";
	String ExDescription;

	if(overwrite){
		_id = H5Fcreate(n,H5F_ACC_TRUNC,_create_plist,_acc_plist);
	}else{
		_id = H5Fcreate(n,H5F_ACC_EXCL,_create_plist,_acc_plist);
	}
	//check here for errors

	if (_id < 0){
		//have to handle here the HDF5 error stack
		H5FileException e;
		e.setIssuer(ExIssuer);
		ExDescription = "Error opening file "+String(n)+"!";
		e.setDescription(ExDescription);
		throw e;
	}

}

//end of namespace
}
}
}


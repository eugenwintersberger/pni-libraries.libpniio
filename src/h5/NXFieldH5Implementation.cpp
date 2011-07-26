/*
 * NXFieldH5Implementation.cpp
 *
 *  Created on: Jul 3, 2011
 *      Author: eugen
 */

#include "NXFieldH5Implementation.hpp"
#include "H5Exceptions.hpp"

namespace nx{
namespace h5{

using namespace nx::h5;

NXFieldH5Implementation::NXFieldH5Implementation() {
	_id = 0;
	_space_id = 0;
	_type_id = 0;
}

NXFieldH5Implementation::NXFieldH5Implementation(const NXFieldH5Implementation &i){
	static String ExIssuer = "NXFieldH5Implementation::NXFieldH5Implementation(const NXFieldH5Implementation &i)";
	String ExDescription;
	if(i._id != 0){
		_id = H5Dopen2(i._pid,i._name.c_str(),H5P_DEFAULT);
		if(_id<0){
			ExDescription = "Error opening data-set ["+i._name+"] in copy constructor!";
			H5DataSetException e(ExIssuer,ExDescription);
			std::cerr<<e<<std::endl;
			throw e;
		}
	}else{
		_id = 0;
	}

	_name = i._name;
	_pid = i._pid;
	_space_id = H5Scopy(i._space_id);
	if(_space_id<0){
		ExDescription = "Error copying data-space for data-set ["+i._name+"] in copy constructor!";
		H5DataSpaceException e(ExIssuer,ExDescription);
		H5Dclose(_id);
		std::cerr<<e<<std::endl;
		throw e;
	}
	_type_id = H5Tcopy(i._type_id);
	if(_type_id < 0){
		ExDescription = "Error copying data-type for data-set ["+i._name+"] in copy constructor!";
		H5DataTypeException e(ExIssuer,ExDescription);
		H5Dclose(_id);
		H5Sclose(_space_id);
		std::cerr<<e<<std::endl;
		throw e;
	}
}

NXFieldH5Implementation::~NXFieldH5Implementation() {
	_pid = 0;
	_name.clear();
	close();
}

NXFieldH5Implementation &NXFieldH5Implementation::operator=(const NXFieldH5Implementation &o){
	static String ExIssuer = "NXFieldH5Implementation &NXFieldH5Implementation::operator=(const NXFieldH5Implementation &o)";
	String ExDescription;
	if ( this != &o ){
		_pid = o._pid;
		_name = o._name;

		_id = H5Dopen2(o._pid,o._name.c_str(),H5P_DEFAULT);
		if(_id < 0){
			ExDescription = "Error opening data-set ["+o._name+"] in assignment operator!";
			H5DataSetException e(ExIssuer,ExDescription);
			std::cerr<<e<<std::endl;
			throw e;
		}
		_space_id = H5Scopy(o._space_id);
		if(_space_id < 0){
			ExDescription = "Error copying data-space for data-set ["+o._name+"] in assignment operator!";
			H5DataSpaceException e(ExIssuer,ExDescription);
			H5Dclose(_id);
			std::cerr<<e<<std::endl;
			throw e;
		}
		_type_id = H5Tcopy(o._type_id);
		if(_type_id < 0){
			ExDescription = "Error copying data-type for data-set ["+o._name+"] in assignment operator!";
			H5DataTypeException e(ExIssuer,ExDescription);
			H5Sclose(_space_id);
			H5Dclose(_id);
			std::cerr<<e<<std::endl;
			throw e;
		}
	}

	return *this;
}

void NXFieldH5Implementation::close(){
	if(H5Iis_valid(_id)) H5Dclose(_id);
	if(H5Iis_valid(_space_id)) H5Sclose(_space_id);
	if(H5Iis_valid(_type_id)) H5Tclose(_type_id);
}

void NXFieldH5Implementation::write(pni::utils::ScalarObject &s){
	static String ExIssuer = "void NXFieldH5Implementation::write(pni::utils::ScalarObject &s)";
	String ExDescription;
	herr_t err;

	err = H5Dwrite(_id,_type_id,H5S_ALL,H5S_ALL,H5P_DEFAULT,s.getVoidPtr());
	if(err<0){
		ExDescription = "Error writing data to field ["+_name+"]!";
		H5DataSetException e(ExIssuer,ExDescription);
		std::cerr<<e<<std::endl;
		throw e;
	}
}

void NXFieldH5Implementation::write(pni::utils::ArrayObject &s){
	static String ExIssuer = "void NXFieldH5Implementation::write(pni::utils::ArrayObject &s)";
	String ExDescription;
	herr_t err;

	err = H5Dwrite(_id,_type_id,H5S_ALL,H5S_ALL,H5P_DEFAULT,s.getBuffer()->getVoidPtr());
	if(err<0){
		ExDescription = "Error writing data to field ["+_name+"]!";
		H5DataSetException e(ExIssuer,ExDescription);
		std::cerr<<e<<std::endl;
		throw e;
	}
}

void NXFieldH5Implementation::write(pni::utils::String &s){
	static String ExIssuer = "void NXFieldH5Implementation::write(pni::utils::String &s)";
	String ExDescription;
	herr_t err;

	err = H5Dwrite(_id,_type_id,H5S_ALL,H5S_ALL,H5P_DEFAULT,s.c_str());
	if(err<0){
		ExDescription = "Error writing data to field ["+_name+"]!";
		H5DataSetException e(ExIssuer,ExDescription);
		std::cerr<<e<<std::endl;
		throw e;
	}
}

void NXFieldH5Implementation::read(pni::utils::ScalarObject &s){
	static String ExIssuer = "void NXFieldH5Implementation::read(pni::utils::ScalarObject &s)";
	String ExDescription;
	herr_t err;

	err = H5Dread(_id,_type_id,H5S_ALL,H5S_ALL,H5P_DEFAULT,s.getVoidPtr());
	if(err<0){
		ExDescription = "Error reading data from field ["+_name+"]!";
		H5DataSetException e(ExIssuer,ExDescription);
		std::cerr<<e<<std::endl;
		throw e;
	}
}

void NXFieldH5Implementation::read(pni::utils::ArrayObject &s){
	static String ExIssuer = "void NXFieldH5Implementation::read(pni::utils::ArrayObject &s)";
	String ExDescription;
	herr_t err;

	err = H5Dread(_id,_type_id,H5S_ALL,H5S_ALL,H5P_DEFAULT,s.getBuffer()->getVoidPtr());
	if(err<0){
		ExDescription = "Error reading data from field ["+_name+"]!";
		H5DataSetException e(ExIssuer,ExDescription);
		std::cerr<<e<<std::endl;
		throw e;
	}
}

void NXFieldH5Implementation::read(pni::utils::String &s){
	static String ExIssuer = "void NXFieldH5Implementation::read(pni::utils::String &s)";
	String ExDescription;
	herr_t err;

	//clear previous string data and resize the string buffer
	s.clear();
	s.resize(H5Tget_size(_type_id));

	err = H5Dread(_id,_type_id,H5S_ALL,H5S_ALL,H5P_DEFAULT,(void *)s.c_str());
	if(err<0){
		ExDescription = "Error reading data from field ["+_name+"]!";
		H5DataSetException e(ExIssuer,ExDescription);
		std::cerr<<e<<std::endl;
		throw e;
	}
}

pni::utils::UInt32 NXFieldH5Implementation::getRank(){



}

pni::utils::UInt32 NXFieldH5Implementation::getDimension(pni::utils::UInt32 i){
	return 0;
}


//end of namespace
}
}

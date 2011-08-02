/*
 * H5Error.cpp
 *
 *  Created on: Aug 2, 2011
 *      Author: eugen
 */

extern "C"{
#include <hdf5.h>
}

#include "H5ErrorStack.hpp"

namespace pni{
namespace nx{
namespace h5{


H5Error::H5Error(){

}

H5Error::H5Error(const H5Error &e){
	_class_id = e._class_id;
	_class_name = e._class_name;
	_major_number = e._major_number;
	_minor_number = e._minor_number;
	_file_name = e._file_name;
	_func_name = e._func_name;
	_description = e._description;
	_minor_message = e._minor_message;
	_major_message = e._major_message;
}

H5Error::~H5Error(){

}

H5Error &H5Error::operator=(const H5Error &e){
	if(this != &e){
		_class_id = e._class_id;
		_class_name = e._class_name;
		_major_number = e._major_number;
		_minor_number = e._minor_number;
		_file_name = e._file_name;
		_func_name = e._func_name;
		_description = e._description;
		_minor_message = e._minor_message;
		_major_message = e._major_message;
	}

	return *this;
}

hid_t H5Error::getClassId() const{
	return _class_id;
}

void H5Error::setClassId(hid_t id){
	char *ptr;
	size_t buffer_size;

	//set the class id
	_class_id = id;
	//determine the class name from the class id

	buffer_size = H5Eget_class_name(id,NULL,1)+1;
	ptr = new char[buffer_size];
	H5Eget_class_name(id,ptr,buffer_size);
	_class_name = String(ptr);
	delete [] ptr;

}

hid_t H5Error::getMajorNumber() const{
	return _major_number;
}

void H5Error::setMajorNumber(hid_t v){
	char *ptr;
	size_t buffer_size;
	H5E_type_t msg_type;

	//set the major number
	_major_number = v;

	//get the major message from the error stack
	buffer_size = H5Eget_msg(v,&msg_type,NULL,1);
	if(buffer_size > 0){
		ptr = new char[buffer_size+1];
		H5Eget_msg(v,&msg_type,ptr,buffer_size+1);
		_major_message = String(ptr);
		delete [] ptr;
	}
}

hid_t H5Error::getMinorNumber() const{
	return _minor_number;
}

void H5Error::setMinorNumber(hid_t v){
	char *ptr;
	size_t buffer_size;
	H5E_type_t msg_type;

	//set the minor number
	_minor_number = v;

	//get the minor message
	buffer_size = H5Eget_msg(v,&msg_type,NULL,1);
	if(buffer_size > 0){
		ptr = new char[buffer_size+1];
		H5Eget_msg(v,&msg_type,ptr,buffer_size+1);
		_minor_message = String(ptr);
		delete [] ptr;
	}
}

String H5Error::getFileName() const{
	return _file_name;
}

void H5Error::setFileName(const String &n){
	_file_name = n;
}

String H5Error::getFuncName() const{
	return _func_name;
}

void H5Error::setFuncName(const String &n){
	_func_name = n;
}

String H5Error::getDescription() const{
	return _description;
}

void H5Error::setDescription(const String &n){
	_description = n;
}


String H5Error::getMajorMessage() const{
	return _major_message;
}


String H5Error::getMinorMessage() const{
	return _minor_message;
}



std::ostream &operator<<(std::ostream &o,const H5Error &e){
	o<<e._class_name<<" - Error in: "<<e._func_name<<" ("<<e._file_name<<")"<<std::endl;
	o<<e._description<<": "<<e._major_message<<" -- "<<e._minor_message<<std::endl;

	return o;
}

//end of namespace
}
}
}

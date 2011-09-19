/*
 * NXObjectH5Implementation.cpp
 *
 *  Created on: Jul 1, 2011
 *      Author: eugen
 */

#include "NXObjectH5Implementation.hpp"
#include "H5TypeFactory.hpp"
#include "H5Exceptions.hpp"
#include "H5Utilities.hpp"

#include <pni/utils/Exceptions.hpp>

namespace pni{
namespace nx{
namespace h5{

using namespace pni::utils;

NXObjectH5Implementation::NXObjectH5Implementation() {
	_id = 0;
	_pid = 0;
}

NXObjectH5Implementation::~NXObjectH5Implementation() {
}

NXObjectH5Implementation &NXObjectH5Implementation::operator=(const NXObjectH5Implementation &o){
	//the situation is here slightly different from that of the copy constructor
	//Here we have two existing objects.

	if(this != &o){
		//do nothing here.

		//MUST BE IMPLEMENTED BY THE CONCRETE CLASSES
	}

	return *this;
}

void NXObjectH5Implementation::_create_and_write_attribute(hid_t pid,const char *n,
		                       hid_t type_id,hid_t space_id,const void *ptr){
	EXCEPTION_SETUP("void NXObjectH5Implementation::"
			          "_create_and_write_attribute(hid_t pid,char *n,"
			          "hid_t type_id,hid_t space_id,void *ptr)");
	hid_t aid; //attribute handler

	//create the attribute and check for errors
	aid = H5Acreate2(pid,n,type_id,space_id,H5P_DEFAULT,H5P_DEFAULT);
	if(aid<0){
		EXCEPTION_INIT(H5AttributeError,"Error creating array attribute ["+String(n)+"]!");
		H5Sclose(space_id);
		EXCEPTION_THROW();
	}

	//write data and check for errors
	if((H5Awrite(aid,type_id,ptr))<0){
		EXCEPTION_INIT(H5AttributeError,"Error writing data to array attribute ["+String(n)+"]!");
		H5Aclose(aid);
		H5Sclose(space_id);
		EXCEPTION_THROW();
	}

	H5Aclose(aid);

}

void NXObjectH5Implementation::_open_attribute(hid_t pid,const char *n,
		                       hid_t &attr_id,hid_t &type_id,hid_t &space_id){
	EXCEPTION_SETUP("void NXObjectH5Implementation::"
		 			  "_open_attribute(hid_t pid,const char *n,"
					  "hid_t &attr_id,hid_t &type_id,hid_t &space_id)");
	attr_id = H5Aopen(_id,n,H5P_DEFAULT);
	if(attr_id<0){
		EXCEPTION_INIT(H5AttributeError,"Error opening array attribute ["+String(n)+"]!");
		EXCEPTION_THROW();
	}

	space_id= H5Aget_space(attr_id);
	if(space_id<0){
		EXCEPTION_INIT(H5DataSpaceError,"Error opening data-space for array attribute ["+String(n)+"]!");
		H5Aclose(attr_id);
		EXCEPTION_THROW();
	}
	type_id = H5Aget_type(attr_id);
	if(type_id<0){
		EXCEPTION_INIT(H5DataTypeError,"Error opening data-type for array attribute ["+String(n)+"]!");
		H5Sclose(space_id);
		H5Aclose(attr_id);
		EXCEPTION_THROW();
	}
}

void NXObjectH5Implementation::setAttribute(const char *n,ArrayObject &a){
	EXCEPTION_SETUP("void NXObjectH5Implementation::setAttribute(const char *n,ArrayObject &a)");
	hid_t tid;   //id of the data type
	hid_t setid; //id of the data set
	const ArrayShape &s = a.getShape();

	//determine the data type of the array object
	tid = H5TFactory.getTypeFromID(a.getTypeID());

	//create the dataspace
	H5Utilities::ArrayShape2DataSpace(s,setid);

	//create the attribute and write the data
	try{
		_create_and_write_attribute(_id,n,tid,setid,a.getBuffer().getVoidPtr());
	}catch(...){
		EXCEPTION_INIT(H5AttributeError,"Cannot create and write attribute "+String(n)+"!");
		EXCEPTION_THROW();
	}

	//close everything except the data type
	H5Sclose(setid);
}

void NXObjectH5Implementation::setAttribute(const char *n,ScalarObject &d){
	EXCEPTION_SETUP("void NXObjectH5Implementation::setAttribute(const char *n,ScalarObject &a)");
	hid_t tid;   //id of the data type
	hid_t setid; //id of the data set

	//determine the data type of the array object
	tid = H5TFactory.getTypeFromID(d.getTypeID());

	//create the dataspace
	setid = H5Screate(H5S_SCALAR);
	if(setid<0){
		EXCEPTION_INIT(H5DataSpaceError,"Error creating data-space for scalar attribute ["+String(n)+"]!");
		EXCEPTION_THROW();
	}

	//create and write attribute data
	try{
		_create_and_write_attribute(_id,n,tid,setid,d.getVoidPtr());
	}catch(...){
		EXCEPTION_INIT(H5AttributeError,"Cannot create and write attribute "+String(n)+"!");
		EXCEPTION_THROW();
	}

	//close everything except the data type
	H5Sclose(setid);
}


void NXObjectH5Implementation::setAttribute(const char *n,const String &s){
	EXCEPTION_SETUP("void NXObjectH5Implementation::setAttribute(const char *n,String &s)");
	hid_t tid;   //id of the data type
	hid_t setid; //id of the data set

	//determine the data type of the array object
	tid = H5TFactory.createStringType(s.size());

	//create the dataspace
	setid = H5Screate(H5S_SCALAR);
	if (setid < 0) {
		EXCEPTION_INIT(H5DataSpaceError,"Error creating data-space for string attribute ["+String(n)+"]!");
		EXCEPTION_THROW();
	}

	//create and write the attribute data
	try{
		_create_and_write_attribute(_id,n,tid,setid,(void *)s.c_str());
	}catch(...){
		EXCEPTION_INIT(H5AttributeError,"Cannot create and write attribute "+String(n)+"!");
		EXCEPTION_THROW();
	}

	//close everything except the data type
	H5Sclose(setid);
}

void NXObjectH5Implementation::getAttribute(const char *n,ArrayObject &a){
	EXCEPTION_SETUP("void NXObjectH5Implementation::getAttribute(const char *n,ArrayObject &a)");
	ArrayShape temp_shape;


	hid_t atid = 0;
	hid_t asid = 0;
	hid_t aid  = 0;

	try{
		_open_attribute(_id,n,aid,atid,asid);
	}catch(...){
		EXCEPTION_INIT(H5AttributeError,"Error opening attribute "+String(n)+" for reading!");
		EXCEPTION_THROW();
	}
	//need to do some error checking here

	H5Utilities::DataSpace2ArrayShape(asid,temp_shape);
	if((a.getShape().getSize()==0)||(temp_shape != a.getShape())){
		a.setShape(temp_shape);
		a.allocate();
	}

	//copy data to the array buffer
	if((H5Aread(aid,atid,(void *)a.getBuffer().getVoidPtr()))<0){
		EXCEPTION_INIT(H5DataSetError,"Error reading data from array attribute ["+String(n)+"]!");
		H5Tclose(atid);
		H5Sclose(asid);
		H5Aclose(aid);
		EXCEPTION_THROW();
	}

	//close everything
	H5Tclose(atid);
	H5Sclose(asid);
	H5Aclose(aid);

}

void NXObjectH5Implementation::getAttribute(const char *n,ScalarObject &s){
	EXCEPTION_SETUP("void NXObjectH5Implementation::getAttribute(const char *n,ScalarObject &a)");
	hid_t atid = 0;
	hid_t asid = 0;
	hid_t aid  = 0;

	try{
		_open_attribute(_id,n,aid,atid,asid);
	}catch(...){
		EXCEPTION_INIT(H5AttributeError,"Error opening attribute "+String(n)+" for reading!");
		EXCEPTION_THROW();
	}

	//copy data to the array buffer
	if((H5Aread(aid,atid,s.getVoidPtr()))<0){
		EXCEPTION_INIT(H5AttributeError,"Error reading data from scalar attribute ["+String(n)+"]!");
		//close data-space, attribute, and data-type
		H5Tclose(atid);
		H5Sclose(asid);
		H5Aclose(aid);
		EXCEPTION_THROW();
	}

	s.setName(String(n));

	//close everything
	H5Tclose(atid);
	H5Sclose(asid);
	H5Aclose(aid);
}

void NXObjectH5Implementation::getAttribute(const char *n,String &s){
	EXCEPTION_SETUP("void NXObjectH5Implementation::getAttribute(const char *n,String &s)");
	hid_t atid = 0;
	hid_t asid = 0;
	hid_t aid  = 0;

	try{
		_open_attribute(_id,n,aid,atid,asid);
	}catch(...){
		EXCEPTION_INIT(H5AttributeError,"Error opening attribute "+String(n)+" for reading!");
		EXCEPTION_THROW();
	}
	//need to do some error checking here

	//now we need to find out how much memory to allocate
	s.resize(H5Tget_size(atid));
	if((H5Aread(aid,atid,(void *)s.c_str()))<0){
		EXCEPTION_INIT(H5AttributeError,"Error reading data from string attribute ["+String(n)+"]!");
		H5Tclose(atid);
		H5Aclose(aid);
		H5Sclose(asid);
		EXCEPTION_THROW();
	}

	//close everything down
	H5Aclose(aid);
	H5Tclose(atid);
	H5Sclose(asid);
}

String NXObjectH5Implementation::getName() const{
	if(H5Iis_valid(_id)){
		//if the object has already been created return this value
		hsize_t bsize;
		String name;

		bsize = H5Iget_name(_id,NULL,1)+1;
		name.clear();
		name.resize(bsize);
		H5Iget_name(_id,(char*)name.c_str(),bsize);
		return name;
	}

	return String("");
}

void NXObjectH5Implementation::setParent(hid_t id){
	if(H5Iis_valid(id)){
		_pid = id;
	}
	//maybe I should raise an exception here
}

hid_t NXObjectH5Implementation::getParent() const{
	return _pid;
}




//end of namespace
}
}
}

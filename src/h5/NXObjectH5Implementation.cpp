/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * NXObjectH5Implementation.cpp
 *
 *  Created on: Jul 1, 2011
 *      Author: Eugen Wintersberger
 */

#include "NXObjectH5Implementation.hpp"
#include "H5TypeFactory.hpp"
#include "H5Exceptions.hpp"
#include "H5Utilities.hpp"

#include <pni/utils/Exceptions.hpp>

#include <string>
#include <iostream>

namespace pni{
namespace nx{
namespace h5{

using namespace pni::utils;

//------------------------------------------------------------------------------
//Implementation of the default constructor
NXObjectH5Implementation::NXObjectH5Implementation() {
	_id = 0;
}

//------------------------------------------------------------------------------
//Implementation of the destructor
NXObjectH5Implementation::~NXObjectH5Implementation() {
	//close the handler to the object
	close();
}

//------------------------------------------------------------------------------
//Implementation of the copy constructor
NXObjectH5Implementation::NXObjectH5Implementation(const NXObjectH5Implementation &o){
	EXCEPTION_SETUP("NXObjectH5Implementation::NXObjectH5Implementation"
					"(const NXObjectH5Implementation &o)");

	//the object we want to use as a template must be a valid object
	if(!H5Iis_valid(o._id)){
		EXCEPTION_INIT(H5ObjectError,"RHS object not a valid HDF5 object!");
		EXCEPTION_THROW();
	}

	//assign ID values and increment reference counter on this id
	_id = o._id;
	H5Iinc_ref(_id);
}

//------------------------------------------------------------------------------
//Implementation of the move constructor
NXObjectH5Implementation::NXObjectH5Implementation(NXObjectH5Implementation &&o){
	EXCEPTION_SETUP("NXObjectH5Implementation::NXObjectH5Implementation"
					"(NXObjectH5Implementation &&o)");

	//implement the move constructor in terms of move assignment
	*this = std::move(o);
}

//------------------------------------------------------------------------------
//Implementation of the copy assignment operator
NXObjectH5Implementation &NXObjectH5Implementation::operator=(const NXObjectH5Implementation &o){
	EXCEPTION_SETUP("NXObjectH5Implementation &NXObjectH5Implementation"
					"::operator=(const NXObjectH5Implementation &o)");

	if(this != &o){
		if(H5Iis_valid(_id)) H5Oclose(_id);
		_id = o._id;
		H5Iinc_ref(_id);
	}

	return *this;
}

//-----------------------------------------------------------------------------
//Implementation of the move assignment operator
NXObjectH5Implementation &NXObjectH5Implementation::operator=(NXObjectH5Implementation &&o){
	EXCEPTION_SETUP("NXObjectH5Implementation &NXObjectH5Implementation::"
					"operator=(NXObjectH5Implementation &&o)");

	if(this != &o){
		//close this instance of the object
		if(H5Iis_valid(_id)) H5Oclose(_id);

		//copy the object id
		_id = o._id;
		o._id = 0;
	}

	return *this;
}

//------------------------------------------------------------------------------
void NXObjectH5Implementation::_create_and_write_attribute(hid_t pid,const char *n,
		                       hid_t type_id,hid_t space_id,const void *ptr) const{
	EXCEPTION_SETUP("void NXObjectH5Implementation::"
			          "_create_and_write_attribute(hid_t pid,char *n,"
			          "hid_t type_id,hid_t space_id,void *ptr)");
	hid_t aid; //attribute handler
	htri_t retval;

	//remove attribute if it already exists
	retval = H5Aexists(pid,n);

	if(retval>0){
		H5Adelete(pid,n); //delete the attribute if it already exists
	}else if(retval < 0){
		EXCEPTION_INIT(H5AttributeError,"Existence check of attribute ["+String(n)+"] failed!");
		EXCEPTION_THROW();
	}

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

//------------------------------------------------------------------------------
void NXObjectH5Implementation::_open_attribute(const hid_t &pid,const char *n,
		                       hid_t &attr_id,hid_t &type_id,hid_t &space_id) const{
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

//------------------------------------------------------------------------------
void NXObjectH5Implementation::setAttribute(const String &n,const ArrayObject &a) const{
	EXCEPTION_SETUP("void NXObjectH5Implementation::setAttribute(const char *n,ArrayObject &a)");
	hid_t tid = 0;   //id of the data type
	hid_t setid = 0; //id of the data set

	if(!a.is_allocated()){
		EXCEPTION_INIT(H5AttributeError,"ArrayObject not allocated!");
		EXCEPTION_THROW();
	}

	tid = H5TFactory.getTypeFromID(a.type_id());

	//create the dataspace
	H5Utilities::Shape2DataSpace(a.shape(),setid);

	//create the attribute and write the data
	try{
		_create_and_write_attribute(_id,n.c_str(),tid,setid,a.buffer().void_ptr());
	}catch(...){
		EXCEPTION_INIT(H5AttributeError,"Cannot create and write attribute "+n+"!");
		EXCEPTION_THROW();
	}

	//close everything except the data type
	H5Sclose(setid);
}

//------------------------------------------------------------------------------
void NXObjectH5Implementation::setAttribute(const String &n,const ScalarObject &d) const{
	EXCEPTION_SETUP("void NXObjectH5Implementation::setAttribute(const char *n,ScalarObject &a)");
	hid_t tid = 0;   //id of the data type
	hid_t setid = 0; //id of the data set

	//determine the data type of the array object
	tid = H5TFactory.getTypeFromID(d.type_id());

	//create the dataspace
	setid = H5Screate(H5S_SCALAR);
	if(setid<0){
		EXCEPTION_INIT(H5DataSpaceError,"Error creating data-space for scalar attribute ["+n+"]!");
		EXCEPTION_THROW();
	}

	//create and write attribute data
	try{
		_create_and_write_attribute(_id,n.c_str(),tid,setid,d.void_ptr());
	}catch(...){
		EXCEPTION_INIT(H5AttributeError,"Cannot create and write attribute "+n+"!");
		EXCEPTION_THROW();
	}

	//close everything except the data type
	H5Sclose(setid);
}

//------------------------------------------------------------------------------
void NXObjectH5Implementation::setAttribute(const String &n,const String &s) const{
	EXCEPTION_SETUP("void NXObjectH5Implementation::setAttribute(const char *n,String &s)");
	hid_t tid;   //id of the data type
	hid_t setid; //id of the data set

	//determine the data type of the array object
	tid = H5TFactory.createTypeFromID(TypeID::STRING);
	//need to set the size of the string type
	H5Tset_size(tid,s.size());

	//create the dataspace
	setid = H5Screate(H5S_SCALAR);
	if (setid < 0) {
		EXCEPTION_INIT(H5DataSpaceError,"Error creating data-space for string attribute ["+n+"]!");
		EXCEPTION_THROW();
	}

	//create and write the attribute data
	try{
		_create_and_write_attribute(_id,n.c_str(),tid,setid,s.c_str());
	}catch(...){
		EXCEPTION_INIT(H5AttributeError,"Cannot create and write attribute "+String(n)+"!");
		EXCEPTION_THROW();
	}

	//close everything except the data type
	H5Sclose(setid);
}

//------------------------------------------------------------------------------
void NXObjectH5Implementation::getAttribute(const String &n,ArrayObject &a) const{
	EXCEPTION_SETUP("void NXObjectH5Implementation::getAttribute(const char *n,ArrayObject &a)");
	Shape temp_shape;


	hid_t atid = 0;
	hid_t asid = 0;
	hid_t aid  = 0;

	try{
		_open_attribute(_id,n.c_str(),aid,atid,asid);
	}catch(...){
		EXCEPTION_INIT(H5AttributeError,"Error opening attribute "+n+" for reading!");
		EXCEPTION_THROW();
	}
	//need to do some error checking here

	H5Utilities::DataSpace2Shape(asid,temp_shape);
	if((a.shape().size()==0)||(temp_shape != a.shape())){
		a.shape(temp_shape);
		a.allocate();
	}

	//copy data to the array buffer
	if((H5Aread(aid,atid,(void *)a.buffer().void_ptr()))<0){
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

//------------------------------------------------------------------------------
void NXObjectH5Implementation::getAttribute(const String &n,ScalarObject &s) const{
	EXCEPTION_SETUP("void NXObjectH5Implementation::getAttribute(const char *n,ScalarObject &a)");
	hid_t atid = 0;
	hid_t asid = 0;
	hid_t aid  = 0;

	try{
		_open_attribute(_id,n.c_str(),aid,atid,asid);
	}catch(...){
		EXCEPTION_INIT(H5AttributeError,"Error opening attribute "+n+" for reading!");
		EXCEPTION_THROW();
	}

	//copy data to the array buffer
	if((H5Aread(aid,atid,s.void_ptr()))<0){
		EXCEPTION_INIT(H5AttributeError,"Error reading data from scalar attribute ["+n+"]!");
		//close data-space, attribute, and data-type
		H5Tclose(atid);
		H5Sclose(asid);
		H5Aclose(aid);
		EXCEPTION_THROW();
	}

	s.name(n);

	//close everything
	H5Tclose(atid);
	H5Sclose(asid);
	H5Aclose(aid);
}

//------------------------------------------------------------------------------
void NXObjectH5Implementation::getAttribute(const String &n,String &s) const{
	EXCEPTION_SETUP("void NXObjectH5Implementation::getAttribute(const char *n,String &s)");
	hid_t atid = 0;
	hid_t asid = 0;
	hid_t aid  = 0;

	try{
		_open_attribute(_id,n.c_str(),aid,atid,asid);
	}catch(...){
		EXCEPTION_INIT(H5AttributeError,"Error opening attribute "+n+" for reading!");
		EXCEPTION_THROW();
	}
	//need to do some error checking here

	//now we need to find out how much memory to allocate
	s.resize(H5Tget_size(atid));
	if((H5Aread(aid,atid,(void *)s.c_str()))<0){
		EXCEPTION_INIT(H5AttributeError,"Error reading data from string attribute ["+n+"]!");
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

//------------------------------------------------------------------------------
String NXObjectH5Implementation::getPath() const{
	EXCEPTION_SETUP("String NXObjectH5Implementation::getName() const");
	char *buffer = nullptr;

	if(H5Iis_valid(_id)){
		//if the object has already been created return this value
		hsize_t bsize;
		bsize = H5Iget_name(_id,NULL,1)+1;
		buffer = new char[bsize];
		if(!buffer){
			EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate buffer for object name!");
			EXCEPTION_THROW();
		}

		H5Iget_name(_id,buffer,bsize);
		String name(buffer);
		if(buffer) delete [] buffer;
		return name;
	}

	return String("");
}

//------------------------------------------------------------------------------
String NXObjectH5Implementation::getBase() const {
	String p(getPath());

	size_t lpos = p.find_last_of("/");
	String base = "";
	if(lpos != p.npos){
		base = String(p,0,lpos+1);
	}

	return base;
}

//------------------------------------------------------------------------------
String NXObjectH5Implementation::getName() const {
	String p = getPath();

	//need to extract the the name information from the path
	size_t lpos = p.find_last_of("/");
	String name = "";
	if(lpos != p.npos){
		name = String(p,lpos+1,p.size()-lpos+1);
	}

	return name;

}

//------------------------------------------------------------------------------
pni::nx::NXObjectClass NXObjectH5Implementation::getObjectClass() const{
	if(H5Iis_valid(_id)){
		switch(H5Iget_type(_id)){
		case H5I_FILE: return NXFILE;
		case H5I_GROUP: return NXGROUP;
		case H5I_DATASET: return NXFIELD;
		default: return NXNONE;
		}
	}

	return NXNONE;
}

//------------------------------------------------------------------------------
bool NXObjectH5Implementation::isOpen() const {
	if(H5Iis_valid(_id)) return true;
	return false;
}

//------------------------------------------------------------------------------
void NXObjectH5Implementation::close(){
	if(H5Iis_valid(_id)) H5Oclose(_id);
	_id = 0;
}

//------------------------------------------------------------------------------
void NXObjectH5Implementation::createLink(const NXObjectH5Implementation &pos,
									      const String &n) const{
	EXCEPTION_SETUP("void NXObjectH5Implementation::createLink"
					"(const NXObjectH5Implementation &pos,const String &n)");

	hid_t loc_id = pos.getId();

	//check if the location is a valid HDF5 object
	if(!H5Iis_valid(loc_id)){
		EXCEPTION_INIT(H5ObjectError,"Link location is not a valid HDF5 location!");
		EXCEPTION_THROW();
	}

	//need to check if this object is open
	if(!isOpen()){
		EXCEPTION_INIT(H5ObjectError,"Link target is not open!");
		EXCEPTION_THROW();
	}

	herr_t err = H5Lcreate_soft(getPath().c_str(),loc_id,n.c_str(),H5P_DEFAULT,H5P_DEFAULT);
	if(err < 0){
		EXCEPTION_INIT(H5LinkError,"Could not establish link from "+
					   getPath()+" to "+pos.getPath()+"["+n+"]!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
void NXObjectH5Implementation::createLink(const String &path) const{
	EXCEPTION_SETUP("void NXObjectH5Implementation::createLink(const String &pos)");

	hid_t id = getId();

	if(!isOpen()){
		EXCEPTION_INIT(H5ObjectError,"Link target is not open!");
		EXCEPTION_THROW();
	}

	herr_t err = H5Lcreate_soft(getPath().c_str(),id,path.c_str(),H5P_DEFAULT,H5P_DEFAULT);
	if(err < 0){
		EXCEPTION_INIT(H5LinkError,"Coult not create symbolic link from "+
					   getPath()+" to "+path+"!");
		EXCEPTION_THROW();
	}

}

//end of namespace
}
}
}

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

namespace pni{
namespace nx{
namespace h5{

using namespace pni::utils;

NXObjectH5Implementation::NXObjectH5Implementation() {
	// TODO Auto-generated constructor stub

}

//implementation of the copy constructor
NXObjectH5Implementation::NXObjectH5Implementation(const NXObjectH5Implementation &o){
	//basic problem - what happens if the object that holds the
	//handler (_id) to a particular HDF5 object goes out of scope or becomes
	//destroyed for any other reason?

	//what one has to do here is simply open a new handler to the object
	//refered to by o.

	//DO NOTHING HERE - MUST BE IMPLEMENTED BY THE CONCRETE CLASSES
}

NXObjectH5Implementation::~NXObjectH5Implementation() {
	_name.clear();
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

void NXObjectH5Implementation::setAttribute(const char *n,ArrayObject &a){
	H5METHOD_EXCEPTION_SETUP("void NXObjectH5Implementation::setAttribute(const char *n,ArrayObject &a)");
	hid_t aid;   //id of the attribute object
	hid_t tid;   //id of the data type
	hid_t setid; //id of the data set
	ArrayShape &s = *(a.getShape());

	//determine the data type of the array object
	tid = H5TFactory.getTypeFromID(a.getTypeID());

	//create the dataspace
	H5Utilities::ArrayShape2DataSpace(s,setid);

	//create the attribute and check for errors
	aid = H5Acreate2(_id,n,tid,setid,H5P_DEFAULT,H5P_DEFAULT);
	if(aid<0){
		H5METHOD_EXCEPTION_INIT(H5AttributeException,"Error creating array attribute ["+String(n)+"]!");
		H5Sclose(setid);
		H5METHOD_EXCEPTION_THROW();
	}

	//write data and check for errors
	if((H5Awrite(aid,tid,a.getBuffer()->getVoidPtr()))<0){
		H5METHOD_EXCEPTION_INIT(H5AttributeException,"Error writing data to array attribute ["+String(n)+"]!");
		H5Aclose(aid);
		H5Sclose(setid);
		H5METHOD_EXCEPTION_THROW();
	}

	//close everything except the data type
	H5Aclose(aid);
	H5Sclose(setid);
}

void NXObjectH5Implementation::setAttribute(const char *n,ScalarObject &d){
	H5METHOD_EXCEPTION_SETUP("void NXObjectH5Implementation::setAttribute(const char *n,ScalarObject &a)");
	hid_t aid;   //id of the attribute object
	hid_t tid;   //id of the data type
	hid_t setid; //id of the data set

	//determine the data type of the array object
	tid = H5TFactory.getTypeFromID(d.getTypeID());

	//create the dataspace
	setid = H5Screate(H5S_SCALAR);
	if(setid<0){
		H5METHOD_EXCEPTION_INIT(H5DataSpaceException,"Error creating data-space for scalar attribute ["+String(n)+"]!");
		H5METHOD_EXCEPTION_THROW();
	}

	//create the attribute
	aid = H5Acreate2(_id, n, tid, setid, H5P_DEFAULT,H5P_DEFAULT);
	if(aid<0){
		H5METHOD_EXCEPTION_INIT(H5AttributeException,"Error creating scalar attribute ["+String(n)+"]!");
		H5Sclose(setid);
		H5METHOD_EXCEPTION_THROW();
	}

	//have to write the data
	if((H5Awrite(aid, tid, d.getVoidPtr()))<0){
		H5METHOD_EXCEPTION_INIT(H5AttributeException,"Error writting data to scalar attribute ["+String(n)+"]!");
		H5Aclose(aid);
		H5Sclose(setid);
		H5METHOD_EXCEPTION_THROW();

	}

	//close everything except the data type
	H5Aclose(aid);
	H5Sclose(setid);
}


void NXObjectH5Implementation::setAttribute(const char *n,const String &s){
	H5METHOD_EXCEPTION_SETUP("void NXObjectH5Implementation::setAttribute(const char *n,String &s)");
	hid_t aid;   //id of the attribute object
	hid_t tid;   //id of the data type
	hid_t setid; //id of the data set

	//determine the data type of the array object
	tid = H5TFactory.createStringType(s.size());

	//create the dataspace
	setid = H5Screate(H5S_SCALAR);
	if (setid < 0) {
		H5METHOD_EXCEPTION_INIT(H5DataSpaceException,"Error creating data-space for string attribute ["+String(n)+"]!");
		H5METHOD_EXCEPTION_THROW();
	}

	//create the attribute
	aid = H5Acreate2(_id, n, tid, setid, H5P_DEFAULT, H5P_DEFAULT);
	if (aid < 0) {
		H5METHOD_EXCEPTION_INIT(H5AttributeException,"Error creating string attribute ["+String(n)+"]!");
		H5Sclose(setid);
		H5METHOD_EXCEPTION_THROW();
	}

	//have to write the data
	if ((H5Awrite(aid, tid, s.c_str())) < 0) {
		H5METHOD_EXCEPTION_INIT(H5AttributeException,"Error writing data to string attribute ["+String(n)+"]!");
		H5Aclose(aid);
		H5Sclose(setid);
		H5METHOD_EXCEPTION_THROW();
	}

	//close everything except the data type
	H5Aclose(aid);
	H5Sclose(setid);
}

void NXObjectH5Implementation::getAttribute(const char *n,ArrayObject &a){
	H5METHOD_EXCEPTION_SETUP("void NXObjectH5Implementation::getAttribute(const char *n,ArrayObject &a)");
	ArrayShape temp_shape;


	hid_t atid = 0;
	hid_t asid = 0;
	hid_t aid  = 0;

	aid = H5Aopen(_id,n,H5P_DEFAULT);
	if(aid<0){
		H5METHOD_EXCEPTION_INIT(H5AttributeException,"Error opening array attribute ["+String(n)+"]!");
		H5METHOD_EXCEPTION_THROW();
	}

	asid = H5Aget_space(aid);
	if(asid<0){
		H5METHOD_EXCEPTION_INIT(H5DataSpaceException,"Error opening data-space for array attribute ["+String(n)+"]!");
		H5Aclose(aid);
		H5METHOD_EXCEPTION_THROW();
	}
	atid = H5Aget_type(aid);
	if(atid<0){
		H5METHOD_EXCEPTION_INIT(H5DataTypeException,"Error opening data-type for array attribute ["+String(n)+"]!");
		H5Tclose(atid);
		H5Aclose(aid);
		H5METHOD_EXCEPTION_THROW();
	}

	H5Utilities::DataSpace2ArrayShape(asid,temp_shape);
	if((!a.getShape())||(temp_shape != *(a.getShape()))){
		a.setShape(temp_shape);
		a.Allocate();
	}

	//copy data to the array buffer
	if((H5Aread(aid,atid,a.getBuffer()->getVoidPtr()))<0){
		H5METHOD_EXCEPTION_INIT(H5DataSetException,"Error reading data from array attribute ["+String(n)+"]!");
		H5Tclose(atid);
		H5Sclose(asid);
		H5Aclose(aid);
		H5METHOD_EXCEPTION_THROW();
	}

	//close everything
	H5Tclose(atid);
	H5Sclose(asid);
	H5Aclose(aid);

}

void NXObjectH5Implementation::getAttribute(const char *n,ScalarObject &s){
	H5METHOD_EXCEPTION_SETUP("void NXObjectH5Implementation::getAttribute(const char *n,ScalarObject &a)");
	hid_t atid = 0;
	hid_t asid = 0;
	hid_t aid  = 0;

	aid = H5Aopen(_id,n,H5P_DEFAULT);
	if(aid<0){
		H5METHOD_EXCEPTION_INIT(H5AttributeException,"Error opening scalar attribute ["+String(n)+"]!");
		H5METHOD_EXCEPTION_THROW();
	}

	asid = H5Aget_space(aid);
	if(asid<0){
		H5METHOD_EXCEPTION_INIT(H5DataSpaceException,"Error opening data-space for scalar attribute ["+String(n)+"]!");
		H5Aclose(aid);
		H5METHOD_EXCEPTION_THROW();
	}
	if(!H5Sis_simple(asid)){
		H5METHOD_EXCEPTION_INIT(H5DataSpaceException,"Dataspace of scalar attribute ["+String(n)+"] is of array type!");
		//close space and attribute
		H5Sclose(asid);
		H5Aclose(aid);
		H5METHOD_EXCEPTION_THROW();
	}

	atid = H5Aget_type(aid);
	if(atid<0){
		H5METHOD_EXCEPTION_INIT(H5DataTypeException,"Error opening data type for scalar attribute ["+String(n)+"]!");
		//close dataspace and data type
		H5Tclose(atid);
		H5Sclose(asid);
		H5METHOD_EXCEPTION_THROW();
	}

	//copy data to the array buffer
	if((H5Aread(aid,atid,s.getVoidPtr()))<0){
		H5METHOD_EXCEPTION_INIT(H5AttributeException,"Error reading data from scalar attribute ["+String(n)+"]!");
		//close data-space, attribute, and data-type
		H5Tclose(atid);
		H5Sclose(asid);
		H5Aclose(aid);
		H5METHOD_EXCEPTION_THROW();
	}

	s.setName(_name);

	//close everything
	H5Tclose(atid);
	H5Sclose(asid);
	H5Aclose(aid);
}

void NXObjectH5Implementation::getAttribute(const char *n,String &s){
	H5METHOD_EXCEPTION_SETUP("void NXObjectH5Implementation::getAttribute(const char *n,String &s)");
	hid_t atid = 0;
	hid_t asid = 0;
	hid_t aid  = 0;

	aid = H5Aopen(_id,n,H5P_DEFAULT);
	if(aid<0){
		H5METHOD_EXCEPTION_INIT(H5AttributeException,"Error opening string attribute ["+String(n)+"]!");
	}

	//fetch dataspace and datatype
	atid = H5Aget_type(aid);
	if(atid<0){
		H5METHOD_EXCEPTION_INIT(H5DataTypeException,"Error opening data type for string attribute ["+String(n)+"]!");
		H5Aclose(aid);
		H5METHOD_EXCEPTION_THROW();
	}

	if(H5Tget_class(atid)!=H5T_STRING){
		H5METHOD_EXCEPTION_INIT(H5DataTypeException,"Data type of attribute ["+String(n)+"] is not of string type!");
		//close attribute and type object
		H5Aclose(aid);
		H5Tclose(atid);
		H5METHOD_EXCEPTION_THROW();
	}

	asid = H5Aget_space(aid);
	if(asid<0){
		H5METHOD_EXCEPTION_INIT(H5DataSpaceException,"Error opening data-space for string attribute ["+String(n)+"]!");
		H5Tclose(atid);
		H5Aclose(aid);
		H5METHOD_EXCEPTION_THROW();
	}

	//now we need to find out how much memory to allocate
	s.resize(H5Tget_size(atid));
	if((H5Aread(aid,atid,(void *)s.c_str()))<0){
		H5METHOD_EXCEPTION_INIT(H5AttributeException,"Error reading data from string attribute ["+String(n)+"]!");
		H5Tclose(atid);
		H5Aclose(aid);
		H5Sclose(asid);
		H5METHOD_EXCEPTION_THROW();
	}

	//close everything down
	H5Aclose(aid);
	H5Tclose(atid);
	H5Sclose(asid);
}



//end of namespace
}
}
}

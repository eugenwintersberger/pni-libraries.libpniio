/*
 * NXObjectH5Implementation.cpp
 *
 *  Created on: Jul 1, 2011
 *      Author: eugen
 */

#include "NXObjectH5Implementation.hpp"
#include "H5TypeFactory.hpp"
#include "H5Exceptions.hpp"

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
	static String ExIssuer("void NXObjectH5Implementation::setAttribute(const char *n,ArrayObject &a)");
	String ExDescription;
	hid_t aid;   //id of the attribute object
	hid_t tid;   //id of the data type
	hid_t setid; //id of the data set
	ArrayShape &s = *(a.getShape());

	//determine the data type of the array object
	tid = H5TFactory.getTypeFromID(a.getTypeID());

	//create the dataspace
	setid = H5Screate_simple(s.getRank(),(hsize_t *)s.getDimensions(),NULL);
	//check here for errors
	if(setid<0){
		ExDescription = "Error creating simple data space for array attribute ["+String(n)+"]!";
		H5DataSpaceException e(ExIssuer,ExDescription);
		std::cerr<<e<<std::endl;
		throw e;
	}

	//create the attribute and check for errors
	aid = H5Acreate1(_id,n,tid,setid,H5P_DEFAULT);
	if(aid<0){
		ExDescription = "Error creating array attribute ["+String(n)+"]!";
		H5AttributeException e(ExIssuer,ExDescription);

		//close the already open dataspace
		H5Sclose(setid);
		std::cerr<<e<<std::endl;
		throw e;
	}

	//write data and check for errors
	if((H5Awrite(aid,tid,a.getBuffer()->getVoidPtr()))<0){
		ExDescription = "Error writing data to array attribute ["+String(n)+"]!";
		H5AttributeException e(ExIssuer,ExDescription);

		H5Aclose(aid);
		H5Sclose(setid);
		std::cerr<<e<<std::endl;
		throw e;
	}

	//close everything except the data type
	H5Aclose(aid);
	H5Sclose(setid);
}

void NXObjectH5Implementation::setAttribute(const char *n,ScalarObject &d){
	static String ExIssuer("void NXObjectH5Implementation::setAttribute(const char *n,ScalarObject &a)");
	String ExDescription;
	hid_t aid; //id of the attribute object
	hid_t tid; //id of the data type
	hid_t setid; //id of the data set

	//determine the data type of the array object
	tid = H5TFactory.getTypeFromID(d.getTypeID());

	//create the dataspace
	setid = H5Screate(H5S_SCALAR);
	if(setid<0){
		ExDescription = "Error creating data-space for scalar attribute ["+String(n)+"]!";
		H5DataSpaceException e(ExIssuer,ExDescription);
		std::cerr<<e<<std::endl;
		throw e;
	}

	//create the attribute
	aid = H5Acreate2(_id, n, tid, setid, H5P_DEFAULT,H5P_DEFAULT);
	if(aid<0){
		ExDescription="Error creating scalar attribute ["+String(n)+"]!";
		H5AttributeException e(ExIssuer,ExDescription);

		H5Sclose(setid);
		std::cerr<<e<<std::endl;
		throw e;
	}

	//have to write the data
	if((H5Awrite(aid, tid, d.getVoidPtr()))<0){
		ExDescription = "Error writting data to scalar attribute ["+String(n)+"]!";
		H5AttributeException e(ExIssuer,ExDescription);

		H5Aclose(aid);
		H5Sclose(setid);
		std::cerr<<e<<std::endl;
		throw e;
	}

	//close everything except the data type
	H5Aclose(aid);
	H5Sclose(setid);
}


void NXObjectH5Implementation::setAttribute(const char *n,const String &s){
	static String ExIssuer("void NXObjectH5Implementation::setAttribute(const char *n,String &s)");
	String ExDescription;
	hid_t aid;   //id of the attribute object
	hid_t tid;   //id of the data type
	hid_t setid; //id of the data set

	//determine the data type of the array object
	tid = H5TFactory.createStringType(s.size());

	//create the dataspace
	setid = H5Screate(H5S_SCALAR);
	if (setid < 0) {
		ExDescription = "Error creating data-space for string attribute ["+String(n)+"]!";
		H5DataSpaceException e(ExIssuer,ExDescription);
		std::cerr<<e<<std::endl;
		throw e;
	}

	//create the attribute
	aid = H5Acreate2(_id, n, tid, setid, H5P_DEFAULT, H5P_DEFAULT);
	if (aid < 0) {
		ExDescription = "Error creating string attribute ["+String(n)+"]!";
		H5AttributeException e(ExIssuer,ExDescription);

		H5Sclose(setid);
		std::cerr<<e<<std::endl;
		throw e;
	}

	//have to write the data
	if ((H5Awrite(aid, tid, s.c_str())) < 0) {
		ExDescription = "Error writing data to string attribute ["+String(n)+"]!";
		H5AttributeException e(ExIssuer,ExDescription);

		H5Aclose(aid);
		H5Sclose(setid);
		std::cerr<<e<<std::endl;
		throw e;
	}

	//close everything except the data type
	H5Aclose(aid);
	H5Sclose(setid);
}

void NXObjectH5Implementation::getAttribute(const char *n,ArrayObject &a){
	static String ExIssuer("void NXObjectH5Implementation::getAttribute(const char *n,ArrayObject &a)");
	String ExDescription;
	pni::utils::ArrayShape &s = *a.getShape();
	pni::utils::BufferObject &b = *a.getBuffer();

	hid_t atid = 0;
	hid_t asid = 0;
	hid_t aid  = 0;
	hsize_t *dims=NULL;
	int rank;

	aid = H5Aopen(_id,n,H5P_DEFAULT);
	if(aid<0){
		ExDescription = "Error opening array attribute ["+String(n)+"]!";
		H5AttributeException e(ExIssuer,ExDescription);
		std::cerr<<e<<std::endl;
		throw e;
	}

	asid = H5Aget_space(aid);
	if(asid<0){
		ExDescription = "Error opening data-space for array attribute ["+String(n)+"]!";
		H5DataSpaceException e(ExIssuer,ExDescription);
		H5Aclose(aid);
		std::cerr<<e<<std::endl;
		throw e;
	}
	atid = H5Aget_type(aid);
	if(atid<0){
		ExDescription = "Error opening data-type for array attribute ["+String(n)+"]!";
		H5DataTypeException e(ExIssuer,ExDescription);
		H5Tclose(atid);
		H5Aclose(aid);
		std::cerr<<e<<std::endl;
		throw e;
	}

	//now we have to identify the shape parameters of the dataspace
	rank = H5Sget_simple_extent_dims(asid,dims,NULL);
	//do some error checking here

	//set rank and dimensions for the array shape object
	s.setRank(rank);
	for(pni::utils::Int64 i=0;i<rank;i++) s.setDimension(i,dims[i]);

	//now allocate memory for the buffer
	b.resize(s.getSize());

	//copy data to the array buffer
	if((H5Aread(aid,atid,b.getVoidPtr()))<0){
		ExDescription = "Error reading data from array attribute ["+String(n)+"]!";
		H5DataSetException e(ExIssuer,ExDescription);
		H5Tclose(atid);
		H5Sclose(asid);
		H5Aclose(aid);
		std::cerr<<e<<std::endl;
		throw e;
	}


	//close everything
	H5Tclose(atid);
	H5Sclose(asid);
	H5Aclose(aid);

}

void NXObjectH5Implementation::getAttribute(const char *n,ScalarObject &s){
	static String ExIssuer("void NXObjectH5Implementation::getAttribute(const char *n,ScalarObject &a)");
	String ExDescription;
	hid_t atid = 0;
	hid_t asid = 0;
	hid_t aid  = 0;

	aid = H5Aopen(_id,n,H5P_DEFAULT);
	if(aid<0){
		ExDescription = "Error opening scalar attribute ["+String(n)+"]!";
		H5AttributeException e(ExIssuer,ExDescription);
		std::cerr<<e<<std::endl;
		throw e;
	}

	asid = H5Aget_space(aid);
	if(asid<0){
		ExDescription = "Error opening data-space for scalar attribute ["+String(n)+"]!";
		H5DataSpaceException e(ExIssuer,ExDescription);
		H5Aclose(aid);
		std::cerr<<e<<std::endl;
		throw e;
	}
	if(!H5Sis_simple(asid)){
		ExDescription = "Dataspace of scalar attribute ["+String(n)+"] is of array type!";
		H5DataSpaceException e(ExIssuer,ExDescription);

		//close space and attribute
		H5Sclose(asid);
		H5Aclose(aid);

		//throw exception
		std::cerr<<e<<std::endl;
		throw e;
	}


	atid = H5Aget_type(aid);
	if(atid<0){
		ExDescription = "Error opening data type for scalar attribute ["+String(n)+"]!";
		H5DataTypeException e(ExIssuer,ExDescription);

		//close dataspace and data type
		H5Tclose(atid);
		H5Sclose(asid);
		//throw exception
		std::cerr<<e<<std::endl;
		throw e;
	}

	//copy data to the array buffer
	if((H5Aread(aid,atid,s.getVoidPtr()))<0){
		ExDescription = "Error reading data from scalar attribute ["+String(n)+"]!";
		H5AttributeException e(ExIssuer,ExDescription);

		//close data-space, attribute, and data-type
		H5Tclose(atid);
		H5Sclose(asid);
		H5Aclose(aid);
		std::cerr<<e<<std::endl;
		throw e;
	}

	s.setName(_name);

	//close everything
	H5Tclose(atid);
	H5Sclose(asid);
	H5Aclose(aid);
}

void NXObjectH5Implementation::getAttribute(const char *n,String &s){
	static String ExIssuer("void NXObjectH5Implementation::getAttribute(const char *n,String &s)");
	String ExDescription;
	hid_t atid = 0;
	hid_t asid = 0;
	hid_t aid  = 0;


	aid = H5Aopen(_id,n,H5P_DEFAULT);
	if(aid<0){
		ExDescription = "Error opening string attribute ["+String(n)+"]!";
		H5AttributeException e(ExIssuer,ExDescription);
		std::cerr<<e<<std::endl;
		throw e;
	}

	//fetch dataspace and datatype
	atid = H5Aget_type(aid);
	if(atid<0){
		ExDescription = "Error opening data type for string attribute ["+String(n)+"]!";
		H5DataTypeException e(ExIssuer,ExDescription);
		H5Aclose(aid);
		std::cerr<<e<<std::endl;
		throw e;
	}

	if(H5Tget_class(atid)!=H5T_STRING){
		ExDescription = "Data type of attribute ["+String(n)+"] is not of string type!";
		H5DataTypeException e(ExIssuer,ExDescription);

		//close attribute and type object
		H5Aclose(aid);
		H5Tclose(atid);

		//raise an exeption here
		std::cerr<<e<<std::endl;
		throw e;
	}

	asid = H5Aget_space(aid);
	if(asid<0){
		ExDescription = "Error opening data-space for string attribute ["+String(n)+"]!";
		H5DataSpaceException e(ExIssuer,ExDescription);

		H5Tclose(atid);
		H5Aclose(aid);
		std::cerr<<e<<std::endl;
		throw e;
	}

	//now we need to find out how much memory to allocate
	s.resize(H5Tget_size(atid));
	if((H5Aread(aid,atid,(void *)s.c_str()))<0){
		ExDescription = "Error reading data from string attribute ["+String(n)+"]!";
		H5AttributeException e(ExIssuer,ExDescription);

		H5Tclose(atid);
		H5Aclose(aid);
		H5Sclose(asid);
		std::cerr<<e<<std::endl;
		throw e;
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

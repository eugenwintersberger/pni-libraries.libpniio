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
 * NXStringFieldH5Implementation.cpp
 *
 *  Created on: Dec 2, 2011
 *      Author: Eugen Wintersberger
 */

#include "NXStringFieldH5Implementation.hpp"
#include "H5Exceptions.hpp"

namespace pni {
namespace nx {
namespace h5 {

//===================Implementation of constructors and destructor==============
//implementation of the default constructor
NXStringFieldH5Implementation::NXStringFieldH5Implementation():
		NXFieldH5Implementation(){

}

//------------------------------------------------------------------------------
//implementation of the copy conversion constructor
NXStringFieldH5Implementation::
NXStringFieldH5Implementation(const NXFieldH5Implementation &o):
NXFieldH5Implementation(o){
	EXCEPTION_SETUP("NXStringFieldH5Implementation::"
					"NXStringFieldH5Implementation"
					"(const NXFieldH5Implementation &o)");

	//have to check here if the data type is correct
	if(getTypeID() != PNITypeID::STRING){
		close();
		EXCEPTION_INIT(TypeError,"Data field is not a string field!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
//implementation of the copy conversion constructor
NXStringFieldH5Implementation::
NXStringFieldH5Implementation(const NXObjectH5Implementation &o):
NXFieldH5Implementation(o){
	EXCEPTION_SETUP("NXStringFieldH5Implementation::"
					"NXStringFieldH5Implementation"
					"(const NXObjectH5Implementation &o)");

	//have to check here if the data type is correct
	if(getTypeID() != PNITypeID::STRING){
		close();
		EXCEPTION_INIT(TypeError,"Object is not a not a string field!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
//implementation of the move conversion constructor
NXStringFieldH5Implementation::
NXStringFieldH5Implementation(NXFieldH5Implementation &&o):
NXFieldH5Implementation(std::move(o)){
	EXCEPTION_SETUP("NXStringFieldH5Implementation::"
					"NXStringFieldH5Implementation"
					"(NXFieldH5Implementation &&o)");

	std::cout<<"Calling move conversion constructor!"<<std::endl;
	//have to check if the data type is correct for a string field
	if(getTypeID() != PNITypeID::STRING){
		close();
		EXCEPTION_INIT(TypeError,"Field is not a string field!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
//implementation of the move conversion constructor
NXStringFieldH5Implementation::
NXStringFieldH5Implementation(NXObjectH5Implementation &&o):
NXFieldH5Implementation(std::move(o)){
	EXCEPTION_SETUP("NXStringFieldH5Implementation::"
					"NXStringFieldH5Implementation"
					"(NXObjectH5Implementation &&o)");

	//have to check here if the data type is correct
	if(getTypeID() != PNITypeID::STRING){
		close();
		EXCEPTION_INIT(TypeError,"Object is not a not a string field!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
//implementation of the copy constructor
NXStringFieldH5Implementation::
NXStringFieldH5Implementation(const NXStringFieldH5Implementation &o):
NXFieldH5Implementation(o){
	EXCEPTION_SETUP("NXStringFieldH5Implementation::"
					"NXStringFieldH5Implementation"
					"(const NXStringFieldH5Implementation &o)");


	//have to check if the data type is correct for a string field
	if(getTypeID() != PNITypeID::STRING){
		close();
		EXCEPTION_INIT(TypeError,"Field is not a string field!");
		EXCEPTION_THROW();
	}


}

//------------------------------------------------------------------------------
//implementation of the move constructor
NXStringFieldH5Implementation::
NXStringFieldH5Implementation(NXStringFieldH5Implementation &&o):
NXFieldH5Implementation(std::move(o)){
	EXCEPTION_SETUP("NXStringFieldH5Implementation::"
					"NXStringFieldH5Implementation"
					"(NXStringFieldH5Implementation &&o)");

	//have to check if the data type is correct for a string field
	if(getTypeID() != PNITypeID::STRING){
		close();
		EXCEPTION_INIT(TypeError,"Field is not a string field!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
//implementation of the destructor
NXStringFieldH5Implementation::~NXStringFieldH5Implementation(){

}

//=====================Implementation of the assignment operators===============
//implementation of the copy assignment operator
NXStringFieldH5Implementation &
NXStringFieldH5Implementation::operator=(const NXStringFieldH5Implementation &o){
	EXCEPTION_SETUP("NXStringFieldH5Implementation &"
					"NXStringFieldH5Implementation::operator="
					"(const NXStringFieldH5Implementation &o)");

	(NXFieldH5Implementation &)(*this) = (NXFieldH5Implementation &)o;
	return *this;
}

//------------------------------------------------------------------------------
//implementation of the move assignment operator
NXStringFieldH5Implementation &
NXStringFieldH5Implementation::operator=(NXStringFieldH5Implementation &&o){
	EXCEPTION_SETUP("NXStringFieldH5Implementation &"
					"NXStringFieldH5Implementation::operator="
					"(NXStringFieldH5Implementation &&o)");

	(NXFieldH5Implementation &)(*this) = std::move((NXFieldH5Implementation &&)o);
	return *this;
}

//------------------------------------------------------------------------------
//implementation of the copy conversion assignment
NXStringFieldH5Implementation &
NXStringFieldH5Implementation::operator=(const NXFieldH5Implementation &o){
	EXCEPTION_SETUP("NXStringFieldH5Implementation &"
					"NXStringFieldH5Implementation::operator="
					"(const NXFieldH5Implementation &o)");

	if(o.getTypeID() != PNITypeID::STRING){
		EXCEPTION_INIT(TypeError,"Field is not a string field!");
		EXCEPTION_THROW();
	}

	(NXFieldH5Implementation &)(*this) = o;

	return *this;
}

//------------------------------------------------------------------------------
//implementation of the copy conversion assignment
NXStringFieldH5Implementation &
NXStringFieldH5Implementation::operator=(const NXObjectH5Implementation &o){
	EXCEPTION_SETUP("NXStringFieldH5Implementation &"
					"NXStringFieldH5Implementation::operator="
					"(const NXObjectH5Implementation &o)");

	(NXFieldH5Implementation &)(*this) = o;
	if(getTypeID() != PNITypeID::STRING){
		EXCEPTION_INIT(TypeError,"Object is not a string field!");
		EXCEPTION_THROW();
	}
	return *this;
}

//------------------------------------------------------------------------------
//implementation of the move conversion assignment
NXStringFieldH5Implementation &
NXStringFieldH5Implementation::operator=(NXFieldH5Implementation &&o){
	EXCEPTION_SETUP("NXStringFieldH5Implementation &"
					"NXStringFieldH5Implementation::operator="
					"(NXFieldH5Implementation &&o)");

	if(o.getTypeID() != PNITypeID::STRING){
		EXCEPTION_INIT(TypeError,"Field is not a string field!");
		EXCEPTION_THROW();
	}

	(NXFieldH5Implementation &)(*this) = std::move(o);
	return *this;
}

//------------------------------------------------------------------------------
//implementation of the move conversion assignment
NXStringFieldH5Implementation &
NXStringFieldH5Implementation::operator=(NXObjectH5Implementation &&o){
	EXCEPTION_SETUP("NXStringFieldH5Implementation &"
					"NXStringFieldH5Implementation::operator="
					"(NXObjectH5Implementation &&o)");

	(NXFieldH5Implementation &)(*this) = std::move(o);
	if(getTypeID() != PNITypeID::STRING){
		EXCEPTION_INIT(TypeError,"Object is not a string field!");
		EXCEPTION_THROW();
	}
	return *this;
}

//================Implementation of IO functions================================
//get number of strings
UInt64 NXStringFieldH5Implementation::size() const{
	return getShape().getDimension(0);
}

//------------------------------------------------------------------------------
//append a string
void NXStringFieldH5Implementation::append(const String &o){
	EXCEPTION_SETUP("void NXFieldH5Implementation::append(const String &s)");
	herr_t err;
	hid_t elem_type;

	elem_type = H5Dget_type(getId());
	//extend field along growth dimension
	_resize_dataset(1);
	_offset[0] = getShape().getDimension(0)-1;

	const char *ptr = o.c_str();

	H5Sselect_hyperslab(_filespace,H5S_SELECT_SET,_offset,NULL,_count,NULL);
	err = H5Dwrite(getId(),elem_type,_elemspace,_filespace,H5P_DEFAULT,&ptr);
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error writing data!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
//set a string
void NXStringFieldH5Implementation::set(const UInt64 &i,const String &o){
	EXCEPTION_SETUP("void NXStringFieldH5Implementation::set(const UInt64 &i,const String &o)");
	herr_t err;
	hid_t elem_type;

	elem_type = H5Dget_type(getId());
	//extend field along growth dimension
	if(i>=getShape().getDimension(0)){
		_resize_dataset(1+i-getShape().getDimension(0));
	}
	_offset[0] = i;

	const char *ptr = o.c_str();

	H5Sselect_hyperslab(_filespace,H5S_SELECT_SET,_offset,NULL,_count,NULL);
	err = H5Dwrite(getId(),elem_type,_elemspace,_filespace,H5P_DEFAULT,&ptr);
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error writing data!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
//get a string
void NXStringFieldH5Implementation::get(const UInt64 &i,String &o){
	EXCEPTION_SETUP("void NXFieldH5Implementation::get(const UInt64 &i,String &s)");

	if(i>=getShape().getDimension(0)){
		EXCEPTION_INIT(IndexError,"Element index exceeds container size!");
		EXCEPTION_THROW();
	}

	hid_t elem_type = H5Dget_type(getId());
	_offset[0] = i;
	herr_t err = 0;
	hid_t xfer_plist = H5Pcreate(H5P_DATASET_XFER);

	//select data element
	H5Sselect_hyperslab(_filespace,H5S_SELECT_SET,_offset,NULL,_count,NULL);

	//need to determine the amount of memory required to store the data
	char *ptr = nullptr;

	err = H5Dread(getId(),elem_type,_elemspace,_filespace,xfer_plist,&ptr);
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error reading data from field ["+getName()+"]!");
		EXCEPTION_THROW();
	}

	//reset selection - this is needed in order to make H5Dvlen_reclaim
	//work without producing segmentation faults
	H5Sselect_none(_filespace);

	//copy content of the pointer to the string object
    try{
	    o = String(ptr);
    }catch(...){
        o = "";
    }

	//reclaim memory from HDF5 library.
	H5Dvlen_reclaim(elem_type,_filespace,xfer_plist,&ptr);

}

//------------------------------------------------------------------------------
//get a string
String NXStringFieldH5Implementation::get(const UInt64 &i){
	EXCEPTION_SETUP("String &&NXStringFieldH5Implementation::get(const UInt64 &i)");
	String value;

	get(i,value);

	return value;
}

//------------------------------------------------------------------------------
String NXStringFieldH5Implementation::get(const char &sep){
	EXCEPTION_SETUP("String &&NXStringFieldH5Implementation::get(const char &sep)");
	String total;

	for(UInt64 i=0;i<size();i++){
		total += get(i);
		if(i!= size()-1) total += sep;
	}

	return std::move(total);
}



} /* namespace h5 */
} /* namespace nx */
} /* namespace pni */

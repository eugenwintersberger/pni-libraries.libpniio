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
 * NXBinaryFieldH5Implementation.cpp
 *
 *  Created on: Dec 2, 2011
 *      Author: Eugen Wintersberger
 */

#include "NXBinaryFieldH5Implementation.hpp"
#include "H5Exceptions.hpp"

namespace pni {
namespace nx {
namespace h5 {

//=============Implementation of constructors and destructor====================
//implementation of default constructor
NXBinaryFieldH5Implementation::NXBinaryFieldH5Implementation():
	NXFieldH5Implementation(){

}

//------------------------------------------------------------------------------
//implementation of copy conversion constructor
NXBinaryFieldH5Implementation::
NXBinaryFieldH5Implementation(const NXFieldH5Implementation &o):
NXFieldH5Implementation(o){
	EXCEPTION_SETUP("NXBinaryFieldH5Implementation::"
					"NXBinaryFieldH5Implementation"
					"(const NXFieldH5Implementation &o)");

	if(getTypeID() != PNITypeID::BINARY){
		EXCEPTION_INIT(TypeError,"Field is not a binary field!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
//implementation of copy move conversion constructor
NXBinaryFieldH5Implementation::
NXBinaryFieldH5Implementation(NXFieldH5Implementation &&o):
NXFieldH5Implementation(std::move(o)){
	EXCEPTION_SETUP("NXBinaryFieldH5Implementation::"
					"NXBinaryFieldH5Implementation"
					"(NXFieldH5Implementation &&o)");

	if(getTypeID() != PNITypeID::BINARY){
		EXCEPTION_INIT(TypeError,"Field is not a binary field!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
//implementation of copy conversion constructor
NXBinaryFieldH5Implementation::
NXBinaryFieldH5Implementation(const NXObjectH5Implementation &o):
NXFieldH5Implementation(o){
	EXCEPTION_SETUP("NXBinaryFieldH5Implementation::"
					"NXBinaryFieldH5Implementation"
					"(const NXObjectH5Implementation &o)");

	if(getTypeID() != PNITypeID::BINARY){
		EXCEPTION_INIT(TypeError,"Object is not a binary field!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
//implementation of copy move conversion constructor
NXBinaryFieldH5Implementation::
NXBinaryFieldH5Implementation(NXObjectH5Implementation &&o):
NXFieldH5Implementation(std::move(o)){
	EXCEPTION_SETUP("NXBinaryFieldH5Implementation::"
					"NXBinaryFieldH5Implementation"
					"(NXObjectH5Implementation &&o)");

	if(getTypeID() != PNITypeID::BINARY){
		EXCEPTION_INIT(TypeError,"Object is not a binary field!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
//implementation of copy constructor
NXBinaryFieldH5Implementation::
NXBinaryFieldH5Implementation(const NXBinaryFieldH5Implementation &o):
NXFieldH5Implementation(o){

}

//------------------------------------------------------------------------------
//! move constructor
NXBinaryFieldH5Implementation::
NXBinaryFieldH5Implementation(NXBinaryFieldH5Implementation &&o):
NXFieldH5Implementation(std::move(o)){

}

//------------------------------------------------------------------------------
//implementation of the destructor
NXBinaryFieldH5Implementation::~NXBinaryFieldH5Implementation(){

}

//=================Implementation of assignment operators=======================
//implementation of copy assignment operator
NXBinaryFieldH5Implementation &
NXBinaryFieldH5Implementation::operator=(const NXBinaryFieldH5Implementation &o){
	EXCEPTION_SETUP("NXBinaryFieldH5Implementation &"
					"NXBinaryFieldH5Implementation::operator="
					"(const NXBinaryFieldH5Implementation &o)");

	(NXFieldH5Implementation &)(*this) = (NXFieldH5Implementation &)o;
	return *this;
}

//------------------------------------------------------------------------------
//implementation of move assignment operator
NXBinaryFieldH5Implementation &
NXBinaryFieldH5Implementation::operator=(NXBinaryFieldH5Implementation &&o){
	EXCEPTION_SETUP("NXBinaryFieldH5Implementation &"
					"NXBinaryFieldH5Implementation::operator="
					"(NXBinaryFieldH5Implementation &&o)");

	(NXFieldH5Implementation &)(*this) = std::move((NXFieldH5Implementation &&)o);
	return *this;
}

//------------------------------------------------------------------------------
//implementation of the copy conversion assignment
NXBinaryFieldH5Implementation &
NXBinaryFieldH5Implementation::operator=(const NXFieldH5Implementation &o){
	EXCEPTION_SETUP("NXBinaryFieldH5Implementation &"
					"NXBinaryFieldH5Implementation::operator="
					"(const NXFieldH5Implementation &o)");

	if(o.getTypeID() != PNITypeID::BINARY){
		EXCEPTION_INIT(TypeError,"Field is not a binary field!");
		EXCEPTION_THROW();
	}

	(NXFieldH5Implementation &)(*this) = o;
	return *this;
}

//------------------------------------------------------------------------------
//implementation of the move conversion assignment
NXBinaryFieldH5Implementation &
NXBinaryFieldH5Implementation::operator=(NXFieldH5Implementation &&o){
	EXCEPTION_SETUP("NXBinaryFieldH5Implementation &"
					"NXBinaryFieldH5Implementation::operator="
					"(NXFieldH5Implementation &&o)");

	if(o.getTypeID() != PNITypeID::BINARY){
		EXCEPTION_INIT(TypeError,"Field is not a binary field!");
		EXCEPTION_THROW();
	}

	(NXFieldH5Implementation &)(*this) = std::move(o);
	return *this;
}

//------------------------------------------------------------------------------
//implementation of the copy conversion assignment
NXBinaryFieldH5Implementation &
NXBinaryFieldH5Implementation::operator=(const NXObjectH5Implementation &o){
	EXCEPTION_SETUP("NXBinaryFieldH5Implementation &"
					"NXBinaryFieldH5Implementation::operator="
					"(const NXObjectH5Implementation &o)");

	(NXFieldH5Implementation &)(*this) = o;
	if(getTypeID() != PNITypeID::BINARY){
		EXCEPTION_INIT(TypeError,"Object is not a binary field!");
		EXCEPTION_THROW();
	}

	return *this;
}

//------------------------------------------------------------------------------
//implementation of the move conversion assignment
NXBinaryFieldH5Implementation &
NXBinaryFieldH5Implementation::operator=(NXObjectH5Implementation &&o){
	EXCEPTION_SETUP("NXBinaryFieldH5Implementation &"
					"NXBinaryFieldH5Implementation::operator="
					"(NXObjectH5Implementation &&o)");

	(NXFieldH5Implementation &)(*this) = std::move(o);
	if(getTypeID() != PNITypeID::BINARY){
		EXCEPTION_INIT(TypeError,"Object is not a binary field!");
		EXCEPTION_THROW();
	}

	return *this;
}


//=================Implementation of IO methods=================================
//------------------------------------------------------------------------------
size_t NXBinaryFieldH5Implementation::size() const{
	EXCEPTION_SETUP("size_t NXBinaryFieldH5Implementation::size() const");

	return getShape().getDimension(0);

}

//------------------------------------------------------------------------------
//implementation of append binary buffer

void NXBinaryFieldH5Implementation::append(const Buffer<Binary> &b){
	EXCEPTION_SETUP("void NXBinaryFieldH5Implementation::"
					"append(const Buffer<Binary> &b)");

	herr_t err;

	//extend field along growth dimension
	_offset[0] = getShape().getDimension(0);
	_count[0] = b.getSize();
	_resize_dataset(b.getSize());

	hsize_t dims[] = {b.getSize()};
	hid_t elem_space = H5Screate_simple(1,dims,NULL);
	if(elem_space<0){
		EXCEPTION_INIT(H5DataSpaceError,"Cannot create data space!");
		EXCEPTION_THROW();
	}

	hid_t type = H5Dget_type(getId());

	H5Sselect_hyperslab(_filespace,H5S_SELECT_SET,_offset,NULL,_count,NULL);
	err = H5Dwrite(getId(),type,elem_space,_filespace,H5P_DEFAULT,(void*)b.getVoidPtr());
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error writing data!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
//implementation of set binary buffer
void NXBinaryFieldH5Implementation::set(size_t pos,const Buffer<Binary> &b){
	EXCEPTION_SETUP("void NXBinaryFieldH5Implementation::"
					"set(size_t pos,const Buffer<Binary> &b)");

	herr_t err;

	//extend field along growth dimension
	if(pos>=getShape().getDimension(0)){
		_resize_dataset(1+pos+b.getSize()-getShape().getDimension(0));
	}
	_offset[0] = pos;
	_count[0] = b.getSize();

	hsize_t dims[] = {b.getSize()};
	hid_t elem_space = H5Screate_simple(1,dims,NULL);
	hid_t type = H5Dget_type(getId());

	H5Sselect_hyperslab(_filespace,H5S_SELECT_SET,_offset,NULL,_count,NULL);
	err = H5Dwrite(getId(),type,elem_space,_filespace,H5P_DEFAULT,b.getVoidPtr());
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error writing data!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
//implementation of get binary buffer
void NXBinaryFieldH5Implementation::get(size_t pos,Buffer<Binary> &b){
	EXCEPTION_SETUP("void NXBinaryFieldH5Implementation::"
					"get(size_t pos,Buffer<Binary> &b)");

	if((pos+b.getSize())>getShape().getDimension(0)){
		EXCEPTION_INIT(IndexError,"Element + buffer size exceed field size!");
		EXCEPTION_THROW();
	}

	herr_t err;

	_offset[0] = pos;
	_count[0] = b.getSize();

	hsize_t dims[] = {b.getSize()};
	hid_t elem_space = H5Screate_simple(1,dims,NULL);
	hid_t type = H5Dget_type(getId());

	H5Sselect_hyperslab(_filespace,H5S_SELECT_SET,_offset,NULL,_count,NULL);
	err = H5Dread(getId(),type,elem_space,_filespace,H5P_DEFAULT,b.getVoidPtr());
	if(err<0){
		EXCEPTION_INIT(H5DataSetError,"Error reading data from field ["+getName()+"]!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
//implementation of get binary buffer
void NXBinaryFieldH5Implementation::get(Buffer<Binary> &b){
	EXCEPTION_SETUP("void NXBinaryFieldH5Implementation::"
					"get(Buffer<Binary> &o)");

	if(b.getSize()!=getShape().getDimension(0)){
		EXCEPTION_INIT(ShapeMissmatchError,"Buffer and field have different size!");
		EXCEPTION_THROW();
	}

	herr_t err;

	//clear all selections
	H5Sselect_none(_filespace);
	hid_t type = H5Dget_type(getId());

	err = H5Dread(getId(),type,H5S_ALL,H5S_ALL,H5P_DEFAULT,b.getVoidPtr());
	if(err < 0){
		EXCEPTION_INIT(H5DataSetError,"Error reading data from field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}

} /* namespace h5 */
} /* namespace nx */
} /* namespace pni */

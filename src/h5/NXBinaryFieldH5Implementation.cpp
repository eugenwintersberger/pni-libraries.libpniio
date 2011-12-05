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
}

//------------------------------------------------------------------------------
//implementation of set binary buffer
void NXBinaryFieldH5Implementation::set(size_t pos,const Buffer<Binary> &b){
	EXCEPTION_SETUP("void NXBinaryFieldH5Implementation::"
					"set(size_t pos,const Buffer<Binary> &b)");
}

//------------------------------------------------------------------------------
//implementation of get binary buffer
void NXBinaryFieldH5Implementation::get(size_t pos,Buffer<Binary> &o){
	EXCEPTION_SETUP("void NXBinaryFieldH5Implementation::"
					"get(size_t pos,Buffer<Binary> &o)");

}

//------------------------------------------------------------------------------
//implementation of get binary buffer
void NXBinaryFieldH5Implementation::get(Buffer<Binary> &o){
	EXCEPTION_SETUP("void NXBinaryFieldH5Implementation::"
					"get(Buffer<Binary> &o)");
}


} /* namespace h5 */
} /* namespace nx */
} /* namespace pni */

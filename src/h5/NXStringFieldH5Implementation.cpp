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
NXStringFieldH5Implementation::NXStringFieldH5Implementation(const NXFieldH5Implementation &o):
		NXFieldH5Implementation(o){

}

//------------------------------------------------------------------------------
//implementation of the copy conversion constructor
NXStringFieldH5Implementation::NXStringFieldH5Implementation(const NXObjectH5Implementation &o):
		NXFieldH5Implementation(o){

}

//------------------------------------------------------------------------------
//implementation of the move conversion constructor
NXStringFieldH5Implementation::NXStringFieldH5Implementation(NXFieldH5Implementation &&o):
		NXFieldH5Implementation(std::move(o)){

}

//------------------------------------------------------------------------------
//implementation of the move conversion constructor
NXStringFieldH5Implementation::NXStringFieldH5Implementation(NXObjectH5Implementation &&o):
		NXFieldH5Implementation(std::move(o)){

}

//------------------------------------------------------------------------------
//implementation of the copy constructor
NXStringFieldH5Implementation::NXStringFieldH5Implementation(const NXStringFieldH5Implementation &o):
		NXFieldH5Implementation(o){

}

//------------------------------------------------------------------------------
//implementation of the move constructor
NXStringFieldH5Implementation::NXStringFieldH5Implementation(NXStringFieldH5Implementation &&o):
		NXFieldH5Implementation(std::move(o)){

}

//------------------------------------------------------------------------------
//implementation of the destructor
NXStringFieldH5Implementation::~NXStringFieldH5Implementation(){

}

//=====================Implementation of the assignment operators===============
//implementation of the copy assignment operator
NXStringFieldH5Implementation &
NXStringFieldH5Implementation::operator=(const NXStringFieldH5Implementation &o){
	(NXFieldH5Implementation &)(*this) = (NXFieldH5Implementation &)o;
	return *this;
}

//------------------------------------------------------------------------------
//implementation of the move assignment operator
NXStringFieldH5Implementation &
NXStringFieldH5Implementation::operator=(NXStringFieldH5Implementation &&o){
	(NXFieldH5Implementation &)(*this) = std::move((NXFieldH5Implementation &&)o);
	return *this;
}

//------------------------------------------------------------------------------
//implementation of the copy conversion assignment
NXStringFieldH5Implementation &
NXStringFieldH5Implementation::operator=(const NXFieldH5Implementation &o){
	(NXFieldH5Implementation &)(*this) = o;
	return *this;
}

//------------------------------------------------------------------------------
//implementation of the copy conversion assignment
NXStringFieldH5Implementation &
NXStringFieldH5Implementation::operator=(const NXObjectH5Implementation &o){
	(NXFieldH5Implementation &)(*this) = o;
	return *this;
}

//------------------------------------------------------------------------------
//implementation of the move conversion assignment
NXStringFieldH5Implementation &
NXStringFieldH5Implementation::operator=(NXFieldH5Implementation &&o){
	(NXFieldH5Implementation &)(*this) = std::move(o);
	return *this;
}

//------------------------------------------------------------------------------
//implementation of the move conversion assignment
NXStringFieldH5Implementation &
NXStringFieldH5Implementation::operator=(NXObjectH5Implementation &&o){
	(NXFieldH5Implementation &)(*this) = std::move(o);
}

//================Implementation of IO functions================================
//get number of strings
UInt64 NXStringFieldH5Implementation::size() const{

}

//------------------------------------------------------------------------------
//append a string
void NXStringFieldH5Implementation::append(const String &o){

}

//------------------------------------------------------------------------------
//set a string
void NXStringFieldH5Implementation::set(const UInt64 &i,const String &o){

}

//------------------------------------------------------------------------------
//get a string
void NXStringFieldH5Implementation::get(const UInt64 &i,const String &o){

}

//------------------------------------------------------------------------------
//get a string
String &&NXStringFieldH5Implementation::get(const UInt64 &i){

}

//------------------------------------------------------------------------------
String &&NXStringFieldH5Implementation::get(const char &sep){

}

} /* namespace h5 */
} /* namespace nx */
} /* namespace pni */

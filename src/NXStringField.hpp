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
 * NXStringField.hpp
 *
 *  Created on: Dec 3, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef NXSTRINGFIELD_HPP_
#define NXSTRINGFIELD_HPP_

#include <pni/utils/Types.hpp>

#include "NXField.hpp"

namespace pni{
namespace nx{

//need to do some trick here to get the stream operators overloaded
template<typename Imp> class NXStringField;
template<typename Imp> NXStringField<Imp> &operator<<(NXStringField<Imp> &o,const String &s);
template<typename Imp> NXStringField<Imp> &operator>>(NXStringField<Imp> &o,String &s);


template<typename Imp>
class NXStringField:public NXField<Imp>{
public:
	//! default constructor
	NXStringField();
	//! conversion copy constructor
	NXStringField(const NXField<Imp> &o);
	//! conversion copy constructor
	NXStringField(const NXObject<typename NXObject<Imp>::ObjectImp > &o);
	//! copy constructor
	NXStringField(const NXStringField<Imp> &o);
	//! move constructor
	NXStringField(NXStringField<Imp> &&o);
	//! conversion move constructor
	NXStringField(NXField<Imp> &&o);
	//! conversion move constructor
	NXStringField(NXObject<typename NXObject<Imp>::ObjectImp > &&o);
	//! construct from implementation
	NXStringField(Imp &&o):NXField<Imp>(std::move(o)){}
	//! destructor
	virtual ~NXStringField();

	//!copy assignment
	NXStringField<Imp> &operator=(const NXStringField<Imp> &o);
	//! copy conversion assignment
	NXStringField<Imp> &operator=(const NXObject<typename NXObject<Imp>::ObjectImp > &o);
	//! move assignment
	NXStringField<Imp> &operator=(NXStringField<Imp> &&o);
	//! move conversion operator
	NXStringField<Imp> &operator=(NXObject<typename NXObject<Imp>::ObjectImp > &&o);

	//!append array
	void append(const String &s);

    //!number of strings
    UInt64 size() const;

	//!get data
	void get(const UInt64 &i,String &o);
	String get(const UInt64 &i);
	String get(const char &sep);

	//! set data
	void set(const UInt64 &i,const String &s);


	friend NXStringField<Imp> &operator<< <> (NXStringField<Imp> &o,const String &s);
	friend NXStringField<Imp> &operator>> <> (NXStringField<Imp> &o,String &s);

};

//=================Constructor destructor implementation=======================
//implementation of the default constructor
template<typename Imp> NXStringField<Imp>::NXStringField():NXField<Imp>(){

}

//------------------------------------------------------------------------------
//implementation of the copy constructor
template<typename Imp>
NXStringField<Imp>::NXStringField(const NXStringField<Imp> &o):NXField<Imp>(o){

}

//-----------------------------------------------------------------------------
//implementation of conversion copy constructor
template<typename Imp>
NXStringField<Imp>::NXStringField(const NXField<Imp> &o):NXField<Imp>(o){

}

//-----------------------------------------------------------------------------
//implementation of conversion copy constructor
template<typename Imp>
NXStringField<Imp>::NXStringField(const NXObject<typename NXObject<Imp>::ObjectImp > &o)
:NXField<Imp>(o){

}

//-----------------------------------------------------------------------------
//implementation of the move constructor
template<typename Imp>
NXStringField<Imp>::NXStringField(NXStringField<Imp> &&o):NXField<Imp>(std::move(o)){

}

//-----------------------------------------------------------------------------
//implementation of the move conversion constructor
template<typename Imp>
NXStringField<Imp>::NXStringField(NXField<Imp> &&o):NXField<Imp>(std::move(o)){

}

//-----------------------------------------------------------------------------
//implementation of the move conversion constructor
template<typename Imp>
NXStringField<Imp>::NXStringField(NXObject<typename NXObject<Imp>::ObjectImp > &&o)
:NXField<Imp>(std::move(o)){

}

//-----------------------------------------------------------------------------
//implementation of the destructor
template<typename Imp> NXStringField<Imp>::~NXStringField(){

}

//===========Implementatoin of assignment operators============================
//implementation of copy assignment
template<typename Imp> NXStringField<Imp> &
NXStringField<Imp>::operator=(const NXStringField<Imp> &o){
	(NXField<Imp> &)(*this) = (NXField<Imp> &)o;
	return *this;
}

//------------------------------------------------------------------------------
//implementatoin of move assignment
template<typename Imp> NXStringField<Imp> &
NXStringField<Imp>::operator=(NXStringField<Imp> &&o){
	(NXField<Imp> &)(*this) = std::move((NXField<Imp> &)o);
	return *this;
}

//-----------------------------------------------------------------------------
//implementatoin of the conversion copy assignment
template<typename Imp> NXStringField<Imp> &
NXStringField<Imp>::operator=(const NXObject<typename NXObject<Imp>::ObjectImp > &o){
	EXCEPTION_SETUP("template<typename Imp> NXStringField<Imp> &"
					"NXStringField<Imp>::operator="
					"(const NXObject<typename NXObject<Imp>::ObjectImp > &o)");
	try{
		(NXField<Imp> &)(*this) = o;
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Object cannot be assigned!");
		EXCEPTION_THROW();
	}
	return *this;
}

//------------------------------------------------------------------------------
//implementation of the conversion move assignment
template<typename Imp> NXStringField<Imp> &
NXStringField<Imp>::operator=(NXObject<typename NXObject<Imp>::ObjectImp > &&o){
	EXCEPTION_SETUP("template<typename Imp> NXStringField<Imp> &"
					"NXStringField<Imp>::operator="
					"(NXObject<typename NXObject<Imp>::ObjectImp > &&o)");

	try{
		(NXField<Imp> &)(*this) = std::move(o);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Object cannot be assigned!");
		EXCEPTION_THROW();
	}
	return *this;
}

//=======================Implementation of IO methods===========================
//implementation of append string
template<typename Imp> void NXStringField<Imp>::append(const String &s){
	EXCEPTION_SETUP("template<typename Imp> void NXStringField<Imp>::append(const String &s)");

	try{
		this->getImplementation().append(s);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error writing string to field ["+this->getName()+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
//implementation of get string
template<typename Imp> void NXStringField<Imp>::get(const UInt64 &i,String &s){
	EXCEPTION_SETUP("template<typename Imp> void NXStringField<Imp>::get(const UInt64 &i,String &s)");

	try{
		this->getImplementation().get(i,s);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error reading string data from field ["+this->getName()+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
//implementation of get string
template<typename Imp> String NXStringField<Imp>::get(const UInt64 &i){
	EXCEPTION_SETUP("template<typename Imp> String &&NXStringField<Imp>::"
					"get(const UInt64 &i)");
	String s;

	try{
		s = this->getImplementation().get(i);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error reading string from field ["+this->getName()+"]!");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Imp> String NXStringField<Imp>::get(const char &sep){
	EXCEPTION_SETUP("template<typename Imp> String NXStringField<Imp>::"
					"get(const char &sep)");
	String s;
	try{
		s= this->getImplementation().get(sep);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error reaeding string from field ["
					  +this->getName()+"]!");
		EXCEPTION_THROW();
	}

	return s;
}

//------------------------------------------------------------------------------
//! set data
template<typename Imp> void NXStringField<Imp>::set(const UInt64 &i,const String &s){
	EXCEPTION_SETUP("template<typename Imp> void NXStringField<Imp>::"
					"set(const UInt64 &i,const String &s)");

	try{
		this->getImplementation().set(i,s);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Cannot write data!");
		EXCEPTION_THROW();
	}
}

//-----------------------------------------------------------------------------
template<typename Imp> UInt64 NXStringField<Imp>::size() const{
    return this->getShape().getDimension(0);
}

//=============Implementation of stream operators==============================
template<typename Imp>
NXStringField<Imp> &operator<<(NXStringField<Imp> &o,const String &s){
	o.append(s);
	return o;
}

//------------------------------------------------------------------------------
template<typename Imp>
NXStringField<Imp> &operator>>(NXStringField<Imp> &o,String &s){
	o.get(o._get_read_stream_pos(),s);
	o._increment_read_stream_pos();
	return o;
}


//end of namespace
}
}


#endif /* NXSTRINGFIELD_HPP_ */

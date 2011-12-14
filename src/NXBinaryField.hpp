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
 * NXBinaryField.hpp
 *
 *  Created on: Dec 3, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef NXBINARYFIELD_HPP_
#define NXBINARYFIELD_HPP_

#include <pni/utils/Types.hpp>
#include <pni/utils/Buffer.hpp>

#include "NXField.hpp"

namespace pni{
namespace nx{

//need to do some trick here to get the stream operators overloaded
template<typename Imp> class NXBinaryField;
template<typename Imp> NXBinaryField<Imp> &operator<<(NXBinaryField<Imp> &o,const Buffer<Binary> &b);
template<typename Imp> NXBinaryField<Imp> &operator>>(NXBinaryField<Imp> &o,Buffer<Binary> &s);


template<typename Imp>
class NXBinaryField:public NXField<Imp>{
public:
	//! default constructor
	NXBinaryField();
	//! conversion copy constructor
	NXBinaryField(const NXField<Imp> &o);
	//! conversion copy constructor
	NXBinaryField(const NXObject<typename NXObject<Imp>::ObjectImp > &o);
	//! copy constructor
	NXBinaryField(const NXBinaryField<Imp> &o);
	//! move constructor
	NXBinaryField(NXBinaryField<Imp> &&o);
	//! conversion move constructor
	NXBinaryField(NXField<Imp> &&o);
	//! conversion move constructor
	NXBinaryField(NXObject<typename NXObject<Imp>::ObjectImp > &&o);
	//! construct from implementation
	NXBinaryField(Imp &&o):NXField<Imp>(std::move(o)){}
	//! destructor
	virtual ~NXBinaryField();

	//!copy assignment
	NXBinaryField<Imp> &operator=(const NXBinaryField<Imp> &o);
	//! copy conversion assignment
	NXBinaryField<Imp> &operator=(const NXObject<typename NXObject<Imp>::ObjectImp > &o);
	//! move assignment
	NXBinaryField<Imp> &operator=(NXBinaryField<Imp> &&o);
	//! move conversion operator
	NXBinaryField<Imp> &operator=(NXObject<typename NXObject<Imp>::ObjectImp > &&o);

    //!return the size of the binary field
    size_t size() const{
        return this->getShape().getSize();
    }

	//!append array
	void append(const Buffer<Binary> &s);

	//!get data
	void get(const UInt64 &i,Buffer<Binary> &o);
	void get(Buffer<Binary> &o);
	//String get(const UInt64 &i);
	//String get(const char &sep);

	//! set data
	void set(const UInt64 &i,const Buffer<Binary> &s);


	friend NXBinaryField<Imp> &operator<< <> (NXBinaryField<Imp> &o,const Buffer<Binary> &s);
	friend NXBinaryField<Imp> &operator>> <> (NXBinaryField<Imp> &o,Buffer<Binary> &s);

};

//=================Constructor destructor implementation=======================
//implementation of the default constructor
template<typename Imp> NXBinaryField<Imp>::NXBinaryField():NXField<Imp>(){

}

//------------------------------------------------------------------------------
//implementation of the copy constructor
template<typename Imp>
NXBinaryField<Imp>::NXBinaryField(const NXBinaryField<Imp> &o):NXField<Imp>(o){

}

//-----------------------------------------------------------------------------
//implementation of conversion copy constructor
template<typename Imp>
NXBinaryField<Imp>::NXBinaryField(const NXField<Imp> &o):NXField<Imp>(o){

}

//-----------------------------------------------------------------------------
//implementation of conversion copy constructor
template<typename Imp>
NXBinaryField<Imp>::NXBinaryField(const NXObject<typename NXObject<Imp>::ObjectImp > &o)
:NXField<Imp>(o){

}

//-----------------------------------------------------------------------------
//implementation of the move constructor
template<typename Imp>
NXBinaryField<Imp>::NXBinaryField(NXBinaryField<Imp> &&o):NXField<Imp>(std::move(o)){

}

//-----------------------------------------------------------------------------
//implementation of the move conversion constructor
template<typename Imp>
NXBinaryField<Imp>::NXBinaryField(NXField<Imp> &&o):NXField<Imp>(std::move(o)){

}

//-----------------------------------------------------------------------------
//implementation of the move conversion constructor
template<typename Imp>
NXBinaryField<Imp>::NXBinaryField(NXObject<typename NXObject<Imp>::ObjectImp > &&o)
:NXField<Imp>(std::move(o)){

}

//-----------------------------------------------------------------------------
//implementation of the destructor
template<typename Imp> NXBinaryField<Imp>::~NXBinaryField(){

}

//===========Implementatoin of assignment operators============================
//implementation of copy assignment
template<typename Imp> NXBinaryField<Imp> &
NXBinaryField<Imp>::operator=(const NXBinaryField<Imp> &o){
	(NXField<Imp> &)(*this) = (NXField<Imp> &)o;
	return *this;
}

//------------------------------------------------------------------------------
//implementatoin of move assignment
template<typename Imp> NXBinaryField<Imp> &
NXBinaryField<Imp>::operator=(NXBinaryField<Imp> &&o){
	(NXField<Imp> &)(*this) = std::move((NXField<Imp> &)o);
	return *this;
}

//-----------------------------------------------------------------------------
//implementatoin of the conversion copy assignment
template<typename Imp> NXBinaryField<Imp> &
NXBinaryField<Imp>::operator=(const NXObject<typename NXObject<Imp>::ObjectImp > &o){
	EXCEPTION_SETUP("template<typename Imp> NXBinaryField<Imp> &"
					"NXBinaryField<Imp>::operator="
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
template<typename Imp> NXBinaryField<Imp> &
NXBinaryField<Imp>::operator=(NXObject<typename NXObject<Imp>::ObjectImp > &&o){
	EXCEPTION_SETUP("template<typename Imp> NXBinaryField<Imp> &"
					"NXBinaryField<Imp>::operator="
					"(NXObject<typename NXObject<Imp>::ObjectImp > &&o)");

	try{
		(NXField<Imp> &)(*this) = std::move(o);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Object cannot be assigned!");
		EXCEPTION_THROW();
	}
	return *this;
}

//------------------------------------------------------------------------------
//implementation of append buffer
template<typename Imp>
void NXBinaryField<Imp>::append(const Buffer<Binary> &b){
	EXCEPTION_SETUP("template<typename Imp> void NXBinaryField<Imp>::"
					"append(const Buffer<Binary> &s)");

	try{
		this->implementation().append(b);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Cannot append data to binary field!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
//implementation of get data
template<typename Imp>
void NXBinaryField<Imp>::get(const UInt64 &i,Buffer<Binary> &o){
	EXCEPTION_SETUP("template<typename Imp> void NXBinaryField<Imp>::"
					"get(const UInt64 &i,Buffer<Binary> &o)");

	try{
		this->implementation().get(i,o);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Cannot get data from binary field ["+this->name()+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
//implementation of get data
template<typename Imp> void NXBinaryField<Imp>::get(Buffer<Binary> &b){
	EXCEPTION_SETUP("template<typename Imp> void NXBinaryField<Imp>::"
					"get(Buffer<Binary> &b)");

	try{
		this->implementation().get(b);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error reading data from binary field ["+this->name()+"]!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
//implementation of set data
template<typename Imp>
void NXBinaryField<Imp>::set(const UInt64 &i,const Buffer<Binary> &b){
	EXCEPTION_SETUP("template<typename Imp> void NXBinaryField<Imp>::"
					"set(const UInt64 &i,const Buffer<Binary> &s)");

	try{
		this->implementation().set(i,b);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error reading data from binary field ["+this->name()+"]!");
		EXCEPTION_THROW();
	}
}

template<typename Imp> NXBinaryField<Imp> &operator<<(NXBinaryField<Imp> &o,const Buffer<Binary> &b){
	o.append(b);
	return o;
}
template<typename Imp> NXBinaryField<Imp> &operator>>(NXBinaryField<Imp> &o,Buffer<Binary> &s){
	o.get(o._get_read_stream_pos(),s);
	o._increment_read_stream_pos();
	return o;
}


//end of namespace
}
}




#endif /* NXBINARYFIELD_HPP_ */

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
 * NXNumericField.hpp
 *
 *  Created on: Dec 3, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef NXNUMERICFIELD_HPP_
#define NXNUMERICFIELD_HPP_

#include <pni/utils/Array.hpp>
#include <pni/utils/Scalar.hpp>
#include <pni/utils/Types.hpp>

#include "NXField.hpp"

namespace pni{
namespace nx{

//need to do some trick here to get the stream operators overloaded
template<typename Imp> class NXNumericField;
template<typename Imp> NXNumericField<Imp> &operator<<(NXNumericField<Imp> &o,const ScalarObject &s);
template<typename Imp> NXNumericField<Imp> &operator<<(NXNumericField<Imp> &o,const ArrayObject &a);
template<typename Imp> NXNumericField<Imp> &operator>>(NXNumericField<Imp> &o,ScalarObject &s);
template<typename Imp> NXNumericField<Imp> &operator>>(NXNumericField<Imp> &o,ArrayObject &s);


template<typename Imp>
class NXNumericField:public NXField<Imp>{
private:
	bool _check_unit(const NumericObject &o) const;
public:
	//! default constructor
	NXNumericField();
	//! conversion copy constructor
	NXNumericField(const NXField<Imp> &o);
	//! conversion copy constructor
	NXNumericField(const NXObject<typename NXObject<Imp>::ObjectImp > &o);
	//! copy constructor
	NXNumericField(const NXNumericField<Imp> &o);
	//! move constructor
	NXNumericField(NXNumericField<Imp> &&o);
	//! conversion move constructor
	NXNumericField(NXField<Imp> &&o);
	//! conversion move constructor
	NXNumericField(NXObject<typename NXObject<Imp>::ObjectImp > &&o);
	//! construct from implementation
	NXNumericField(Imp &&o):NXField<Imp>(std::move(o)){}
	//! destructor
	virtual ~NXNumericField();

	//!copy assignment
	NXNumericField<Imp> &operator=(const NXNumericField<Imp> &o);
	//! copy conversion assignment
	NXNumericField<Imp> &operator=(const NXObject<typename NXObject<Imp>::ObjectImp > &o);
	//! move assignment
	NXNumericField<Imp> &operator=(NXNumericField<Imp> &&o);
	//! move conversion operator
	NXNumericField<Imp> &operator=(NXObject<typename NXObject<Imp>::ObjectImp > &&o);

	//!append array
	void append(const ArrayObject &a);
	//!append scalar
	void append(const ScalarObject &a);

	//!get data
	void get(const UInt64 &i,ArrayObject &o);
	void get(const UInt64 &i,ScalarObject &o);
	void get(ArrayObject &o);
	void get(ScalarObject &o);

	//! set data
	void set(const UInt64 &i,const ArrayObject &o);
	void set(const UInt64 &i,const ScalarObject &o);

    UInt32 size() const{
        return this->getShape().getDimension(0);
    }

	friend NXNumericField<Imp> &operator<< <> (NXNumericField<Imp> &o,const ScalarObject &s);
	friend NXNumericField<Imp> &operator<< <> (NXNumericField<Imp> &o,const ArrayObject &a);

	friend NXNumericField<Imp> &operator>> <> (NXNumericField<Imp> &o,ScalarObject &s);
	friend NXNumericField<Imp> &operator>> <> (NXNumericField<Imp> &o,ArrayObject &s);

};

//================Implementation of private methods============================
//implement unit check
template<typename Imp>
bool NXNumericField<Imp>::_check_unit(const NumericObject &o) const{
	String fieldunit;
	this->getAttribute("units",fieldunit);
	if(o.unit() == fieldunit) return true;

	return false;
}

//=================Constructor destructor implementation=======================
//implementation of the default constructor
template<typename Imp> NXNumericField<Imp>::NXNumericField()
		:NXField<Imp>(){

}

//------------------------------------------------------------------------------
//implementation of the copy constructor
template<typename Imp>
NXNumericField<Imp>::NXNumericField(const NXNumericField<Imp> &o)
:NXField<Imp>(o){

}

//-----------------------------------------------------------------------------
//implementation of conversion copy constructor
template<typename Imp>
NXNumericField<Imp>::NXNumericField(const NXField<Imp> &o)
:NXField<Imp>(o){

}

//-----------------------------------------------------------------------------
//implementation of conversion copy constructor
template<typename Imp>
NXNumericField<Imp>::NXNumericField(const NXObject<typename NXObject<Imp>::ObjectImp > &o)
:NXField<Imp>(o){

}

//-----------------------------------------------------------------------------
//implementation of the move constructor
template<typename Imp>
NXNumericField<Imp>::NXNumericField(NXNumericField<Imp> &&o)
:NXField<Imp>(std::move(o)){

}

//-----------------------------------------------------------------------------
//implementation of the move conversion constructor
template<typename Imp>
NXNumericField<Imp>::NXNumericField(NXField<Imp> &&o)
:NXField<Imp>(std::move(o)){

}

//-----------------------------------------------------------------------------
//implementation of the move conversion constructor
template<typename Imp>
NXNumericField<Imp>::NXNumericField(NXObject<typename NXObject<Imp>::ObjectImp > &&o)
:NXField<Imp>(std::move(o)){

}

//-----------------------------------------------------------------------------
//implementation of the destructor
template<typename Imp> NXNumericField<Imp>::~NXNumericField(){

}

//===========Implementatoin of assignment operators============================
//implementation of copy assignment
template<typename Imp> NXNumericField<Imp> &
NXNumericField<Imp>::operator=(const NXNumericField<Imp> &o){
	(NXField<Imp> &)(*this) = (NXField<Imp> &)o;
	return *this;
}

//------------------------------------------------------------------------------
//implementatoin of move assignment
template<typename Imp> NXNumericField<Imp> &
NXNumericField<Imp>::operator=(NXNumericField<Imp> &&o){
	(NXField<Imp> &)(*this) = std::move((NXField<Imp> &)o);
	return *this;
}

//-----------------------------------------------------------------------------
//implementatoin of the conversion copy assignment
template<typename Imp> NXNumericField<Imp> &
NXNumericField<Imp>::operator=(const NXObject<typename NXObject<Imp>::ObjectImp > &o){
	(NXField<Imp> &)(*this) = o;
	return *this;
}

//------------------------------------------------------------------------------
//implementation of the conversion move assignment
template<typename Imp> NXNumericField<Imp> &
NXNumericField<Imp>::operator=(NXObject<typename NXObject<Imp>::ObjectImp > &&o){
	(NXField<Imp> &)(*this) = std::move(o);
	return *this;
}

//==============Implementatoin of IO methods====================================
template<typename Imp>
void NXNumericField<Imp>::append(const ArrayObject &o){
	EXCEPTION_SETUP("template<typename Imp> void NXNumericField<Imp>::"
					"append(const ArrayObject &o)");

	//raise an exception if the array is not allocated
	if(!o.is_allocated()){
		EXCEPTION_INIT(NXFieldError,"Array not allocated!");
		EXCEPTION_THROW();
	}

	//perform unit check
	if(!_check_unit(o)){
		EXCEPTION_INIT(NXFieldError,"Units do not match!");
		EXCEPTION_THROW();
	}

	if(this->getShape().rank()==o.shape().rank()){
		//array and field have the same rank

		if((this->getElementShape().rank()==0) && (o.shape().rank()==1)){
			//an array will be appended as a block to a field that was
			//originally created for scalar values

			try{
				this->getImplementation().append(o,true);
			}catch(...){
				EXCEPTION_INIT(NXFieldError,"Error writing data!");
				EXCEPTION_THROW();
			}
			return;
		}

		//array block
		for(UInt64 i=1;i<o.shape().rank();i++){
			if(this->getShape().dim(i)!=o.shape().dim(i)){
				EXCEPTION_INIT(ShapeMissmatchError,"Field and array shape do not match!");
				EXCEPTION_THROW();
			}
		}

		try{
			this->getImplementation().append(o,true);
		}catch(...){
			EXCEPTION_INIT(NXFieldError,"Error writing data!");
			EXCEPTION_THROW();
		}
		return;
	}


	//the array is an element of the field
	if(this->getElementShape()==o.shape()){
		try{
			this->getImplementation().append(o,false);
		}catch(...){
			EXCEPTION_INIT(NXFieldError,"Error writing data!");
			EXCEPTION_THROW();
		}
	}
}

//------------------------------------------------------------------------------
//implementation append scalar
template<typename Imp>
void NXNumericField<Imp>::append(const ScalarObject &o){
	EXCEPTION_SETUP("template<typename Imp> void NXNumericField<Imp>::"
					"append(const ScalarObject &o)");

	if(this->getElementShape().rank()!=0){
		EXCEPTION_INIT(NXFieldError,"Object rank does not match!");
		EXCEPTION_THROW();
	}

	//check units
	if(!this->_check_unit(o)){
		EXCEPTION_INIT(NXFieldError,"Units do not match!");
		EXCEPTION_THROW();
	}

	try{
		this->getImplementation().append(o,false);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Cannot append data to field ["+this->getName()+"]!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
//implementation of array get
template<typename Imp>
void NXNumericField<Imp>::get(const UInt64 &index,ArrayObject &o){
	EXCEPTION_SETUP("template<typename Imp> void NXNumericField<Imp>::"
					"get(const UInt64 &i,ArrayObject &o)");

	if(!o.is_allocated()){
		EXCEPTION_INIT(NXFieldError,"Array not allocated!");
		EXCEPTION_THROW();
	}

	if(!this->_check_unit(o)){
		EXCEPTION_INIT(NXFieldError,"Units do not match!");
		EXCEPTION_THROW();
	}

	if(this->getShape().rank()==o.shape().rank()){
		//array and field have the same rank

		if((this->getElementShape().rank()==0) && (o.shape().rank()==1)){
			//an array will be appended as a block to a field that was
			//originally created for scalar values

			try{
				this->getImplementation().get(index,o,true);
			}catch(...){
				EXCEPTION_INIT(NXFieldError,"Error writing data!");
				EXCEPTION_THROW();
			}
			return;
		}

		//array block
		for(size_t i=1;i<o.shape().rank();i++){
			if(this->getShape().dim(i)!=o.shape().dim(i)){
				EXCEPTION_INIT(ShapeMissmatchError,"Field and array shape do not match!");
				EXCEPTION_THROW();
			}
		}

		try{
			this->getImplementation().get(index,o,true);
		}catch(...){
			EXCEPTION_INIT(NXFieldError,"Error writing data!");
			EXCEPTION_THROW();
		}
		return;
	}


	//the array is an element of the field
	if(this->getElementShape()==o.shape()){
		try{
			this->getImplementation().get(index,o,false);
		}catch(...){
			EXCEPTION_INIT(NXFieldError,"Error reading data!");
			EXCEPTION_THROW();
		}
	}

}

//------------------------------------------------------------------------------
//implementation of scalar get
template<typename Imp>
void NXNumericField<Imp>::get(const UInt64 &i,ScalarObject &o){
	EXCEPTION_SETUP("template<typename Imp> void NXNumericField<Imp>::"
					"get(const UInt64 &i,ScalarObject &o)");

	if(!this->_check_unit(o)){
		EXCEPTION_INIT(NXFieldError,"Units do not match!");
		EXCEPTION_THROW();
	}

	try{
		this->getImplementation().get(i,o,false);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Cannot read data!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
//implementation of get all for array
template<typename Imp> void NXNumericField<Imp>::get(ArrayObject &o){
	EXCEPTION_SETUP("template<typename Imp> void NXNumericField<Imp>::"
					"get(ArrayObject &o)");

	if(!o.is_allocated()){
		EXCEPTION_INIT(NXFieldError,"Array is not allocated!");
		EXCEPTION_THROW();
	}

	if(!this->_check_unit(o)){
		EXCEPTION_INIT(NXFieldError,"Units do not match!");
		EXCEPTION_THROW();
	}

	if(this->getShape()!=o.shape()){
		EXCEPTION_INIT(ShapeMissmatchError,"Field and array shape do not match!");
		EXCEPTION_THROW();
	}

	try{
		this->getImplementation().get(o);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error reading data!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
//implementation of get all for scalar
template<typename Imp> void NXNumericField<Imp>::get(ScalarObject &o){
	EXCEPTION_SETUP("template<typename Imp> void NXNumericField<Imp>::"
					"get(ScalarObject &o)");

	if(!this->_check_unit(o)){
		EXCEPTION_INIT(NXFieldError,"Units do not match!");
		EXCEPTION_THROW();
	}

	if((this->getShape().getRank()!=1)||
	   (this->getShape().getDimension(0)!=1)){
		EXCEPTION_INIT(NXFieldError,"Fields holds more than one value!");
		EXCEPTION_THROW();
	}

	try{
		this->getImplementation().get(o);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error reading data!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
//implementation of array set
template<typename Imp>
void NXNumericField<Imp>::set(const UInt64 &index,const ArrayObject &o){
	EXCEPTION_SETUP("template<typename Imp> void NXNumericField<Imp>::"
					"set(const UInt64 &i,const ArrayObject &o)");

	if(!o.is_allocated()){
		EXCEPTION_INIT(NXFieldError,"Array not allocated!");
		EXCEPTION_THROW();
	}

	if(!this->_check_unit(o)){
		EXCEPTION_INIT(NXFieldError,"Units do not match!");
		EXCEPTION_THROW();
	}

	if(this->getShape().rank()==o.shape().rank()){
		//array and field have the same rank

		if((this->getElementShape().rank()==0) && (o.shape().rank()==1)){
			//an array will be appended as a block to a field that was
			//originally created for scalar values

			try{
				this->getImplementation().set(index,o,true);
			}catch(...){
				EXCEPTION_INIT(NXFieldError,"Error writing data!");
				EXCEPTION_THROW();
			}
			return;
		}

		//array block
		for(size_t i=1;i<o.shape().rank();i++){
			if(this->getShape().dim(i)!=o.shape().dim(i)){
				EXCEPTION_INIT(ShapeMissmatchError,"Field and array shape do not match!");
				EXCEPTION_THROW();
			}
		}

		try{
			this->getImplementation().set(index,o,true);
		}catch(...){
			EXCEPTION_INIT(NXFieldError,"Error writing data!");
			EXCEPTION_THROW();
		}
		return;
	}


	//the array is an element of the field
	if(this->getElementShape()==o.shape()){
		try{
			this->getImplementation().set(index,o,false);
		}catch(...){
			EXCEPTION_INIT(NXFieldError,"Error reading data!");
			EXCEPTION_THROW();
		}
	}




}

//------------------------------------------------------------------------------
//implemenation of scalar set
template<typename Imp>
void NXNumericField<Imp>::set(const UInt64 &i,const ScalarObject &o){
	EXCEPTION_SETUP("template<typename Imp> void NXNumericField<Imp>::"
					"set(const UInt64 &i,const ScalarObject &o)");

	if(!this->_check_unit(o)){
		EXCEPTION_INIT(NXFieldError,"Units do not match!");
		EXCEPTION_THROW();
	}

	try{
		this->getImplementation().set(i,o,false);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error writing data!");
		EXCEPTION_THROW();
	}
}

//=============Implementation of stream operators==============================
template<typename Imp>
NXNumericField<Imp> &operator<<(NXNumericField<Imp> &o,const ScalarObject &s){
	o.append(s);
	return o;
}

//------------------------------------------------------------------------------
template<typename Imp>
NXNumericField<Imp> &operator<<(NXNumericField<Imp> &o,const ArrayObject &a){
	o.append(a);
	return o;
}

//------------------------------------------------------------------------------
template<typename Imp>
NXNumericField<Imp> &operator>>(NXNumericField<Imp> &o,ScalarObject &s){
	o.get(o._read_stream_pos,s);
	o._read_stream_pos++;
	return o;
}

//------------------------------------------------------------------------------
template<typename Imp>
NXNumericField<Imp> &operator>>(NXNumericField<Imp> &o,ArrayObject &a){
	o.get(o._read_stream_pos,a);
	o._read_stream_pos++;
	return o;
}


//end of namespace
}
}




#endif /* NXNUMERICFIELD_HPP_ */

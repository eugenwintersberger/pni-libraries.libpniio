/*
 * Declaration of the NXfield template
 *
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
 *
 * Declaration of the NXfield template
 *
 * Created on: Jul 3, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXFIELD_HPP_
#define NXFIELD_HPP_

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/ScalarObject.hpp>
#include <pni/utils/Scalar.hpp>
#include <pni/utils/ArrayShape.hpp>
#include <pni/utils/ArrayObject.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/NumericObject.hpp>

#include "NXObject.hpp"
#include "NXExceptions.hpp"
#include "NXSelection.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{

//need to do some trick here to get the stream operators overloaded
template<typename Imp> class NXField;
template<typename Imp> NXField<Imp> &operator<<(NXField<Imp> &o,const ScalarObject &s);
template<typename Imp> NXField<Imp> &operator<<(NXField<Imp> &o,const ArrayObject &a);
template<typename Imp> NXField<Imp> &operator<<(NXField<Imp> &o,const String &s);
template<typename Imp> NXField<Imp> &operator>>(NXField<Imp> &o,ScalarObject &s);
template<typename Imp> NXField<Imp> &operator>>(NXField<Imp> &o,ArrayObject &s);
template<typename Imp> NXField<Imp> &operator>>(NXField<Imp> &o,String &s);

template<typename Imp>
class NXField:public NXObject<Imp> {
private:
	UInt64 _read_stream_pos;


protected:
	//void write(const void *ptr) const;
	//void read(void *ptr) const;
public:
	typedef NXSelection<typename NXImpMap<Imp::IMPCODE>::SelectionImplementation > Selection;
	typedef boost::shared_ptr<NXField<Imp> > sptr;
	NXField();
	//! copy constructor
	NXField(const NXField<Imp> &);
	//! move constructor
	NXField(NXField<Imp> &&o);
	virtual ~NXField();

	//! copy assignment
	NXField<Imp> &operator=(const NXField<Imp> &);

	//! move assignment
	NXField<Imp> &operator=(NXField<Imp> &&o);

	//inquery of a field
	UInt32 getRank() const{
		return this->getImplementation().getRank();
	}

	//! get dimension of a field
	UInt32 getDimension(UInt32 i) const {
		return this->getImplementation().getDimension(i);
	}

	//need a function here to get an array rank from a field
	virtual const ArrayShape &getShape() const{
		return this->getImplementation().getShape();
	}

	virtual const ArrayShape &getElementShape() const {
		return this->getImplementation().getElementShape();
	}

	virtual UInt32 getElementRank() const {
		return this->getImplementation().getElementRank();
	}

	//get the type ID
	virtual PNITypeID getTypeID() const {
		return this->getImplementation().getTypeID();
	}

	virtual UInt64 getSize() const {
		return this->getImplementation().getSize();
	}

	virtual String getName() const {
		return this->getImplementation().getName();
	}

	//need methods to access data stored in the field
	void append(const ArrayObject &a);
	void append(const ScalarObject &s);
	void append(const String &s);

	void insert(const UInt64 &i,const ArrayObject &s);
	void insert(const UInt64 &i,const ScalarObject &s);
	void insert(const UInt64 &i,const String &s);

	void get(const UInt64 &i,ArrayObject &a);
	void get(const UInt64 &i,ScalarObject &s);
	void get(const UInt64 &i,String &s);


	void close();

	void resetReadStreamPosition() {
		_read_stream_pos = 0;
	}

	friend NXField<Imp> &operator<< <> (NXField<Imp> &o,const ScalarObject &s);
	friend NXField<Imp> &operator<< <> (NXField<Imp> &o,const ArrayObject &a);
	friend NXField<Imp> &operator<< <> (NXField<Imp> &o,const String &s);

	friend NXField<Imp> &operator>> <> (NXField<Imp> &o,ScalarObject &s);
	friend NXField<Imp> &operator>> <> (NXField<Imp> &o,ArrayObject &s);
	friend NXField<Imp> &operator>> <> (NXField<Imp> &o,String &s);

};

//--------------constructors and destructors------------------------------------

template<typename Imp> NXField<Imp>::NXField():NXObject<Imp>() {
	_read_stream_pos = 0;
}

template<typename Imp> NXField<Imp>::NXField(const NXField<Imp> &o)
		:NXObject<Imp>(o){
	EXCEPTION_SETUP("template<typename Imp> NXField<Imp>::NXField(const NXField<Imp> &o)");
	try{
		//this->setImplementation(o.getImplementation());
		_read_stream_pos = 0;
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error in copy constructor for NXField!");
		EXCEPTION_THROW();
	}
}

template<typename Imp> NXField<Imp>::NXField(NXField<Imp> &&o){
	EXCEPTION_SETUP("template<typename Imp> NXField<Imp>::NXField(NXField<Imp> &&o)");
	try{
		//express the move constructor in terms of move assignment
		 *this = std::move(o);
		_read_stream_pos = 0;
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error in move constructor for NXField!");
		EXCEPTION_THROW();
	}
}

template<typename Imp> NXField<Imp>::~NXField() {
	// TODO Auto-generated destructor stub
	close();
	_read_stream_pos = 0;
}

//------------------------------operators---------------------------------------
template<typename Imp> NXField<Imp> &NXField<Imp>::operator=(const NXField<Imp> &o){
	EXCEPTION_SETUP("template<typename Imp> NXField<Imp> &NXField<Imp>::operator=(const NXField<Imp> &o)");

	if( this != &o){
		try{
			(NXObject<Imp> &)(*this) = (NXObject<Imp> &)o;
			//this->setImplementation(o.getImplementation());
			_read_stream_pos = 0;
		}catch(...){
			EXCEPTION_INIT(NXFieldError,"Error in copy assignment of NXField!");
			EXCEPTION_THROW();
		}
	}
	return *this;
}

template<typename Imp> NXField<Imp> &NXField<Imp>::operator=(NXField<Imp> &&o){
	EXCEPTION_SETUP("template<typename Imp> NXField<Imp> &NXField<Imp>::operator=(NXField<Imp> &&o)");

	if(this != &o){
		try{
			//move assignment of the base class
			(NXObject<Imp> &)(*this) = std::move((NXObject<Imp> &)o);
			//this->setImplementation(std::move(o.getImplementation()));
			_read_stream_pos = 0;
		}catch(...){
			EXCEPTION_INIT(NXFieldError,"Error in move assignment of NXField!");
			EXCEPTION_THROW();
		}
	}

	return *this;
}

//--------------------------write operations------------------------------------
template<typename Imp> void NXField<Imp>::append(const ArrayObject &a){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::append(const ArrayObject &a)");

	if(!a.isAllocated()){
		EXCEPTION_INIT(NXFieldError,"Array not allocated - cannot append!");
		EXCEPTION_THROW();
	}

	if(a.getShape() != getElementShape()){
		EXCEPTION_INIT(ShapeMissmatchError,"Element shape and array shape do not match!");
		EXCEPTION_THROW();
	}

	try{
		this->getImplementation().append(a);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Cannot append data to field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}

template<typename Imp> void NXField<Imp>::append(const ScalarObject &s){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::append(const ScalarObject &s)");

	if(!this->getImplementation().isScalar()){
		EXCEPTION_INIT(NXFieldError,"Data field is not for scalar data!");
		EXCEPTION_THROW();
	}

	try{
		this->getImplementation().append(s);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Cannot append data to field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}

template<typename Imp> void NXField<Imp>::append(const String &s){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::append(const String &s)");
	if(!this->getImplementation().isString()){
		EXCEPTION_INIT(NXFieldError,"Data field is not a string field!");
		EXCEPTION_THROW();
	}

	try{
		this->getImplementation().append(s);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Cannot append string data to field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}

template<typename Imp> void NXField<Imp>::insert(const UInt64 &i,const ArrayObject &a){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::insert(const UInt64 &i,const ArrayObject &a)");

}

template<typename Imp> void NXField<Imp>::insert(const UInt64 &i,const ScalarObject &a){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::insert(const UInt64 &i,const ScalarObject &a)");

}

template<typename Imp> void NXField<Imp>::insert(const UInt64 &i,const String &s){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::insert(const UInt64 &i,const String &s)");

}

template<typename Imp> void NXField<Imp>::get(const UInt64 &i,ArrayObject &a){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::get(const UInt64 &i,ArrayObject &a)");

	if(!this->getImplementation().isArray()){
		EXCEPTION_INIT(NXFieldError,"Data field is not an array!");
		EXCEPTION_THROW();
	}

	try{
		this->getImplementation().get(i,a);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Cannot read array data from field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}

template<typename Imp> void NXField<Imp>::get(const UInt64 &i,ScalarObject &a){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::get(const UInt64 &i,ScalarObject &a)");
	if(!this->getImplementation().isScalar()){
		EXCEPTION_INIT(NXFieldError,"Data field is not scalar!");
		EXCEPTION_THROW();
	}

	try{
		this->getImplementation().get(i,a);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Cannot read scalar data from field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}

template<typename Imp> void NXField<Imp>::get(const UInt64 &i,String &s){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::get(const UInt64 &i,String &s)");

	if(!this->getImplementation().isString()){
		EXCEPTION_INIT(NXFieldError,"Data field is not a string array!");
		EXCEPTION_THROW();
	}

	try{
		this->getImplementation().get(i,s);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Cannot fetch string data from field ["+getName()+"]!");
		EXCEPTION_THROW();
	}

}


//----------------------stream operators---------------------------------------
template<typename Imp>
NXField<Imp> &operator<<(NXField<Imp> &o,const ScalarObject &s){
	o.append(s);
	return o;
}

template<typename Imp>
NXField<Imp> &operator<<(NXField<Imp> &o,const ArrayObject &a){
	o.append(a);
	return o;
}

template<typename Imp>
NXField<Imp> &operator<<(NXField<Imp> &o,const String &s){
	o.append(s);
	return o;
}

template<typename Imp>
NXField<Imp> &operator>>(NXField<Imp> &o,ScalarObject &s){
	o.get(o._read_stream_pos,s);
	o._read_stream_pos++;
	return o;
}

template<typename Imp>
NXField<Imp> &operator>>(NXField<Imp> &o,ArrayObject &a){
	o.get(o._read_stream_pos,a);
	o._read_stream_pos++;
	return o;
}

template<typename Imp>
NXField<Imp> &operator>>(NXField<Imp> &o,String &s){
	o.get(o._read_stream_pos,s);
	o._read_stream_pos++;
	return o;
}




//------------------convienance methods-----------------------------------------
template<typename Imp> void NXField<Imp>::close(){
	this->getImplementation().close();
}



//end of namespace
}
}

#endif /* NXFIELD_HPP_ */

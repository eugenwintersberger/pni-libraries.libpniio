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

#include <pni/utils/Types.hpp>
#include <pni/utils/ScalarObject.hpp>
#include <pni/utils/Scalar.hpp>
#include <pni/utils/Shape.hpp>
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
template<typename Imp> NXField<Imp> &operator<<(NXField<Imp> &o,const String &s);
template<typename Imp> NXField<Imp> &operator>>(NXField<Imp> &o,String &s);

//! \ingroup nexus_lowlevel
//! \brief NXfield base class

//! NXField is the basic data holding object in a Nexus file. You cannot create
//! an instance of this object directly rather you have to use one of the
//! factory methods provided by NXGroup.
//! NXField behaves like a container for data object which for the time being
//! can be either strings, Scalars, or Array objects.
template<typename Imp>
class NXField:public NXObject<Imp> {
private:
	UInt64 _read_stream_pos;
protected:
	void _increment_read_stream_pos(){
		_read_stream_pos++;
	}

	UInt64 _get_read_stream_pos(){
		return _read_stream_pos;
	}
public:
	typedef NXSelection<typename NXImpMap<Imp::IMPCODE>::SelectionImplementation > Selection;
	typedef boost::shared_ptr<NXField<Imp> > sptr;
	//! default constructor
	NXField();
	//! copy constructor
	NXField(const NXField<Imp> &);
	//! move constructor
	NXField(NXField<Imp> &&o);
	NXField(Imp &&o):NXObject<Imp>(std::move(o)){}
	//! copy conversion constructor
	NXField(const NXObject<typename NXObject<Imp>::ObjectImp > &o);
	//! move conversion constructor
	NXField(NXObject<typename NXObject<Imp>::ObjectImp > &&o);
	virtual ~NXField();

	//! copy assignment
	NXField<Imp> &operator=(const NXField<Imp> &);
	//! copy conversion assignment
	NXField<Imp> &operator=(const NXObject<typename NXObject<Imp>::ObjectImp > &o);

	//! move assignment
	NXField<Imp> &operator=(NXField<Imp> &&o);
	//! move conversion assignment
	NXField<Imp> &operator=(NXObject<typename NXObject<Imp>::ObjectImp > &&o);



	//! total field shape

	//! Return the total shape of the field. The rank if this
	//! shape is the rank of the object stored +1. The method returns
	//! a constant reference to the fields' shape. So you cannot alter
	//! this object.
	//! \return ArrayShape& reference to the shape object
	virtual const Shape &shape() const{
		return this->implementation().shape();
	}

	//! shape of a single element

	//! Return the shape of a single element stored in the container.
	virtual const Shape &element_shape() const {
		return this->implementation().element_shape();
	}

	//! get the type ID

	//! Return the ID of the data type stored in the field.
	//! \return data type ID
	virtual TypeID type_id() const {
		return this->implementation().type_id();
	}

	//! get the field name

	//! Return the name of the field.
	virtual String name() const {
		return this->implementation().name();
	}

	//! append a string obect to the field

	//! The onyl condition for this operation to succeed is that the
	//! field is of string type.
	void append(const String &s);

	//! set a string object
	void set(const UInt64 &i,const String &s);

	//! get a string object
	void get(const UInt64 &i,String &s);


	//! close the field
	void close();

	//! reset read stream position

	//! Reset the stream position for reading. This can be used
	//! to re-read data using stream IO.
	void resetreadstream() {
		_read_stream_pos = 0;
	}



	friend NXField<Imp> &operator<< <> (NXField<Imp> &o,const String &s);
	friend NXField<Imp> &operator>> <> (NXField<Imp> &o,String &s);

};

//========Implementation of constructors and destructors========================
//implementation of the default constructor
template<typename Imp> NXField<Imp>::NXField():NXObject<Imp>() {
	_read_stream_pos = 0;
}

//------------------------------------------------------------------------------
//implementation of the copy constructor
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

//------------------------------------------------------------------------------
//implementation of the move constructor
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

//------------------------------------------------------------------------------
//implementation of the copy conversion constructor
template<typename Imp>
NXField<Imp>::NXField(const NXObject<typename NXObject<Imp>::ObjectImp > &o):
NXObject<Imp>((NXObject<Imp> &)o){

}

//------------------------------------------------------------------------------
//implementation of the move conversion constructor
template<typename Imp>
NXField<Imp>::NXField(NXObject<typename NXObject<Imp>::ObjectImp > &&o)
:NXObject<Imp>(std::move((NXObject<Imp> &&)o)){

}

//------------------------------------------------------------------------------
//implementation of the destructor
template<typename Imp> NXField<Imp>::~NXField() {
	// TODO Auto-generated destructor stub
	close();
	_read_stream_pos = 0;
}

//==================Implementation of the assignment operators==================
//copy assignment operator
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

//------------------------------------------------------------------------------
//move assignment operator
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

//------------------------------------------------------------------------------
//copy conversion assignment operator
template<typename Imp>
NXField<Imp> &NXField<Imp>::operator=(const NXObject<typename NXObject<Imp>::ObjectImp > &o){

	(NXObject<Imp> &)(*this) = (NXObject<Imp> &)o;
	return *this;
}

//------------------------------------------------------------------------------
//move conversion assignment operator
template<typename Imp>
NXField<Imp> &NXField<Imp>::operator=(NXObject<typename NXObject<Imp>::ObjectImp > &&o){
	(NXObject<Imp> &)(*this) = std::move((NXObject<Imp> &&)o);
	return *this;
}

//------------------------------------------------------------------------------
template<typename Imp> void NXField<Imp>::append(const String &s){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::append(const String &s)");

	try{
		this->implementation().append(s);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Cannot append string data to field ["+this->name()+"]!");
		EXCEPTION_THROW();
	}
}



template<typename Imp> void NXField<Imp>::set(const UInt64 &i,const String &s){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::insert(const UInt64 &i,const String &s)");

}


template<typename Imp> void NXField<Imp>::get(const UInt64 &i,String &s){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::get(const UInt64 &i,String &s)");

	try{
		this->implementation().get(i,s);
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Cannot fetch string data from field ["+this->name()+"]!");
		EXCEPTION_THROW();
	}

}


//----------------------stream operators---------------------------------------

template<typename Imp>
NXField<Imp> &operator<<(NXField<Imp> &o,const String &s){
	o.append(s);
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
	this->implementation().close();
}



//end of namespace
}
}

#endif /* NXFIELD_HPP_ */

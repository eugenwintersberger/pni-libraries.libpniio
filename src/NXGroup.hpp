/*
 * Declaration of the NXGroup template
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
 * Declaration of the NXGroup template
 *
 * Created on: Jul 1, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXGROUP_HPP_
#define NXGROUP_HPP_

#include <boost/shared_ptr.hpp>
#include <pni/utils/Types.hpp>
#include <pni/utils/Shape.hpp>

#include "NXObject.hpp"
#include "NXImpMap.hpp"
#include "NXField.hpp"
#include "NXNumericField.hpp"
#include "NXStringField.hpp"
#include "NXBinaryField.hpp"
#include "NXFilter.hpp"
#include "NXExceptions.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{

template<typename Imp>
class NXGroup:public NXObject<Imp> {
protected:
public:
	typedef boost::shared_ptr<NXGroup<Imp> > sptr;
	//! default constructor
	NXGroup();
	//! copy constructor

	//! The copy constructor is doing exactly the
	//! same as the assignment operator. Thus it can be used to assign
	//! an object directly at its construction.
	NXGroup(const NXGroup<Imp> &);

	//! copy conversion constructor
	NXGroup(const NXObject<typename NXObject<Imp>::ObjectImp > &o);
	//! move conversion constructor
	NXGroup(NXObject<typename NXObject<Imp>::ObjectImp > &&o);
	//! move constructor
	NXGroup(NXGroup<Imp> &&o);
	NXGroup(Imp &&i):NXObject<Imp>(std::move(i)){}
	//! destructor
	virtual ~NXGroup();

	//! copy assignment operator
	NXGroup<Imp> &operator=(const NXGroup<Imp> &);
	//! copy assignment conversion operator
	NXGroup<Imp> &operator=(const NXObject<typename NXObject<Imp>::ObjectImp > &o);
	//! move assignment operator
	NXGroup<Imp> &operator=(NXGroup<Imp> &&o);
	//! move assignment conversion operator
	NXGroup<Imp> &operator=(NXObject<typename NXObject<Imp>::ObjectImp > &&o);

	virtual NXGroup<typename NXObject<Imp>::GroupImp> createGroup(const String &n) const;
	virtual NXGroup<typename NXObject<Imp>::GroupImp> createGroup(const String &n,const String &type) const;

	//! create a field for array data using an ArrayShape

	//! Here a reference to an ArrayShape object is used to create a data field
	//! \param n name of the field as String object
	//! \param tid PNI type code of the data type
	//! \param s reference to an ArrayShape object
	NXNumericField<typename NXObject<Imp>::NumericFieldImp>
	createNumericField(const String &n, TypeID tid,const Shape &s,
					   const String &unit,const String &desc) const;
	template<typename Filter>
	NXNumericField<typename NXObject<Imp>::NumericFieldImp >
	createNumericField(const String &n, TypeID tid,const Shape &s,
					   const String &unit,const String &desc,
				       NXFilter<Filter> &f) const;

	//! create a field for array data from an ArrayObject

	//! This method uses a reference to an ArrayObject instance. All parameters
	//! relevant to the
	//! field are derived from the ArrayObject object.
	//! \param n name of the field
	//! \param a reference to the ArrayObject instance
	NXNumericField<typename NXObject<Imp>::NumericFieldImp>
	createNumericField(const ArrayObject &a) const;
	template<typename Filter>
	NXNumericField<typename NXObject<Imp>::NumericFieldImp>
	createNumericField(const ArrayObject &a,NXFilter<Filter> &f) const;


	//! create a field for scalar data - simplest approach

	//! A data field for a single scalar datum will be created.
	//! \param n name of the data field
	//! \param tid ID of the PNI type for the field
	NXNumericField<typename NXObject<Imp>::NumericFieldImp>
	createNumericField(const String &n,TypeID tid,const String &unit,
					   const String &desc) const;
	//! create a field for scalar data from ScalarObject

	//! A reference to an instance of ScalarObject is used to derive all
	//! parameters for data field creation.
	//! \param n name of the data field
	//! \parma s reference to the ScalarObject instance
	NXNumericField<typename NXObject<Imp>::NumericFieldImp>
	createNumericField(const ScalarObject &s) const;

	//! create a field for string data

	//! Create a field for String data encoded in UTF8.
	//! \param n name of the field
	//! \param s string for which the field should be created
	NXStringField<typename NXObject<Imp>::StringFieldImp> createStringField(const String &n) const;

	//! create a binary field
	NXBinaryField<typename NXObject<Imp>::BinaryFieldImp > createBinaryField(const String &n) const;

	//! open an arbitrary object
	virtual NXObject<typename NXObject<Imp>::ObjectImp> open(const String &n);


	//! close the group object
	virtual void close();

	virtual bool exists(const String &n) const{
		return this->getImplementation().exists(n);
	}

	virtual void remove(const String &n) const{
		this->getImplementation().remove(n);
	}


};

//========================constructors and destructors==========================
//implementation of default constructor
template<typename Imp>
NXGroup<Imp>::NXGroup():NXObject<Imp>(){
}

//------------------------------------------------------------------------------
//implementation of copy constructor
template<typename Imp> NXGroup<Imp>::NXGroup(const NXGroup &g)
		:NXObject<Imp>(g){
	EXCEPTION_SETUP("template<typename Imp> NXGroup<Imp>::NXGroup(const NXGroup &g)");
}

//------------------------------------------------------------------------------
//implementation of move constructor
template<typename Imp> NXGroup<Imp>::NXGroup(NXGroup<Imp> &&g){
	EXCEPTION_SETUP("template<typename Imp> NXGroup<Imp>::NXGroup(NXGroup<Imp> &&g)");

	*this = std::move(g);
}

//------------------------------------------------------------------------------
//implementation of copy conversion constructor
template<typename Imp>
NXGroup<Imp>::NXGroup(const NXObject<typename NXObject<Imp>::ObjectImp > &o)
:NXObject<Imp>((NXObject<Imp> &)o){
}

//------------------------------------------------------------------------------
//implementationof move conversion constructor
template<typename Imp>
NXGroup<Imp>::NXGroup(NXObject<typename NXObject<Imp>::ObjectImp > &&o):
NXObject<Imp>(std::move((NXObject<Imp> &&)o)){

}

//------------------------------------------------------------------------------
template<typename Imp> NXGroup<Imp>::~NXGroup(){
	close();
}

//======================================variants of the assignment operator====
//implementation of the copy assignment operator
template<typename Imp> NXGroup<Imp> &NXGroup<Imp>::operator=(const NXGroup<Imp> &g){
	EXCEPTION_SETUP("template<typename Imp> NXGroup<Imp> &NXGroup<Imp>::operator=(const NXGroup<Imp> &g)");
	if( this != &g){
		(NXObject<Imp> &)(*this) = (NXObject<Imp> &)g;
	}

	return *this;
}

//------------------------------------------------------------------------------
//implementation of the copy conversion assignment operator
template<typename Imp>
NXGroup<Imp> &NXGroup<Imp>::operator=(const NXObject<typename NXObject<Imp>::ObjectImp > &o){
	if(this != &o){
		(NXObject<Imp> &)(*this) = (NXObject<Imp> &)o;
	}
	return *this;
}

//------------------------------------------------------------------------------
//implementation of the move assignment operator
template<typename Imp> NXGroup<Imp> &NXGroup<Imp>::operator=(NXGroup<Imp> &&o){
	EXCEPTION_SETUP("template<typename Imp> NXGroup<Imp> &NXGroup<Imp>::operator=(NXGroup<Imp> &&o)");

	if(this != &o){
		(NXObject<Imp> &)(*this) = std::move((NXObject<Imp> &)o);
	}

	return *this;
}

//------------------------------------------------------------------------------
//implementation of the move assignment conversion operator
//implementation of the copy conversion assignment operator
template<typename Imp>
NXGroup<Imp> &NXGroup<Imp>::operator=(NXObject<typename NXObject<Imp>::ObjectImp > &&o){

	(NXObject<Imp> &)(*this) = std::move((NXObject<Imp> &&)o);

	return *this;
}



//==============methods for creating and opening groups========================
template<typename Imp>
NXGroup<typename NXObject<Imp>::GroupImp> NXGroup<Imp>::createGroup(const String &n) const{
	EXCEPTION_SETUP("template<typename Imp> NXGroup<typename NXGroup<Imp>::GImp> NXGroup<Imp>::createGroup(const String &n) const");

	NXGroup<typename NXObject<Imp>::GroupImp> group;

	try{
		group = NXGroup<typename NXObject<Imp>::GroupImp >(this->getImplementation().createGroup(n));
	}catch(...){
		EXCEPTION_INIT(NXGroupError,"Error creating group ["+n+"] below group ["+this->getName()+"]!");
		EXCEPTION_THROW();
	}
	return group;
}

//------------------------------------------------------------------------------
template<typename Imp>
NXGroup<typename NXObject<Imp>::GroupImp > NXGroup<Imp>::createGroup(const String &n,const String &type) const{
	EXCEPTION_SETUP("template<typename Imp> NXGroup<typename NXGroup<Imp>::GImp > NXGroup<Imp>::createGroup(const String &n) const");

	NXGroup<typename NXObject<Imp>::GroupImp > group;

	//before creating the group we should first lookup if the group
	//really exists - this has to be implemented!!!!

	//create the group
	try{
		group = NXGroup<typename NXObject<Imp>::GroupImp>(this->getImplementation().createGroup(n));
	}catch(...){
		EXCEPTION_INIT(NXGroupError,"Error creating group ["+n+"] below group ["+this->getName()+"]!");
		EXCEPTION_THROW();
	}

	//here we have to set the group type
	group.setAttribute("NX_class",type);

	return group;
}

//================Methods for opening and creating fields======================

template<typename Imp>
NXNumericField<typename NXObject<Imp>::NumericFieldImp >
NXGroup<Imp>::createNumericField(const String &n,TypeID tid,const Shape &s,
		                  const String &unit,const String &desc) const{
	EXCEPTION_SETUP("template<typename Imp> NXField<typename NXGroup<Imp>::FImp >"
					"NXGroup<Imp>::createNumericField(const String &n,"
					"PNITypeID tid,const ArrayShape &s,const String &unit,"
					"const String &desc) const");
	typedef NXNumericField<typename NXObject<Imp>::NumericFieldImp > FieldType;

	FieldType field;
	try{
		field = FieldType(this->getImplementation().createNumericField(n,tid,s));
		field.setAttribute("units",unit);
		field.setAttribute("long_name",desc);
	}catch(...){
		EXCEPTION_INIT(NXGroupError,"Error creating array field ["+n+"] below group ["+this->getName()+"]!");
		EXCEPTION_THROW();
	}

	return field;
}

//------------------------------------------------------------------------------
template<typename Imp>
template<typename Filter>
NXNumericField<typename NXObject<Imp>::NumericFieldImp >
NXGroup<Imp>::createNumericField(const String &n,TypeID tid,
		                  const Shape &s,const String &unit,const String &desc,
		                  NXFilter<Filter> &f) const{
	EXCEPTION_SETUP("template<typename Imp> template<typename Filter>"
				    " NXField<typename NXGroup<Imp>::FImp > "
					"NXGroup<Imp>::createNumericField(const String &n,"
					"PNITypeID tid,const ArrayShape &s,const String &unit,"
					"const String &desc,NXFilter<Filter> &f) const");
	typedef NXNumericField<typename NXObject<Imp>::NumericFieldImp > FieldType;
	FieldType field;

	try{
		field.setImplementation(std::move(this->_imp.createNumericField(n.c_str(),tid,s,f)));
		field.setAttribute("units",unit);
		field.setAttribute("long_name",desc);
	}catch(...){
		EXCEPTION_INIT(NXGroupError,"Error creating array field ["+n+"] below group ["+this->getName()+"]!");
		EXCEPTION_THROW();
	}

	return field;
}

//------------------------------------------------------------------------------
template<typename Imp>
NXNumericField<typename NXObject<Imp>::NumericFieldImp >
NXGroup<Imp>::createNumericField(const ArrayObject &a) const{
	EXCEPTION_SETUP("template<typename Imp> NXField<typename NXGroup<Imp>::FImp >"
					" NXGroup<Imp>::createNumericField(const ArrayObject &a) const");

	NXNumericField<typename NXObject<Imp>::NumericFieldImp > field;
	try{
		field = createNumericField(a.name(),a.type_id(),a.shape(),a.unit(),a.description());
	}catch(...){
		EXCEPTION_INIT(NXGroupError,"Error creating array object ["+a.name()+"] below group ["+this->getName()+"]!");
		EXCEPTION_THROW();
	}

	return field;
}

//------------------------------------------------------------------------------
template<typename Imp>
template<typename Filter>
NXNumericField<typename NXObject<Imp>::NumericFieldImp >
NXGroup<Imp>::createNumericField(const ArrayObject &a,NXFilter<Filter> &f) const{
	EXCEPTION_SETUP("template<typename Imp> template<typename Filter>"
					" NXField<typename NXGroup<Imp>::FImp > "
					"NXGroup<Imp>::createNumericField(const ArrayObject &a,"
					"NXFilter<Filter> &f) const");

	NXNumericField<typename NXObject<Imp>::NumericFieldImp > field;
	try{
		field = createNumericField(a.name(),a.type_id(),a.shape(),a.unit(),a.description(),f);
	}catch(...){
		EXCEPTION_INIT(NXGroupError,"Error creating array field ["+a.name()+"] below group ["+this->getName()+"]!");
		EXCEPTION_THROW();
	}

	return field;
}

//------------------------------------------------------------------------------
template<typename Imp> NXNumericField<typename NXObject<Imp>::NumericFieldImp >
NXGroup<Imp>::createNumericField(const String &n,TypeID tid,const String &unit,const String &desc) const{
	EXCEPTION_SETUP("template<typename Imp> NXField<typename NXGroup<Imp>::FImp > "
					"NXGroup<Imp>::createNumericField(const String &n,"
					"PNITypeID tid,const String &unit,const String &desc) const");
	typedef NXNumericField<typename NXObject<Imp>::NumericFieldImp > FieldType;
	FieldType field;

	try{
		field = FieldType(std::move(this->getImplementation().createNumericField(n,tid)));
		field.setAttribute("units",unit);
		field.setAttribute("long_name",desc);
	}catch(...){
		EXCEPTION_INIT(NXGroupError,"Cannot create scalar field ["+n+"] below group ["+this->getName()+"]!");
		EXCEPTION_THROW();
	}

	return field;
}

//------------------------------------------------------------------------------
template<typename Imp>
NXNumericField<typename NXObject<Imp>::NumericFieldImp > NXGroup<Imp>::createNumericField(const ScalarObject &s) const{
	EXCEPTION_SETUP("template<typename Imp> NXField<typename NXGroup<Imp>::FImp > "
					"NXGroup<Imp>::createNumericField(const ScalarObject &s) const");
	NXNumericField<typename NXObject<Imp>::NumericFieldImp > field;

	try{
		field =createNumericField(s.name(),s.type_id(),s.unit(),s.description());
	}catch(...){
		EXCEPTION_INIT(NXGroupError,"Cannot create scalar field ["+s.name()+"] below group ["+this->getName()+"]!");
		EXCEPTION_THROW();
	}
	return field;
}

//------------------------------------------------------------------------------
template<typename Imp>
NXStringField<typename NXObject<Imp>::StringFieldImp > NXGroup<Imp>::createStringField(const String &n) const{
	EXCEPTION_SETUP("template<typename Imp> NXField<typename NXGroup<Imp>::FImp > NXGroup<Imp>::createStringField(const String &n,const String &s) const");

	typedef NXStringField<typename NXObject<Imp>::StringFieldImp > FieldType;
	FieldType field;

	try{
		field = FieldType(std::move(this->getImplementation().createStringField(n)));
	}catch(...){
		EXCEPTION_INIT(NXGroupError,"Error creating string field ["+n+"] below group ["+this->getName()+"]!");
		EXCEPTION_THROW();
	}

	return field;
}

//------------------------------------------------------------------------------
//implementation of create a binary field
template<typename Imp>
NXBinaryField<typename NXObject<Imp>::BinaryFieldImp >
NXGroup<Imp>::createBinaryField(const String &n) const{
	EXCEPTION_SETUP("template<typename Imp> "
					"NXBinaryField<typename NXObject<Imp>::BinaryFieldImp > "
					"NXGroup<Imp>::createBinaryField(const String &n) const");

	typedef NXBinaryField<typename NXObject<Imp>::BinaryFieldImp > FieldType;
	FieldType field;

	try{
		field = FieldType(std::move(this->getImplementation().createBinaryField(n)));
	}catch(...){
		EXCEPTION_INIT(NXGroupError,"Error creating binary field ["+n+"] below gruop ["+this->getName()+"]!");
		EXCEPTION_THROW();
	}

	return field;
}

//------------------------------------------------------------------------------
template<typename Imp>
void NXGroup<Imp>::close(){
	this->getImplementation().close();
}

//------------------------------------------------------------------------------
template<typename Imp>
NXObject<typename NXObject<Imp>::ObjectImp> NXGroup<Imp>::open(const String &n){
	EXCEPTION_SETUP("template<typename Imp> NXObject<typename NXObject<Imp>::ObjectImp> NXGroup<Imp>::open(const String &n)");
	typedef NXObject<typename NXObject<Imp>::ObjectImp > ObjectType;
	ObjectType o;

	try{
		o = ObjectType(std::move(this->getImplementation().open(n)));
	}catch(...){
		EXCEPTION_INIT(NXGroupError,"Cannot open object!");
		EXCEPTION_THROW();
	}
	return o;
}

//end of namespace
}
}


#endif /* NXGROUP_HPP_ */

/*
 * NXGroup.hpp
 *
 *  Created on: Jul 1, 2011
 *      Author: eugen
 */

#ifndef NXGROUP_HPP_
#define NXGROUP_HPP_

#include <boost/shared_ptr.hpp>
#include <pni/utils/PNITypes.hpp>
#include <pni/utils/ArrayShape.hpp>

#include "NXObject.hpp"
#include "NXImpMap.hpp"
#include "NXField.hpp"
#include "NXFilter.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{

template<typename Imp>
class NXGroup:public NXObject<Imp> {
protected:
public:
	typedef typename NXImpMap<Imp::IMPCODE>::ObjectImplementation OImp;
	typedef typename NXImpMap<Imp::IMPCODE>::GroupImplementation GImp;
	typedef typename NXImpMap<Imp::IMPCODE>::FieldImplementation FImp;
	typedef boost::shared_ptr<NXGroup<Imp> > sptr;
	//! default constructor
	NXGroup();
	//! copy constructor

	//! The copy constructor is doing exactly the
	//! same as the assignment operator. Thus it can be used to assign
	//! an object directly at its construction.
	NXGroup(const NXGroup &);
	//! destructor
	virtual ~NXGroup();

	//! assignment operator
	NXGroup &operator=(const NXGroup &);

	virtual NXGroup<GImp> createGroup(const String &n);
	virtual NXGroup<GImp> openGroup(const String &n);

	//! create a field for array data using an ArrayShape

	//! Here a reference to an ArrayShape object is used to create a data field
	//! \param n name of the field as String object
	//! \param tid PNI type code of the data type
	//! \param s reference to an ArrayShape object
	NXField<FImp> createField(const String &n, PNITypeID tid,
			                           const ArrayShape &s);
	template<typename Filter>
	NXField<FImp> createField(const String &n, PNITypeID tid,
				                       const ArrayShape &s,
				                       NXFilter<Filter> &f);

	//! create a field for array data from an ArrayObject

	//! This method uses a reference to an ArrayObject instance. All parameters
	//! relevant to the
	//! field are derived from the ArrayObject object.
	//! \param n name of the field
	//! \param a reference to the ArrayObject instance
	NXField<FImp> createField(const String &n,ArrayObject &a);
	template<typename Filter>
	NXField<FImp> createField(const String &n,ArrayObject &a,
											 NXFilter<Filter> &f);
	//! create a field for array data from an ArrayObject

	//! Create a data field using a shared pointer to an ArrayObject instance.
	//! All parameters relevant to the field are derived from the original
	//! ArrayObject object.
	//! \param n name of the field
	//! \param a shared pointer to the ArrayObject object
	NXField<FImp> createField(const String &n,ArrayObject::sptr a);
	template<typename Filter>
	NXField<FImp> createField(const String &n,ArrayObject::sptr a,
			  	  	  	  	  	  	  	  	 NXFilter<Filter> &f);


	//! create a field for scalar data - simplest approach

	//! A data field for a single scalar datum will be created.
	//! \param n name of the data field
	//! \param tid ID of the PNI type for the field
	NXField<FImp> createField(const String &n,PNITypeID tid);
	//! create a field for scalar data from ScalarObject

	//! A reference to an instance of ScalarObject is used to derive all
	//! parameters for data field creation.
	//! \param n name of the data field
	//! \parma s reference to the ScalarObject instance
	NXField<FImp> createField(const String &n,ScalarObject &s);
	//! create a field for scalar data from ScalarObject

	//! A shared pointer to an instance of ScalarObject is used to derive all
	//! parameters for data field creation.
	//! \param n name of the data field
	//! \param s shared pointer ot the instance of ScalarObject
	NXField<FImp> createField(const String &n,ScalarObject::sptr s);

	//! create a field for string data

	//! Create a field for String data encoded in UTF8.
	//! \param n name of the field
	//! \param s string for which the field should be created
	NXField<FImp> createField(const String &n,const String &s);

	//! open a field object
	NXField<FImp> openField(const String &n);
	//! open an arbitrary object
	NXObject<OImp> open(const String &n);


	//! close the group object
	virtual void close();

	virtual bool exists(const String &n) const{
		return this->_imp.exists(n);
	}


};

//========================constructors and destructors==========================
template<typename Imp>
NXGroup<Imp>::NXGroup(){
}

template<typename Imp> NXGroup<Imp>::NXGroup(const NXGroup &g){
	this->_imp = g._imp;
}

template<typename Imp> NXGroup<Imp>::~NXGroup(){
	close();
}

//======================================variants of the assignment operator====

template<typename Imp>
NXGroup<Imp> &NXGroup<Imp>::operator=(const NXGroup<Imp> &g){
	if( this != &g){
		this->_imp = g._imp;
	}

	return *this;
}

//==============methods for creating and opening groups========================
template<typename Imp>
NXGroup<typename NXGroup<Imp>::GImp> NXGroup<Imp>::createGroup(const String &n) {

	NXGroup<GImp> group;

	//create a new implementation object
	this->_imp.createGroup(n.c_str(), group.getImplementation());

	return group;
}

template<typename Imp>
NXGroup<typename NXGroup<Imp>::GImp > NXGroup<Imp>::openGroup(const String &n){

	NXGroup<GImp> group ;

	//open a group
	this->_imp.openGroup(n.c_str(),group.getImplementation());

	return group;
}


//================Methods for opening and creating fields======================

template<typename Imp>
NXField<typename NXGroup<Imp>::FImp >
NXGroup<Imp>::createField(const String &n,PNITypeID tid,const ArrayShape &s){
	NXField<FImp> field;
	this->_imp.createField(n.c_str(),tid,s,field.getImplementation());

	return field;
}

template<typename Imp>
template<typename Filter>
NXField<typename NXGroup<Imp>::FImp >
NXGroup<Imp>::createField(const String &n,PNITypeID tid,
		                  const ArrayShape &s,NXFilter<Filter> &f){
	NXField<FImp> field;

	this->_imp.createField(n.c_str(),tid,s,field.getImplementation(),f);

	return field;
}

template<typename Imp>
NXField<typename NXGroup<Imp>::FImp >
NXGroup<Imp>::createField(const String &n,ArrayObject &a){

	return createField(n,a.getTypeID(),a.getShape());
}

template<typename Imp>
template<typename Filter>
NXField<typename NXGroup<Imp>::FImp >
NXGroup<Imp>::createField(const String &n,ArrayObject &a,NXFilter<Filter> &f){

	return createField(n,a.getTypeID(),a.getShape(),f);
}

template<typename Imp>
NXField<typename NXGroup<Imp>::FImp >
NXGroup<Imp>::createField(const String &n,ArrayObject::sptr a){

	return createField(n,a->getTypeID(),a->getShape());
}

template<typename Imp>
template<typename Filter>
NXField<typename NXGroup<Imp>::FImp >
NXGroup<Imp>::createField(const String &n,ArrayObject::sptr a,NXFilter<Filter> &f){

	return createField(n,a->getTypeID(),a->getShape(),f);
}


template<typename Imp>
NXField<typename NXGroup<Imp>::FImp > NXGroup<Imp>::openField(const String &n){
	NXField<FImp> field;

	this->_imp.openField(n.c_str(),field.getImplementation());

	return field;
}

template<typename Imp>
NXField<typename NXGroup<Imp>::FImp > NXGroup<Imp>::createField(const String &n,PNITypeID tid){
	NXField<FImp> field;

	this->_imp.createField(n.c_str(),tid,field.getImplementation());

	return field;
}

template<typename Imp>
NXField<typename NXGroup<Imp>::FImp > NXGroup<Imp>::createField(const String &n,ScalarObject &s){
	return createField(n.c_str(),s.getTypeID());
}

template<typename Imp>
NXField<typename NXGroup<Imp>::FImp >
NXGroup<Imp>::createField(const String &n,ScalarObject::sptr s){

	return createField(n.c_str(),s->getTypeID());
}


template<typename Imp>
NXField<typename NXGroup<Imp>::FImp > NXGroup<Imp>::createField(const String &n,const String &s){

	NXField<FImp> field;

	this->_imp.createField(n.c_str(),s.size(),field.getImplementation());

	return field;
}

template<typename Imp>
void NXGroup<Imp>::close(){
	this->_imp.close();
}

//end of namespace
}
}


#endif /* NXGROUP_HPP_ */

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
//#include "NXFilter.hpp"

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

	virtual typename NXGroup<GImp>::sptr createGroup(const String &n);
	virtual typename NXGroup<GImp>::sptr openGroup(const String &n);

	//! create a field for array data - most basic approach

	//! This is the most basic approach to define field.
	//! \param n name of the field
	//! \param tid PNI type code of the data type
	//! \param rank number of dimensions of the field
	//! \param dims number of points along each dimension
	typename NXField<FImp>::sptr createField(const String &n, PNITypeID tid,
				                             UInt32 rank, const UInt32 dims[]);
	//! create a field for array data using an ArrayShape

	//! Here a reference to an ArrayShape object is used to create a data field
	//! \param n name of the field as String object
	//! \param tid PNI type code of the data type
	//! \param s reference to an ArrayShape object
	typename NXField<FImp>::sptr createField(const String &n, PNITypeID tid,
			                                 const ArrayShape &s);
	//! create a field for array data with ArrayShape

	//! Create a data field using a shared pointer to an ArrayShape object
	//! (this is
	//! what is returned by ArrayObject::getShape() method.
	//! \param n name of the field as String object
	//! \param tid PNI type code of the data type
	//! \param s shared pointer ot a ArrayShape object
	typename NXField<FImp>::sptr createField(const String &n, PNITypeID tid,
			                        	     const ArrayShape::sptr s);

	//! create a field for array data from an ArrayObject

	//! This method uses a reference to an ArrayObject instance. All parameters
	//! relevant to the
	//! field are derived from the ArrayObject object.
	//! \param n name of the field
	//! \param a reference to the ArrayObject instance
	typename NXField<FImp>::sptr createField(const String &n,ArrayObject &a);
	//! create a field for array data from an ArrayObject

	//! Create a data field using a shared pointer to an ArrayObject instance.
	//! All parameters relevant to the field are derived from the original
	//! ArrayObject object.
	//! \param n name of the field
	//! \param a shared pointer to the ArrayObject object
	typename NXField<FImp>::sptr createField(const String &n,ArrayObject::sptr a);


	//! create a field for scalar data - simplest approach

	//! A data field for a single scalar datum will be created.
	//! \param n name of the data field
	//! \param tid ID of the PNI type for the field
	typename NXField<FImp>::sptr createField(const String &n,PNITypeID tid);
	//! create a field for scalar data from ScalarObject

	//! A reference to an instance of ScalarObject is used to derive all
	//! parameters for data field creation.
	//! \param n name of the data field
	//! \parma s reference to the ScalarObject instance
	typename NXField<FImp>::sptr createField(const String &n,ScalarObject &s);
	//! create a field for scalar data from ScalarObject

	//! A shared pointer to an instance of ScalarObject is used to derive all
	//! parameters for data field creation.
	//! \param n name of the data field
	//! \param s shared pointer ot the instance of ScalarObject
	typename NXField<FImp>::sptr createField(const String &n,ScalarObject::sptr s);

	//! create a field for string data

	//! Create a field for String data encoded in UTF8.
	//! \param n name of the field
	//! \param s string for which the field should be created
	typename NXField<FImp>::sptr createField(const String &n,const String &s);

	//! open a field object
	typename NXField<FImp>::sptr openField(const String &n);
	//! open an arbitrary object
	typename NXObject<OImp>::sptr open(const String &n);

	//! create a link below this node

	//! Create a symbolic link below this node. The first argument of the
	//! method describes the target. Two target forms are allowed:
	//! t="/path/to/target" in which case a link to an internal object
	//! object is created and t="file:/path/to/target" in which case
	//! an external link (link to an object in another file) is created.
	//! \param t target path
	//! \param n name of the link
	virtual void createLink(const String &t,const String &n){}

	//! close the group object
	virtual void close();


};

//================================constructors and destructors=================
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
typename NXGroup<typename NXGroup<Imp>::GImp>::sptr
NXGroup<Imp>::createGroup(const String &n) {

	typename NXGroup<GImp>::sptr ptr;
	ptr = typename NXGroup<GImp>::sptr(new NXGroup<GImp> ());

	//create a new implementation object
	this->_imp.createGroup(n.c_str(), ptr->getImplementation());

	return ptr;
}

template<typename Imp>
typename NXGroup<typename NXGroup<Imp>::GImp >::sptr
NXGroup<Imp>::openGroup(const String &n){

	typename NXGroup<GImp>::sptr ptr ;
	ptr = typename NXGroup<GImp>::sptr(new NXGroup<GImp>());

	//open a group
	this->_imp.openGroup(n.c_str(),ptr->getImplementation());

	return ptr;
}


//================Methods for opening and creating fields======================
template<typename Imp>
typename NXField<typename NXGroup<Imp>::FImp >::sptr
NXGroup<Imp>::createField(const String &n,PNITypeID tid,UInt32 rank,
				          const UInt32 dims[]){

	typename NXField<FImp>::sptr ptr;
	ptr = typename NXField<FImp>::sptr(new NXField<FImp>());

	this->_imp.createField(n.c_str(),tid,rank,dims,ptr->getImplementation());
	return ptr;
}


template<typename Imp>
typename NXField<typename NXGroup<Imp>::FImp >::sptr
NXGroup<Imp>::createField(const String &n,PNITypeID tid,const ArrayShape::sptr s){

	return createField(n,tid,s->getRank(),s->getDimensions());
}

template<typename Imp>
typename NXField<typename NXGroup<Imp>::FImp >::sptr
NXGroup<Imp>::createField(const String &n,PNITypeID tid,
		                  const ArrayShape &s){

	return createField(n,tid,s.getRank(),s.getDimensions());
}

template<typename Imp>
typename NXField<typename NXGroup<Imp>::FImp >::sptr
NXGroup<Imp>::createField(const String &n,ArrayObject &a){

	return createField(n,a.getTypeID(),a.getShape());
}

template<typename Imp>
typename NXField<typename NXGroup<Imp>::FImp >::sptr
NXGroup<Imp>::createField(const String &n,ArrayObject::sptr a){

	return createField(n,a->getTypeID(),a->getShape());
}


template<typename Imp>
typename NXField<typename NXGroup<Imp>::FImp >::sptr
NXGroup<Imp>::openField(const String &n){
	typename NXField<FImp>::sptr ptr;
	ptr = typename NXField<FImp>::sptr(new NXField<FImp>());

	this->_imp.openField(n.c_str(),ptr->getImplementation());

	return ptr;
}

template<typename Imp>
typename NXField<typename NXGroup<Imp>::FImp >::sptr
NXGroup<Imp>::createField(const String &n,PNITypeID tid){
	typename NXField<FImp>::sptr ptr;
	ptr = typename NXField<FImp>::sptr(new NXField<FImp>());
	this->_imp.createField(n.c_str(),tid,ptr->getImplementation());

	return ptr;
}

template<typename Imp>
typename NXField<typename NXGroup<Imp>::FImp >::sptr
NXGroup<Imp>::createField(const String &n,ScalarObject &s){
	return createField(n.c_str(),s.getTypeID());
}

template<typename Imp>
typename NXField<typename NXGroup<Imp>::FImp >::sptr
NXGroup<Imp>::createField(const String &n,ScalarObject::sptr s){

	return createField(n.c_str(),s->getTypeID());
}


template<typename Imp>
typename NXField<typename NXGroup<Imp>::FImp >::sptr
NXGroup<Imp>::createField(const String &n,const String &s){

	typename NXField<FImp>::sptr ptr;
	ptr = typename NXField<FImp>::sptr(new NXField<FImp>());

	this->_imp.createStringField(n.c_str(),s.size(),ptr->getImplementation());

	return ptr;
}

template<typename Imp>
void NXGroup<Imp>::close(){
	this->_imp.close();
}

//end of namespace
}
}


#endif /* NXGROUP_HPP_ */

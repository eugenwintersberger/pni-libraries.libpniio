/*
 * NXObject.hpp
 *
 *  Created on: Jul 1, 2011
 *      Author: eugen
 */

#ifndef NXOBJECT_HPP_
#define NXOBJECT_HPP_

#include <iostream>

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/ArrayObject.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/ScalarObject.hpp>
#include <pni/utils/Scalar.hpp>

namespace pni{
namespace nx{

using namespace pni::utils;

//! \ingroup Nexus objects
//! \brief base class for all Nexus objects in the library.

//! This class provides functionality common to all Nexus objects.
//! This includes methods for obtaining the name and path of an object
//! in the Nexus tree, methods to set and get attributes, creation of
//! links to an object. Methods for creating links to this objects are
//! also included.
template<typename Imp>
class NXObject {
protected:
	Imp _imp;	//!< implementation object
public:
	typedef boost::shared_ptr<NXObject<Imp> > sptr;
	//! default constructor
	NXObject();
	//! copy constructor
	NXObject(const NXObject &o);
	//! destructor
	virtual ~NXObject();

	//! assignment operator
	NXObject<Imp> &operator=(const NXObject &o);

	//! get implementation reference

	//! Returns a reference to the actual implementation of an object.
	//! \return reference to implementation
	Imp &getImplementation();

	//! set implementation object

	//! Set the implementation of an object
	//! \param i reference to an implementation
	void setImplementation(const Imp &i);

	//! retrieve objects path

	//! This method returns the absolute path to this object.
	//! \return objects absolute path
	virtual String getPath() const;

	//! retrieve objects base path

	//! Returns the base part of the absolute path of an object. For example
	//! if the path to an object is /scan_1/detector/data this method
	//! will return /scan_1/detector.
	//! \return base part of the absolute path
	virtual String getBase() const;

	//! retrieve an objects name

	//! Return the name of an object. This the top part of the absolute path.
	//! If the path would be /scan_1/detector/data this method would
	//! return data.
	//! \return name of the object
	virtual String getName() const;

	//! write Array attribute

	//! Write an array attribute.
	//! \param n name of the attribute
	//! \param a reference to the array object
	virtual void setAttribute(const String &n,ArrayObject &a);
	//! write scalar attribute

	//! Write a Scalar object as an attribute to a Nexus object.
	//! \param n name of the attribute
	//! \param s reference to the scalar object
	virtual void setAttribute(const String &n,ScalarObject &s);
	//! write string attribute

	//! Write a string attribute
	//! \param n name of the attribute
	//! \param s String to write as attribute
	virtual void setAttribute(const String &n,const String &s);

	//! read Array attribute

	//! Read an array attribute from an object and store its content
	//! in an array object.
	//! \param n name of the attribute
	//! \param a reference to the array object
	virtual void getAttribute(const String &n,ArrayObject &a);
	//! read scalar attribute

	//! Read a scalar attribute from an object an store its content in a
	//! scalar attribute.
	//! \param n name of the attribute
	//! \param s reference to the scalar object
	virtual void getAttribute(const String &n,ScalarObject &s);
	//! read string attribute

	//! Read a string attribute from an object and store it to a string object.
	//! \param n name of the attribute
	//! \param s string where to store the data
	virtual void getAttribute(const String &n,String &s);

	//! link this object under pos

	//! A link will be created to this object under pos with name n.
	//! \param pos position of the link
	//! \param n name of the link
	template<typename ImpL> void createLink(NXObject<ImpL> &pos,const String &n);
	//! link this object under pos

	//! A link to this object will be created under pos using the same
	//! name for the link.
	//! \param pos position of the link
	template<typename ImpL> void createLink(NXObject<ImpL> &pos);

	//! link this object under a path
	virtual void createLink(const String &path);
	virtual void createLink(const String &path,const String &n);

};


//===================constructors and destructor================================
template<typename Imp> NXObject<Imp>::NXObject() {

}

template<typename Imp> NXObject<Imp>::NXObject(const NXObject &o){
	_imp = Imp(o._imp);
}

template<typename Imp> NXObject<Imp> &NXObject<Imp>::operator=(const NXObject &o){
	if(this != &o){
		_imp = o._imp;
	}

	return *this;
}

template<typename Imp> NXObject<Imp>::~NXObject() {
}

//==========methods for obtaining the name and position of the object===========
template<typename Imp> String NXObject<Imp>::getName() const{
	//here we need obviously a better solution
	return _imp.getName();
}

template<typename Imp> String NXObject<Imp>::getBase() const {
	return _imp.getBase();
}

template<typename Imp> String NXObject<Imp>::getPath() const {
	return _imp.getPath();
}

//============methods for handling the implementation object====================

template<typename Imp> void NXObject<Imp>::setImplementation(const Imp &i){
	_imp = i;
}

template<typename Imp> Imp &NXObject<Imp>::getImplementation(){
	return _imp;
}

//==============methods for handling object attributes==========================
template<typename Imp>
void NXObject<Imp>::setAttribute(const String &n,ArrayObject &a){
	_imp.setAttribute(n.c_str(),a);
}

template<typename Imp>
void NXObject<Imp>::setAttribute(const String &n,ScalarObject &s){
	_imp.setAttribute(n.c_str(),s);
}

template<typename Imp>
void NXObject<Imp>::setAttribute(const String &n,const String &s){
	_imp.setAttribute(n.c_str(),s);
}

template<typename Imp>
void NXObject<Imp>::getAttribute(const String &n,String &s){
	_imp.getAttribute(n.c_str(),s);
}

template<typename Imp>
void NXObject<Imp>::getAttribute(const String &n,ArrayObject &a){
	_imp.getAttribute(n.c_str(),a);
}

template<typename Imp>
void NXObject<Imp>::getAttribute(const String &n,ScalarObject &s){
	_imp.getAttribute(n.c_str(),s);
}


//================methods for handling links====================================
template<typename Imp>
template<typename ImpL>
void NXObject<Imp>::createLink(NXObject<ImpL> &pos,const String &n){
	_imp.createLink(pos.getImplementation(),n);
}

template<typename Imp>
template<typename ImpL>
void NXObject<Imp>::createLink(NXObject<ImpL> &pos){
	_imp.createLink(pos.getImplementation(),getName());
}

template<typename Imp>
void NXObject<Imp>::createLink(const String &path){
	_imp.createLink(path);
}

template<typename Imp>
void NXObject<Imp>::createLink(const String &path,const String &n){
	String totpath = "";
	if(path[path.size()]!='/'){
		totpath += path+"/";
	}else{
		totpath += path;
	}
	totpath += n;
	_imp.createLink(totpath);
}

//end of namespace
}
}


#endif /* NXOBJECT_HPP_ */

/*
 * Declaration of Nexus object template.
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
 * Declaration of Nexus object template.
 *
 * Created on: Jul 1, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXOBJECT_HPP_
#define NXOBJECT_HPP_

#include <iostream>

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/ArrayObject.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/ScalarObject.hpp>
#include <pni/utils/Scalar.hpp>

#include "NXImpMap.hpp"

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
private:
	Imp _imp;	//!< implementation object
protected:
	//! get implementation reference

	//! Returns a reference to the actual implementation of an object.
	//! \return reference to implementation
	Imp &getImplementation();


	//! set implementation object

	//! Set the implementation of an object
	//! \param i reference to an implementation
	void setImplementation(const Imp &i);
	void setImplementation(Imp &&i);
public:
	//some type definitions
	typedef typename NXImpMap<Imp::IMPCODE>::ObjectImplementation ObjectImp;
	typedef typename NXImpMap<Imp::IMPCODE>::FieldImplementation FieldImp;
	typedef typename NXImpMap<Imp::IMPCODE>::NumericFieldImplementation NumericFieldImp;
	typedef typename NXImpMap<Imp::IMPCODE>::StringFieldImplementation StringFieldImp;
	typedef typename NXImpMap<Imp::IMPCODE>::GroupImplementation GroupImp;
	typedef typename NXImpMap<Imp::IMPCODE>::FileImplementation FileImp;
	typedef boost::shared_ptr<NXObject<Imp> > sptr;
	//! default constructor
	NXObject();
	//! copy constructor
	//NXObject(const NXObject<Imp> &o);
	template<typename PImp> NXObject(const NXObject<PImp> &o);
	//! move constructor
	//NXObject(NXObject<Imp> &&o);
	template<typename PImp> NXObject(NXObject<PImp> &&o);

	NXObject(Imp &&i){
		_imp = std::move(i);
	}
	//! destructor
	virtual ~NXObject();

	//! copy assignment operator
	template<typename PImp> NXObject<Imp> &operator=(const NXObject<PImp> &o);

	//! move assignment operator
	template<typename PImp> NXObject<Imp> &operator=(NXObject<PImp> &&o);


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
	virtual void setAttribute(const String &n,const ArrayObject &a) const;
	//! write scalar attribute

	//! Write a Scalar object as an attribute to a Nexus object.
	//! \param n name of the attribute
	//! \param s reference to the scalar object
	virtual void setAttribute(const String &n,const ScalarObject &s) const;
	//! write string attribute

	//! Write a string attribute
	//! \param n name of the attribute
	//! \param s String to write as attribute
	virtual void setAttribute(const String &n,const String &s) const;

	//! read Array attribute

	//! Read an array attribute from an object and store its content
	//! in an array object.
	//! \param n name of the attribute
	//! \param a reference to the array object
	virtual void getAttribute(const String &n,ArrayObject &a) const;
	//! read scalar attribute

	//! Read a scalar attribute from an object an store its content in a
	//! scalar attribute.
	//! \param n name of the attribute
	//! \param s reference to the scalar object
	virtual void getAttribute(const String &n,ScalarObject &s) const;
	//! read string attribute

	//! Read a string attribute from an object and store it to a string object.
	//! \param n name of the attribute
	//! \param s string where to store the data
	virtual void getAttribute(const String &n,String &s) const;

	//! link this object under pos

	//! A link will be created to this object under pos with name n.
	//! \param pos position of the link
	//! \param n name of the link
	template<typename ImpL> void createLink(const NXObject<ImpL> &pos,const String &n) const;
	//! link this object under pos

	//! A link to this object will be created under pos using the same
	//! name for the link.
	//! \param pos position of the link
	template<typename ImpL> void createLink(const NXObject<ImpL> &pos) const;

	//! link this object under a path
	virtual void createLink(const String &path) const;
	virtual void createLink(const String &path,const String &n) const;


	//! get implementation const reference

	const Imp &getImplementation() const;

	bool isOpen() const {
		return _imp.isOpen();
	}

};


//===================constructors and destructor================================
//implementation of the default constructor
template<typename Imp> NXObject<Imp>::NXObject() {

}

//------------------------------------------------------------------------------
//implementation of the copy constructor

template<typename Imp>
template<typename PImp>
NXObject<Imp>::NXObject(const NXObject<PImp> &o){
	this->_imp = o.getImplementation();
}

//------------------------------------------------------------------------------
//implementation of the copy constructor
/*
template<typename Imp> NXObject<Imp>::NXObject(const NXObject<Imp> &o){
	this->_imp = Imp(o._imp);
}
*/
//------------------------------------------------------------------------------
//implementation of the move constructor

template<typename Imp>
template<typename PImp>
NXObject<Imp>::NXObject(NXObject<PImp> &&o){
	//express the move constructor in terms of move assignment
	*this = std::move(o);
}


//------------------------------------------------------------------------------
//implementation of the move constructor
/*
template<typename Imp> NXObject<Imp>::NXObject(NXObject<Imp> &&o){
	*this = std::move(o);
}*/

//-----------------------------------------------------------------------------
//implementation of the destructor
template<typename Imp> NXObject<Imp>::~NXObject() {
}


//====================Implementation of assignment operators===================
template<typename Imp>
template<typename PImp> NXObject<Imp> &NXObject<Imp>::operator=(const NXObject<PImp> &o){
	if(this != &o){
		this->_imp = o._imp;
	}

	return *this;
}

template<typename Imp>
template<typename PImp> NXObject<Imp> &NXObject<Imp>::operator=(NXObject<PImp> &&o){
	//we only move the implementation here from one object to the other
	this->_imp = std::move(o._imp);

	return *this;
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

template<typename Imp> void NXObject<Imp>::setImplementation(Imp &&i){
	_imp = std::move(i);
}

template<typename Imp> Imp &NXObject<Imp>::getImplementation(){
	return _imp;
}

template<typename Imp> const Imp &NXObject<Imp>::getImplementation() const{
	return _imp;
}

//==============methods for handling object attributes==========================
template<typename Imp>
void NXObject<Imp>::setAttribute(const String &n,const ArrayObject &a) const{
	_imp.setAttribute(n.c_str(),a);
}

template<typename Imp>
void NXObject<Imp>::setAttribute(const String &n,const ScalarObject &s) const{
	_imp.setAttribute(n,s);
}

template<typename Imp>
void NXObject<Imp>::setAttribute(const String &n,const String &s) const{
	_imp.setAttribute(n,s);
}

template<typename Imp>
void NXObject<Imp>::getAttribute(const String &n,String &s) const{
	_imp.getAttribute(n,s);
}

template<typename Imp>
void NXObject<Imp>::getAttribute(const String &n,ArrayObject &a) const{
	_imp.getAttribute(n,a);
}

template<typename Imp>
void NXObject<Imp>::getAttribute(const String &n,ScalarObject &s) const{
	_imp.getAttribute(n,s);
}


//================methods for handling links====================================
template<typename Imp>
template<typename ImpL>
void NXObject<Imp>::createLink(const NXObject<ImpL> &pos,const String &n) const{
	_imp.createLink(pos.getImplementation(),n);
}

template<typename Imp>
template<typename ImpL>
void NXObject<Imp>::createLink(const NXObject<ImpL> &pos) const{
	_imp.createLink(pos.getImplementation(),getName());
}

template<typename Imp>
void NXObject<Imp>::createLink(const String &path) const{
	_imp.createLink(path);
}

template<typename Imp>
void NXObject<Imp>::createLink(const String &path,const String &n) const{
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

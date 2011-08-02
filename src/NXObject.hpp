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

template<typename Imp>
class NXObject {
protected:
	Imp _imp;
public:
	typedef boost::shared_ptr<NXObject<Imp> > sptr;
	NXObject();
	NXObject(const NXObject &o);
	virtual ~NXObject();

	NXObject<Imp> &operator=(const NXObject &o);

	Imp &getImplementation(){
		return _imp;
	}
	void setImplementation(const Imp &i);
	virtual pni::utils::String getName() const;

	//here comes a bunch of methods to handle attributes

	virtual void setAttribute(const pni::utils::String &n,pni::utils::ArrayObject &a);
	virtual void setAttribute(const pni::utils::String &n,pni::utils::ArrayObject::sptr a);

	virtual void setAttribute(const pni::utils::String &n,pni::utils::ScalarObject &s);
	virtual void setAttribute(const pni::utils::String &n,pni::utils::ScalarObject::sptr s);

	virtual void setAttribute(const pni::utils::String &n,const pni::utils::String &s);


	virtual void getAttribute(const pni::utils::String &n,pni::utils::ArrayObject &a);
	virtual void getAttribute(const pni::utils::String &n,pni::utils::ArrayObject::sptr a);

	virtual void getAttribute(const pni::utils::String &n,pni::utils::ScalarObject &s);
	virtual void getAttribute(const pni::utils::String &n,pni::utils::ScalarObject::sptr s);

	virtual void getAttribute(const pni::utils::String &n,pni::utils::String &s);





};

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

template<typename Imp> String NXObject<Imp>::getName() const{
	//here we need obviously a better solution
	return String("NIX");
}

template<typename Imp>
void NXObject<Imp>::setImplementation(const Imp &i){
	_imp = i;
}

template<typename Imp>
void NXObject<Imp>::setAttribute(const String &n,ArrayObject &a){
	_imp.setAttribute(n.c_str(),a);
}

template<typename Imp>
void NXObject<Imp>::setAttribute(const String &n,ArrayObject::sptr a){
	setAttribute(n,*a);
}


template<typename Imp>
void NXObject<Imp>::setAttribute(const String &n,ScalarObject &s){
	_imp.setAttribute(n.c_str(),s);
}

template<typename Imp>
void NXObject<Imp>::setAttribute(const String &n,ScalarObject::sptr s){
	setAttribute(n,*s);
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
void NXObject<Imp>::getAttribute(const String &n,ArrayObject::sptr a){
	_imp.getAttribute(n.c_str(),*a);

}

template<typename Imp>
void NXObject<Imp>::getAttribute(const String &n,ScalarObject &s){
	_imp.getAttribute(n.c_str(),s);
}

template<typename Imp>
void NXObject<Imp>::getAttribute(const String &n,ScalarObject::sptr s){
	_imp.getAttribute(n.c_str(),*s);
}

//end of namespace
}
}


#endif /* NXOBJECT_HPP_ */

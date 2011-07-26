/*
 * NXField.hpp
 *
 *  Created on: Jul 3, 2011
 *      Author: eugen
 */

#ifndef NXFIELD_HPP_
#define NXFIELD_HPP_

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/ScalarObject.hpp>
#include <pni/utils/Scalar.hpp>
#include <pni/utils/ArrayShape.hpp>
#include <pni/utils/ArrayObject.hpp>
#include <pni/utils/Array.hpp>

#include "NXObject.hpp"

namespace pni{
namespace nx{

template<typename Imp>
class NXField:public NXObject<Imp> {
public:
	typedef boost::shared_ptr<NXField<Imp> > sptr;
	NXField();
	NXField(const NXField<Imp> &);
	virtual ~NXField();

	NXField &operator=(const NXField<Imp> &);

	//inquery of a field
	pni::utils::UInt32 getRank();

	//! get dimension of a field
	pni::utils::UInt32 getDimension(pni::utils::UInt32 i);

	//need a function here to get an array rank from a field
	virtual void getArrayShapeFromField(pni::utils::ArrayShape &s){

	}

	//need something like a selection object to fetch only the data needed
	virtual void setSelection(){

	}

	//need methods to access data stored in the field
	void write(pni::utils::ArrayObject::sptr a);
	void write(pni::utils::ArrayObject &a);
	void write(pni::utils::ScalarObject::sptr s);
	void write(pni::utils::ScalarObject &s);
	void write(pni::utils::String &s);
	template<typename T> void write(typename pni::utils::Array<T>::sptr a);
	template<typename T> void write(pni::utils::Array<T> &a);
	template<typename T> void write(typename pni::utils::Scalar<T>::sptr s);
	template<typename T> void write(pni::utils::Scalar<T> &s);

	//need methods to write data to the field
	void read(pni::utils::ArrayObject::sptr a);
	void read(pni::utils::ArrayObject &a);
	void read(pni::utils::ScalarObject::sptr s);
	void read(pni::utils::ScalarObject &s);
	void read(pni::utils::String &s);
	template<typename T> void read(typename pni::utils::Array<T>::sptr a);
	template<typename T> void read(pni::utils::Array<T> &a);
	template<typename T> void read(typename pni::utils::Scalar<T>::sptr s);
	template<typename T> void read(pni::utils::Scalar<T> &s);

	void close();



};

template<typename Imp>
NXField<Imp>::NXField() {
	// TODO Auto-generated constructor stub

}

template<typename Imp>
NXField<Imp>::NXField(const NXField<Imp> &o){
	this->_imp = o._imp;
}

template<typename Imp>
NXField<Imp>::~NXField() {
	// TODO Auto-generated destructor stub
}

template<typename Imp>
NXField<Imp> &NXField<Imp>::operator=(const NXField<Imp> &o){
	if( this != &o){
		this->_imp = o._imp;
	}
	return *this;
}

template<typename Imp>
void NXField<Imp>::write(pni::utils::ArrayObject &a){
	this->_imp.write(a);
}

template<typename Imp>
void NXField<Imp>::write(pni::utils::ArrayObject::sptr a){
	pni::utils::ArrayObject &data = *a;
	write(data);
}

template<typename Imp>
void NXField<Imp>::write(pni::utils::ScalarObject &s){
	this->_imp.write(s);
}

template<typename Imp>
void NXField<Imp>::write(pni::utils::String &s){
	this->_imp.write(s);
}

template<typename Imp>
template<typename T> void NXField<Imp>::write(typename pni::utils::Array<T>::sptr a){
	write(boost::dynamic_pointer_cast<pni::utils::ArrayObject>(a));
}

template<typename Imp>
template<typename T> void NXField<Imp>::write(pni::utils::Array<T> &a){
	write((pni::utils::ArrayObject &)a);
}

template<typename Imp>
void NXField<Imp>::write(pni::utils::ScalarObject::sptr s){
	pni::utils::ScalarObject &data = *s;
	write(data);
}

template<typename Imp>
void NXField<Imp>::read(pni::utils::ArrayObject::sptr a){
	read(*a);
}
template<typename Imp>
void NXField<Imp>::read(pni::utils::ArrayObject &a){
	this->_imp.read(a);
}

template<typename Imp>
void NXField<Imp>::read(pni::utils::ScalarObject::sptr s){
	read(*s);
}

template<typename Imp>
void NXField<Imp>::read(pni::utils::ScalarObject &s){
	this->_imp.read(s);
}

template<typename Imp>
void NXField<Imp>::read(pni::utils::String &s){
	this->_imp.read(s);
}


template<typename Imp>
template<typename T>
void NXField<Imp>::read(typename pni::utils::Array<T>::sptr a){
	read(boost::dynamic_pointer_cast<pni::utils::ArrayObject>(a));
}

template<typename Imp>
template<typename T>
void NXField<Imp>::read(pni::utils::Array<T> &a){
	read((pni::utils::ArrayObject &)a);
}

template<typename Imp>
template<typename T>
void NXField<Imp>::read(typename pni::utils::Scalar<T>::sptr s){
	read(boost::dynamic_pointer_cast<pni::utils::ScalarObject>(s));
}

template<typename Imp>
template<typename T>
void NXField<Imp>::read(pni::utils::Scalar<T> &s){
	read((pni::utils::ScalarObject &)s);
}

template<typename Imp>
void NXField<Imp>::close(){
	this->_imp.close();
}


//end of namespace
}
}

#endif /* NXFIELD_HPP_ */

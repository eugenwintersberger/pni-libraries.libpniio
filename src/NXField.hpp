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
#include "NXExceptions.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{

template<typename Imp>
class NXField:public NXObject<Imp> {
private:

public:
	typedef boost::shared_ptr<NXField<Imp> > sptr;
	NXField();
	NXField(const NXField<Imp> &);
	virtual ~NXField();

	NXField<Imp> &operator=(const NXField<Imp> &);

	//inquery of a field
	UInt32 getRank() const{
		return this->_imp.getRank();
	}

	//! get dimension of a field
	UInt32 getDimension(UInt32 i) const {
		return this->_imp.getDimension(i);
	}

	//! get all dimensions
	UInt32 *getDimensions() const {
		return this->_imp.getDimensions();
	}

	//need a function here to get an array rank from a field
	virtual void getShape(ArrayShape &s) const{
		s.setRank(this->_imp.getRank());
		for(UInt64 i=0;i<s.getRank();i++) s.setDimension(i,this->_imp.getDimension(i));
	}

	//get the type ID
	virtual PNITypeID getTypeID() const {
		return this->_imp.getTypeID();
	}

	virtual UInt64 getSize() const {
		return this->_imp.getSize();
	}

	virtual String getName() const {
		return this->_imp.getName();
	}

	//need something like a selection object to fetch only the data needed
	virtual void setSelection(){

	}

	//need methods to access data stored in the field
	void write(ArrayObject::sptr a);
	void write(ArrayObject::sptr a,const Selection &s);
	void write(ArrayObject &a);
	void write(ArrayObject &a,const Selection &s);
	void write(ScalarObject &s);
	void write(ScalarObject::sptr s);
	void write(String &s);
	void write(const void *ptr);

	//need methods to write data to the field
	void read(ArrayObject::sptr a) const;
	void read(ArrayObject::sptr a,const Selection &s);
	void read(ArrayObject &a) const;
	void read(ArrayObject &a,const Selection &s);
	void read(ScalarObject::sptr s) const;
	void read(ScalarObject &s) const;
	void read(String &s) const;
	void read(void *ptr) const;

	void close();



};

template<typename Imp>
NXField<Imp>::NXField() {
	// TODO Auto-generated constructor stub

}

template<typename Imp> NXField<Imp>::NXField(const NXField<Imp> &o){
	this->_imp = o._imp;
}

template<typename Imp> NXField<Imp>::~NXField() {
	// TODO Auto-generated destructor stub
	close();
}

template<typename Imp> NXField<Imp> &NXField<Imp>::operator=(const NXField<Imp> &o){
	if( this != &o){
		this->_imp = o._imp;
	}
	return *this;
}


template<typename Imp> void NXField<Imp>::write(ArrayObject &a){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::write(pni::utils::ArrayObject &a)");
	ArrayShape s;
	getShape(s);

	if(!(this->_imp.isArray())){
		EXCEPTION_INIT(NXFieldError,"Field ["+getName()+"] is not of array type!");
		EXCEPTION_THROW();
	}

	//check the data type of the object and the field
	if(a.getTypeID()!=this->_imp.getTypeID()){
		EXCEPTION_INIT(TypeError,"Array and field type do not match!");
		EXCEPTION_THROW();
	}

	//have to do here some checking
	if(a.getShape()!=s){
		EXCEPTION_INIT(ShapeMissmatchError,"Array and field shape do not match!");
		EXCEPTION_THROW();
	}

	try{
		this->_imp.write(a.getBuffer().getVoidPtr());
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error writing array data to field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}

template<typename Imp> void NXField<Imp>::write(ArrayObject::sptr a){
	write(*a);
}

template<typename Imp> void NXField<Imp>::write(ScalarObject &s){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::write(ScalarObject &s)");

	if(!(this->_imp.isScalar())){
		EXCEPTION_INIT(NXFieldError,"Field ["+this->_imp.getName()+"] is not a scalar field!");
		EXCEPTION_THROW();
	}

	if(s.getTypeID()!=this->_imp.getTypeID()){
		EXCEPTION_INIT(TypeError,"Scalar and field type do not match!");
		EXCEPTION_THROW();
	}

	try{
		this->_imp.write(s.getVoidPtr());
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error writing data to scalar field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}

template<typename Imp> void NXField<Imp>::write(ScalarObject::sptr s){
	write(*s);
}

template<typename Imp> void NXField<Imp>::write(String &s){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::write(pni::utils::String &s)");

	if(!this->_imp.isString()){
		EXCEPTION_INIT(NXFieldError,"Field ["+getName()+"] is not of string type!");
		EXCEPTION_THROW();
	}

	//check if the size fits
	if((this->_imp.getSize())!=s.size()){
		EXCEPTION_INIT(SizeMissmatchError,"Size of input string and string field do not match!");
		EXCEPTION_THROW();
	}

	try{
		this->_imp.write((void *)s.c_str());
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error writing string data to field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}



template<typename Imp> void NXField<Imp>::read(ArrayObject::sptr a) const{
	read(*a);
}
template<typename Imp> void NXField<Imp>::read(ArrayObject &a) const{
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::read(ArrayObject &a) const");

	if(!(this->_imp.isArray())){
		EXCEPTION_INIT(NXFieldError,"Field ["+this->_imp.getName()+"] is not of array type!");
		EXCEPTION_THROW();
	}

	if(a.getTypeID() != this->_imp.getTypeID()){
		EXCEPTION_INIT(TypeError,"Type of field ["+this->_imp.getName()+"] does not match target type!");
		EXCEPTION_THROW();
	}

	//get the shape of the field to read
	ArrayShape s;
	this->_imp.getShape(s);

	//the shape of the target array and that of the field
	if(a.getShape().getRank()!=0){
		if(s != a.getShape()){
			a.setShape(s);
			a.allocate();
		}
	}else{
		a.setShape(s);
		a.allocate();
	}

	try{
		this->_imp.read((void *)a.getBuffer().getVoidPtr());
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Cannot read array data from field ["+this->_imp.getName()+"]!");
		EXCEPTION_THROW();
	}
}

template<typename Imp> void NXField<Imp>::read(ScalarObject::sptr s) const{
	read(*s);
}

template<typename Imp> void NXField<Imp>::read(ScalarObject &s) const{
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::read(ScalarObject &s) const");

	if(!(this->_imp.isScalar())){
		EXCEPTION_INIT(NXFieldError,"Field ["+getName()+"] is not of type scalar!");
		EXCEPTION_THROW();
	}

	if(s.getTypeID() != this->_imp.getTypeID()){
		EXCEPTION_INIT(TypeError,"Field ["+getName()+"] and target scalar are of different type!");
		EXCEPTION_THROW();
	}

	try{
		this->_imp.read(s.getVoidPtr());
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Scalar data cannot be read from field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}

template<typename Imp> void NXField<Imp>::read(String &s) const{
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::read(String &s) const");

	if(!(this->_imp.isString())){
		EXCEPTION_INIT(NXFieldError,"Field ["+getName()+"] is not of type string!");
		EXCEPTION_THROW();
	}

	s.clear();
	s.resize(this->_imp.getSize());

	try{
		this->_imp.read((void *)s.c_str());
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error reading string data from field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}


template<typename Imp> void NXField<Imp>::close(){
	this->_imp.close();
}


//end of namespace
}
}

#endif /* NXFIELD_HPP_ */

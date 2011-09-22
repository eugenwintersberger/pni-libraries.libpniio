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
#include <pni/utils/NumericObject.hpp>

#include "NXObject.hpp"
#include "NXExceptions.hpp"
#include "NXSelection.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{

template<typename Imp>
class NXField:public NXObject<Imp> {
private:
	NumericObject *_iobuffer;
	const NXSelection<typename NXImpMap<Imp::IMPCODE>::SelectionImplementation > *_selection;
protected:
	void write(const void *ptr);
	void read(void *ptr) const;
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
	virtual ArrayShape getShape() const{
		ArrayShape s(this->_imp.getRank());
		for(UInt64 i=0;i<s.getRank();i++) s.setDimension(i,this->_imp.getDimension(i));

		return s;
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

	virtual void registerDataObject(ArrayObject &o);
	virtual void registerDataObject(ScalarObject &o);
	virtual void resetDataObject();

	//need something like a selection object to fetch only the data needed
	virtual void registerSelection(NXSelection<typename NXImpMap<Imp::IMPCODE>::SelectionImplementation > &s);

	void resetSelection();

	//need methods to access data stored in the field
	void write(ArrayObject &a);
	void write(ScalarObject &s);
	void write(String &s);
	void write();

	//need methods to write data to the field
	void read(ArrayObject &a);
	void read(ScalarObject &s);
	void read(String &s) const;
	void read();

	void close();



};

//--------------constructors and destructors------------------------------------

template<typename Imp> NXField<Imp>::NXField() {
	// TODO Auto-generated constructor stub
	_iobuffer = NULL;
	_selection = NULL;

}

template<typename Imp> NXField<Imp>::NXField(const NXField<Imp> &o){
	this->_imp = o._imp;

	_iobuffer = NULL;
	_selection = NULL;
}

template<typename Imp> NXField<Imp>::~NXField() {
	// TODO Auto-generated destructor stub
	close();
	_iobuffer = NULL;
	_selection = NULL;
}

//------------------------------operators---------------------------------------
template<typename Imp> NXField<Imp> &NXField<Imp>::operator=(const NXField<Imp> &o){
	if( this != &o){
		this->_imp = o._imp;

		_iobuffer = o._iobuffer;
		_selection = o._selection;
	}
	return *this;
}

//--------------------------write operations------------------------------------
template<typename Imp> void NXField<Imp>::write(ArrayObject &a){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::write(pni::utils::ArrayObject &a)");
	ArrayShape s = getShape();

	//an array must always be stored to an array type field
	if(!(this->_imp.isArray())){
		EXCEPTION_INIT(NXFieldError,"Field ["+getName()+"] is not of array type!");
		EXCEPTION_THROW();
	}

	//check the data type of the object and the field
	if(a.getTypeID()!=this->_imp.getTypeID()){
		EXCEPTION_INIT(TypeError,"Array and field type do not match!");
		EXCEPTION_THROW();
	}

	//check if the array is allocated
	if(!a.isAllocated()){
		EXCEPTION_INIT(MemoryAccessError,"Array ["+a.getName()+"] seems to be not allocated!");
		EXCEPTION_THROW();
	}

	//have to do some shape checking here
	if(_selection != NULL){
		//if a selection is present the shape of the array must match the
		//shape of the selection in memory.
		if(a.getShape() != _selection->getMemShape()){
			EXCEPTION_INIT(ShapeMissmatchError,"Array and selection shape do not match!");
			EXCEPTION_THROW();
		}
	}else{
		//if no selection object is set the shape of the array must match the
		//shape of the entire field
		if(a.getShape()!=s){
			EXCEPTION_INIT(ShapeMissmatchError,"Array and field shape do not match!");
			EXCEPTION_THROW();
		}
	}

	//if a selection object is registered we have to reapply it to the
	//data set
	if(_selection != NULL) this->_imp.setSelection(*_selection);

	//try to write data
	try{
		this->_imp.write(a.getVoidPtr());
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error writing array data to field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}


template<typename Imp> void NXField<Imp>::write(ScalarObject &s){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::write(ScalarObject &s)");

	if((this->_imp.isArray())&&(_selection != NULL)){
		if(_selection->getMemShape().getSize() != 1){
			EXCEPTION_INIT(ShapeMissmatchError,"If a scalar should be written to an array the selection size must be 1!");
			EXCEPTION_THROW();
		}
	}else{
		//if the field is an array and no selection is set we have to
		//raise an exception
		if(!(this->_imp.isScalar())){
			EXCEPTION_INIT(NXFieldError,"Field ["+this->_imp.getName()+"] is not a scalar field!");
			EXCEPTION_THROW();
		}
	}

	//check the data type - this we have to do in any case
	if(s.getTypeID()!=this->_imp.getTypeID()){
		EXCEPTION_INIT(TypeError,"Scalar and field type do not match!");
		EXCEPTION_THROW();
	}

	if(_selection != NULL) this->_imp.setSelection(*_selection);

	try{
		this->_imp.write(s.getVoidPtr());
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error writing data to scalar field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
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

template<typename Imp> void NXField<Imp>::write(){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::write()");

	if(!((_selection != NULL)&&(_iobuffer != NULL))){
		EXCEPTION_INIT(NXFieldError,"No selection or buffer registered at field ["+getName()+"]!");
		EXCEPTION_THROW();
	}

	this->_imp.setSelection(*_selection);

	try{
		this->_imp.write(_iobuffer->getVoidPtr());
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error writing data to field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}

template<typename Imp> void NXField<Imp>::read(){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::write()");

	if(!((_selection != NULL)&&(_iobuffer != NULL))){
		EXCEPTION_INIT(NXFieldError,"No selection or buffer registered at field ["+getName()+"]!");
		EXCEPTION_THROW();
	}

	this->_imp.setSelection(*_selection);

	try{
		this->_imp.read(_iobuffer->getVoidPtr());
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Error writing data to field ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}

//----------------------read operations-----------------------------------------
template<typename Imp> void NXField<Imp>::read(ArrayObject &a){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::read(ArrayObject &a) const");

	//arrays can only be read from array fields
	if(!(this->_imp.isArray())){
		EXCEPTION_INIT(NXFieldError,"Field ["+this->_imp.getName()+"] is not of array type!");
		EXCEPTION_THROW();
	}

	//check the type
	if(a.getTypeID() != this->_imp.getTypeID()){
		EXCEPTION_INIT(TypeError,"Type of field ["+this->_imp.getName()+"] does not match target type!");
		EXCEPTION_THROW();
	}

	//have to check if the array is allocated
	if(!a.isAllocated()){
		EXCEPTION_INIT(MemoryAccessError,"Array ["+a.getName()+"] seems to be not allocated!");
		EXCEPTION_THROW();
	}

	//check the shape of the array
	if(_selection != NULL){
		//if a selection object is associated with this field the shape of the
		//array must match the memory shape of the selection.
		if(a.getShape()!=_selection->getMemShape()){
			EXCEPTION_INIT(ShapeMissmatchError,"Shapes of field ["+getName()+"] and the selection of array ["+a.getName()+"] do not match!");
			EXCEPTION_THROW();
		}
	}else{
		//if there is no selection
		ArrayShape fs;
		this->_imp.getShape(fs);
		if(a.getShape()!=fs){
			EXCEPTION_INIT(ShapeMissmatchError,"Shapes of field ["+getName()+"] and array ["+a.getName()+"] do not match!");
			EXCEPTION_THROW();
		}
	}

	if(_selection != NULL) this->_imp.setSelection(*_selection);

	try{
		this->_imp.read((void *)a.getBuffer().getVoidPtr());
	}catch(...){
		EXCEPTION_INIT(NXFieldError,"Cannot read array data from field ["+this->_imp.getName()+"]!");
		EXCEPTION_THROW();
	}
}


template<typename Imp> void NXField<Imp>::read(ScalarObject &s){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::read(ScalarObject &s) const");

	//check the shape
	if((this->_imp.isArray())&&(_selection != NULL)){
		if(_selection->getMemShape().getSize() != 1){
			EXCEPTION_INIT(ShapeMissmatchError,"If a scalar should be written to an array the selection size must be 1!");
			EXCEPTION_THROW();
		}
	}else{
		//if the field is an array and no selection is set we have to
		//raise an exception
		if(!(this->_imp.isScalar())){
			EXCEPTION_INIT(NXFieldError,"Field ["+this->_imp.getName()+"] is not a scalar field!");
			EXCEPTION_THROW();
		}
	}

	//check data type
	if(s.getTypeID() != this->_imp.getTypeID()){
		EXCEPTION_INIT(TypeError,"Field ["+getName()+"] and target scalar are of different type!");
		EXCEPTION_THROW();
	}

	//set the selection if necessary
	if(_selection != NULL) this->_imp.setSelection(*_selection);

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

//------------------convienance methods-----------------------------------------
template<typename Imp> void NXField<Imp>::close(){
	this->_imp.close();
}

template<typename Imp> void NXField<Imp>::registerDataObject(ArrayObject &o){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::registerDataObject(NumericObject &o)");

	//first check the data type
	if(o.getTypeID() != getTypeID()){
		EXCEPTION_INIT(TypeError,"Type of data object ["+o.getName()+"] and field ["+getName()+"] have different type!");
		EXCEPTION_THROW();
	}

	if(_selection != NULL){
		//there already exists a selection object we have to check the shape
		if(_selection->getMemShape() != o.getShape()){
			EXCEPTION_INIT(ShapeMissmatchError,"Shapes of array and selection object to not match!");
			EXCEPTION_THROW();
		}

	}
	_iobuffer = &o;

}

template<typename Imp> void NXField<Imp>::registerDataObject(ScalarObject &o){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::registerDataObject(ScalarObject &o)");

	if(o.getTypeID() != getTypeID()){
		EXCEPTION_INIT(TypeError,"Type of data object ["+o.getName()+"] and field ["+getName()+"] have different type!");
		EXCEPTION_THROW();
	}

	if(_selection != NULL){
		//if there exists already a selection object
		if(_selection->getMemShape().getSize() != 1){
			EXCEPTION_INIT(ShapeMissmatchError,"To store a scalar in an array object requires a selection of size 1!");
			EXCEPTION_THROW();
		}
	}

	_iobuffer = &o;
}

template<typename Imp> void NXField<Imp>::resetDataObject(){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::resetDataObject() const");
	_iobuffer = NULL;

}

	//need something like a selection object to fetch only the data needed
template<typename Imp>
void NXField<Imp>::registerSelection(NXSelection<typename NXImpMap<Imp::IMPCODE>::SelectionImplementation > &s){
	EXCEPTION_SETUP("template<typename Imp> void NXField<Imp>::registerSelection(const NXSelection<typename NXImpMap<Imp::IMPCODE>::SelectionImplementation > &s)");
	this->_imp.registerSelection(s);
	_selection = &s;

}


template<typename Imp> void NXField<Imp>::resetSelection(){
		this->_imp.resetSelection();
		_selection = NULL;
}

//end of namespace
}
}

#endif /* NXFIELD_HPP_ */

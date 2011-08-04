/*
 * H5Exceptions.cpp
 *
 *  Created on: Jul 6, 2011
 *      Author: Eugen Wintersberger
 *
 *  Implementation of exceptions for the HDF5 interface of the Nexus API.
 */

#include "H5Exceptions.hpp"

namespace pni{
namespace nx{
namespace h5{

H5Exception::H5Exception():Exception(){
	_h5estack.getStack();
}

H5Exception::H5Exception(const String &n):Exception(n){
	_h5estack.getStack();
}

H5Exception::H5Exception(const String &n,const String &i,const String &d)
			:Exception(n,i,d){
	_h5estack.getStack();
}

H5Exception::H5Exception(const H5Exception &e){
	setName(e.getName());
	setIssuer(e.getIssuer());
	setDescription(e.getDescription());

	_h5estack = e._h5estack;
}

H5Exception::~H5Exception(){
}

std::ostream &H5Exception::print(std::ostream &o) const{
	o<<getName()<<" from "+getIssuer()<<std::endl;
	o<<getDescription()<<std::endl;
	o<<_h5estack;

	return o;
}

std::ostream &operator<<(std::ostream &o,const H5Exception &e){
	return e.print(o);
}

H5DataTypeError::H5DataTypeError()
:H5Exception("H5DataTypeException")
{}

H5DataTypeError::H5DataTypeError(const String &i,const String &d):
	H5Exception("H5DataTypeException",i,d){
}

H5DataTypeError::~H5DataTypeError(){

}

std::ostream &operator<<(std::ostream &o,const H5DataTypeError &e){
	return e.print(o);
}

H5DataSetError::H5DataSetError():H5Exception("H5DataTypeException"){
}

H5DataSetError::H5DataSetError(const String &i,const String &d)
:H5Exception("H5DataTypeException",i,d){
}

H5DataSetError::~H5DataSetError()
{
}

std::ostream &operator<<(std::ostream &o,const H5DataSetError &e){
	return e.print(o);
}

H5DataSpaceError::H5DataSpaceError():H5Exception("H5DataSpaceException"){
}

H5DataSpaceError::H5DataSpaceError(const String &i,const String &d):H5Exception("H5DataSpaceException",i,d){

}

H5DataSpaceError::~H5DataSpaceError(){

}

std::ostream &operator<<(std::ostream &o,const H5DataSpaceError &e){
	return e.print(o);
}

H5AttributeError::H5AttributeError():H5Exception("H5AttributeException"){
}

H5AttributeError::H5AttributeError(const String &i,const String &d):H5Exception("H5AttributeException",i,d){

}

H5AttributeError::~H5AttributeError(){

}

std::ostream &operator<<(std::ostream &o,const H5AttributeError &e){
	return e.print(o);
}

H5FileError::H5FileError():H5Exception("H5FileException"){
}

H5FileError::H5FileError(const String &i,const String &d):H5Exception("H5FileException",i,d){
}

H5FileError::~H5FileError(){
}

std::ostream &operator<<(std::ostream &o,const H5FileError &e){
	return e.print(o);
}

H5GroupError::H5GroupError():H5Exception("H5GroupException"){
}

H5GroupError::H5GroupError(const String &i,const String &d):H5Exception("H5GroupException",i,d){
}

H5GroupError::~H5GroupError(){
}

std::ostream &operator<<(std::ostream &o,const H5GroupError &e){
	return e.print(o);
}

//end of namespace
}
}
}


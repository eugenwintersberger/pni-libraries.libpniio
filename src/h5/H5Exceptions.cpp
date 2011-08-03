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

H5Exception::H5Exception():pni::nx::NXException(){
	_h5estack.getStack();
}

H5Exception::H5Exception(const String &n):pni::nx::NXException(n){
	_h5estack.getStack();
}

H5Exception::H5Exception(const String &n,const String &i,const String &d)
			:pni::nx::NXException(n,i,d){
	_h5estack.getStack();
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

H5DataTypeException::H5DataTypeException()
:H5Exception("H5DataTypeException")
{}

H5DataTypeException::H5DataTypeException(const String &i,const String &d):
	H5Exception("H5DataTypeException",i,d){
}

H5DataTypeException::~H5DataTypeException(){

}

std::ostream &operator<<(std::ostream &o,const H5DataTypeException &e){
	return e.print(o);
}

H5DataSetException::H5DataSetException():H5Exception("H5DataTypeException"){
}

H5DataSetException::H5DataSetException(const String &i,const String &d)
:H5Exception("H5DataTypeException",i,d){
}

H5DataSetException::~H5DataSetException()
{
}

std::ostream &operator<<(std::ostream &o,const H5DataSetException &e){
	return e.print(o);
}

H5DataSpaceException::H5DataSpaceException():H5Exception("H5DataSpaceException"){
}

H5DataSpaceException::H5DataSpaceException(const String &i,const String &d):H5Exception("H5DataSpaceException",i,d){

}

H5DataSpaceException::~H5DataSpaceException(){

}

std::ostream &operator<<(std::ostream &o,const H5DataSpaceException &e){
	return e.print(o);
}

H5AttributeException::H5AttributeException():H5Exception("H5AttributeException"){
}

H5AttributeException::H5AttributeException(const String &i,const String &d):H5Exception("H5AttributeException",i,d){

}

H5AttributeException::~H5AttributeException(){

}

std::ostream &operator<<(std::ostream &o,const H5AttributeException &e){
	return e.print(o);
}

H5FileException::H5FileException():H5Exception("H5FileException"){
}

H5FileException::H5FileException(const String &i,const String &d):H5Exception("H5FileException",i,d){
}

H5FileException::~H5FileException(){
}

std::ostream &operator<<(std::ostream &o,const H5FileException &e){
	return e.print(o);
}

//end of namespace
}
}
}


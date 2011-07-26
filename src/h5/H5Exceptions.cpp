/*
 * H5Exceptions.cpp
 *
 *  Created on: Jul 6, 2011
 *      Author: Eugen Wintersberger
 *
 *  Implementation of exceptions for the HDF5 interface of the Nexus API.
 */

#include "H5Exceptions.hpp"

namespace nx{
namespace h5{

H5Exception::H5Exception(){
	_name.clear();
	_issuer.clear();
	_description.clear();
}

H5Exception::H5Exception(const String &n){
	_name = n;
	_issuer.clear();
	_description.clear();
}

H5Exception::H5Exception(const String &n,const String &i,const String &d){
	_name = n;
	_issuer = i;
	_description = d;
}

H5Exception::~H5Exception(){
	_name.clear();
	_issuer.clear();
	_description.clear();
}

void H5Exception::setName(const String &n){
	_name = n;
}

String H5Exception::getName() const{
	return _name;
}

void H5Exception::setIssuer(const String &i){
	_issuer = i;
}

String H5Exception::getIssuer() const{
	return _issuer;
}

void H5Exception::setDescription(const String &d){
	_description = d;
}

String H5Exception::getDescription() const{
	return _description;
}

std::ostream &operator<<(std::ostream &o,const H5Exception &e){
	o<<e._name<<" from "+e._issuer<<std::endl;
	o<<e._description;

	return o;
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
	o<<e._name<<" from "+e._issuer<<std::endl;
	o<<e._description;

	return o;
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
	o<<e._name<<" from "+e._issuer<<std::endl;
	o<<e._description;

	return o;
}

H5DataSpaceException::H5DataSpaceException():H5Exception("H5DataSpaceException"){
}

H5DataSpaceException::H5DataSpaceException(const String &i,const String &d):H5Exception("H5DataSpaceException",i,d){

}

H5DataSpaceException::~H5DataSpaceException(){

}

std::ostream &operator<<(std::ostream &o,const H5DataSpaceException &e){
	o<<e._name<<" from "+e._issuer<<std::endl;
	o<<e._description;

	return o;
}

H5AttributeException::H5AttributeException():H5Exception("H5AttributeException"){
}

H5AttributeException::H5AttributeException(const String &i,const String &d):H5Exception("H5AttributeException",i,d){

}

H5AttributeException::~H5AttributeException(){

}

std::ostream &operator<<(std::ostream &o,const H5AttributeException &e){
	o<<e._name<<" from "+e._issuer<<std::endl;
	o<<e._description;

	return o;
}

//end of namespace
}
}


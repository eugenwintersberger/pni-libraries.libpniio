/*
 * NXException.cpp
 *
 *  Created on: Aug 3, 2011
 *      Author: eugen
 */

#include "NXException.hpp"

namespace pni {

namespace nx {

NXException::NXException() {
	_name = "";
	_issuer = "";
	_description = "";

	_prev_exception.reset();
}

NXException::NXException(const String &n){
	_name = n;
	_issuer = "";
	_description = "";

	_prev_exception.reset();
}

NXException::NXException(const String &n,const String &i){
	_name = n;
	_issuer = i;
	_description = "";

	_prev_exception.reset();
}

NXException::NXException(const String &n,const String &i,const String &d){
	_name = n;
	_issuer = i;
	_description = d;

	_prev_exception.reset();
}

NXException::NXException(const NXException &e){
	_name = e._name;
	_issuer = e._issuer;
	_description = e._description;
	_prev_exception = e._prev_exception;
}

NXException::~NXException() {
	_prev_exception.reset();
}

NXException &NXException::operator=(const NXException &e){
	if(this != &e){
		_name = e._name;
		_issuer = e._issuer;
		_description = e._description;

		_prev_exception = e._prev_exception;
	}

	return *this;
}

void NXException::setName(const String &n){
	_name = n;
}

String NXException::getName() const{
	return _name;
}

void NXException::setIssuer(const String &i){
	_issuer = i;
}

String NXException::getIssuer() const{
	return _issuer;
}

void NXException::setDescription(const String &d){
	_description = d;
}

String NXException::getDescription() const{
	return _description;
}

void NXException::setPreviousException(NXException::sptr prev){
	_prev_exception = prev;
}

//end of namespace
}
}

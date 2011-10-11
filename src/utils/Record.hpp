/*
 * Record.hpp
 *
 *  Created on: Sep 29, 2011
 *      Author: eugen
 */

#ifndef RECORD_HPP_
#define RECORD_HPP_

#include <iostream>
#include <map>

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/Exceptions.hpp>

#include "../NXField.hpp"
#include "../NXSelection.hpp"

using namespace pni::utils;

namespace pni {
namespace nx {

//collection of field objects used to write data with a single call.
template<typename FieldImp> class Record {
private:
	typedef std::map<String,FieldImp > RecordMap;
	typedef typename RecordMap::iterator RecordIterator;
	typedef typename RecordMap::const_iterator RecordConstIterator;

	RecordMap _record;
public:
	Record(){}
	virtual ~Record(){}

	virtual void registerSelection(const String &n,NXSelection<typename FieldImp::SelectionImplementation > &s);
	virtual void resetSelection(const String &n);
	virtual void registerDataObject(const String &n,ScalarObject &o);
	virtual void registerDataObject(const String &n,ArrayObject &o);
	virtual void resetDataObject(const String &n);
	virtual void write();
	virtual void read();
	virtual void insert(FieldImp &s);
	virtual void erase(const String &n);

	virtual FieldImp &operator[](const String &k);
	virtual FieldImp operator[](const String &k) const;

};

template<typename FieldImp>
void Record<FieldImp>::registerSelection(const String &n,NXSelection<typename FieldImp::SelectionImplementation > &s){
	EXCEPTION_SETUP("template<typename FieldImp> void Record<FieldImp>::registerSelection(const String &n,NXSelection<typename FieldImp::SelectionImplementation > &s)");

	_record[n].registerSelection(s);
}

template<typename FieldImp> void Record<FieldImp>::resetSelection(const String &n){
	EXCEPTION_SETUP("template<typename FieldImp> void Record<FieldImp>::resetSelection(const String &n)");
	_record[n].resetSelection();
}

template<typename FieldImp> void Record<FieldImp>::registerDataObject(const String &n,ScalarObject &o){
	EXCEPTION_SETUP("template<typename FieldImp> void Record<FieldImp>::registerDataObject(const String &n,ScalarObject &o)");
	_record[n].registerDataObject(o);
}

template<typename FieldImp> void Record<FieldImp>::registerDataObject(const String &n,ArrayObject &o){
	EXCEPTION_SETUP("template<typename FieldImp> void Record<FieldImp>::registerDataObject(const String &n,ArrayObject &o)");
	_record[n].registerDataObject(o);
}

template<typename FieldImp> void Record<FieldImp>::resetDataObject(const String &n){
	EXCEPTION_SETUP("template<typename FieldImp> void Record<FieldImp>::resetDataObject(const String &n)");
	_record[n].resetDataObject();
}

template<typename FieldImp> void Record<FieldImp>::erase(const String &n){
	EXCEPTION_SETUP("template<typename FieldImp> void Record<FieldImp>::erase(const String &n)");
	_record.erase(n);
}

template<typename FieldImp> void Record<FieldImp>::insert(FieldImp &f){
	EXCEPTION_SETUP("template<typename FieldImp> void Record<FieldImp>::insert(FieldImp &f)");
	_record[f.getName()] = f;
}

template<typename FieldImp> void Record<FieldImp>::write(){
	EXCEPTION_SETUP("template<typename Imp> void Record<Imp>::write()");

	RecordIterator iter;

	for(iter = _record.begin();iter != _record.end(); ++iter) iter->second.write();

}

template<typename FieldImp> void Record<FieldImp>::read(){
	EXCEPTION_SETUP("template<typename Imp> void Record<Imp>::read()");

	RecordIterator iter;
	for(iter = _record.begin();iter != _record.end(); ++iter) iter->second.write();
}

template<typename FieldImp> FieldImp &Record<FieldImp>::operator[](const String &k){
	EXCEPTION_SETUP("template<typename FieldImp> FieldImp &Record<FieldImp>::operator[](const String &k)");
	return _record[k];
}

template<typename FieldImp> FieldImp Record<FieldImp>::operator[](const String &k) const{
	EXCEPTION_SETUP("template<typename FieldImp> FieldImp Record<FieldImp>::operator[](const String &k) const");
	return _record[k];
}

} /* namespace nx */
} /* namespace pni */
#endif /* RECORD_HPP_ */

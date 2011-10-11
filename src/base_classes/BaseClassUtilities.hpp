/*
 * BaseClassUtilities.hpp
 *
 *  Created on: Sep 29, 2011
 *      Author: eugen
 */

#ifndef BASECLASSUTILITIES_HPP_
#define BASECLASSUTILITIES_HPP_

#include <pni/utils/PNITypes.hpp>
#include "../NXField.hpp"
#include "BaseClassExceptions.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{

template<typename Object> inline void setField(Object &obj,const String &n,const String &v){
	EXCEPTION_SETUP("template<typename Imp> void setField(Imp &obj,const String &n,const String &v)");
	NXField<typename Object::FImp> f;

	try{
		if(obj.exists(n)) obj.remove(n);

		f = obj.createField(n,v);
		f.write((String &)n);
		f.close();
	}catch(...){
		EXCEPTION_INIT(pni::nx::NXentryError,"Cannot write field ["+n+"]!");
		EXCEPTION_THROW();
	}
}


template<typename Object> inline void setField(Object &obj,const String &n,const ArrayObject &v){
	EXCEPTION_SETUP("template<typename Imp> void setField(Imp &obj, const String &n,const ArrayObject &v)");
	NXField<typename Object::FImp> f;

	try{
		if(obj.exists(n)) obj.remove(n);

		f = obj.createField(n,v);
		f.write(n);
		f.close();
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write field ["+n+"]!");
		EXCEPTION_THROW();
	}

}

template<typename Object> inline void setField(Object &obj,const String &n,const ScalarObject &v){
	EXCEPTION_SETUP("template<typename Imp> void setField(Imp &obj,const String &n,const ScalarObject &v)");
	NXField<typename Object::FImp> f;

	try{
		if(obj.exists(n)) obj.remove(n);

		f = obj.createField(n,v);
		f.write(n);
		f.close();
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write field ["+n+"]!");
		EXCEPTION_THROW();
	}

}

template<typename Object> inline void getField(Object &obj,const String &n,String &v){
	EXCEPTION_SETUP("template<typename Imp> void getField(Imp &obj,const String &n,String &v)");
	if(!obj.exists(n)){
		EXCEPTION_INIT(NXentryError,"Cannot open field ["+n+"]!");
		EXCEPTION_THROW();
	}

	NXField<typename Object::FImp> f;
	try{
		f = obj.openField(n);
		f.read(v);
		f.close();
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read data from field ["+n+"]!");
		EXCEPTION_THROW();
	}

}

template<typename Object> inline void getField(const Object &obj,const String &n,ArrayObject &v){
	EXCEPTION_SETUP("template<typename Imp> void getField(Imp &obj,const String &n,ArrayObject &v)");
	if(!obj.exists(n)){
		EXCEPTION_INIT(NXentryError,"Cannot open field ["+n+"]!");
		EXCEPTION_THROW();
	}

	NXField<typename Object::FImp> f;
	try{
		f = obj.openField(n);
		f.read(v);
		f.close();
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read data from field ["+n+"]!");
		EXCEPTION_THROW();
	}
}

template<typename Object> inline void getField(const Object &obj,const String &n,ScalarObject &v){
	EXCEPTION_SETUP("template<typename Imp> void getField(Imp &obj,const String &n,ScalarObject &v)");

	if(!obj.exists(n)){
		EXCEPTION_INIT(NXentryError,"Cannot open field ["+n+"]!");
		EXCEPTION_THROW();
	}

	NXField<typename Object::FImp> f;
	try{
		f = obj.openField(n);
		f.read(v);
		f.close();
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read data from field ["+n+"]!");
		EXCEPTION_THROW();
	}
}


}
}


#endif /* BASECLASSUTILITIES_HPP_ */

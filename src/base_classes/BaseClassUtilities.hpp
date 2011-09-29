/*
 * BaseClassUtilities.hpp
 *
 *  Created on: Sep 29, 2011
 *      Author: eugen
 */

#ifndef BASECLASSUTILITIES_HPP_
#define BASECLASSUTILITIES_HPP_

#include <pni/utils/PNITypes.hpp>
#include "BaseClassExceptions.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{



template<typename Imp> inline void setField(Imp &obj,const String &n,const String &v){
	EXCEPTION_SETUP("template<typename Imp> void setField(Imp &obj,const String &n,const String &v)");
	typename Imp::FImp f;

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


template<typename Imp> inline void setField(Imp &obj,const String &n,const ArrayObject &v){
	EXCEPTION_SETUP("template<typename Imp> void setField(Imp &obj, const String &n,const ArrayObject &v)");
	typename Imp::FImp f;

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

template<typename Imp> inline void setField(Imp &obj,const String &n,const ScalarObject &v){
	EXCEPTION_SETUP("template<typename Imp> void setField(Imp &obj,const String &n,const ScalarObject &v)");
	typename Imp::FImp f;

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

template<typename Imp> inline void getField(Imp &obj,const String &n,String &v) const{
	EXCEPTION_SETUP("template<typename Imp> void getField(Imp &obj,const String &n,String &v)");
	if(!obj.exists(n)){
		EXCEPTION_INIT(NXentryError,"Cannot open field ["+n+"]!");
		EXCEPTION_THROW();
	}

	typename Imp::FImp f;
	try{
		f = obj.openField(n);
		f.read(v);
		f.close();
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read data from field ["+n+"]!");
		EXCEPTION_THROW();
	}

}

template<typename Imp> inline void getField(Imp &obj,const String &n,ArrayObject &v) const{
	EXCEPTION_SETUP("template<typename Imp> void getField(Imp &obj,const String &n,ArrayObject &v)");
	if(!obj.exists(n)){
		EXCEPTION_INIT(NXentryError,"Cannot open field ["+n+"]!");
		EXCEPTION_THROW();
	}

	typename Imp::FImp f;
	try{
		f = obj.openField(n);
		f.read(v);
		f.close();
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read data from field ["+n+"]!");
		EXCEPTION_THROW();
	}
}

template<typename Imp> inline void getField(Imp &obj,const String &n,ScalarObject &v) const{
	EXCEPTION_SETUP("template<typename Imp> void getField(Imp &obj,const String &n,ScalarObject &v)");

	if(!obj.exists(n)){
		EXCEPTION_INIT(NXentryError,"Cannot open field ["+n+"]!");
		EXCEPTION_THROW();
	}

	typename Imp::FImp f;
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

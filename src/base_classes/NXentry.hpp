/*
 * NXentry.hpp
 *
 *  Created on: Sep 19, 2011
 *      Author: eugen
 */

#ifndef NXENTRY_HPP_
#define NXENTRY_HPP_

#include <pni/utils/PNITypes.hpp>

#include "BaseClassExceptions.hpp"
//#include "NXinstrument.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{


template<typename Imp> class NXentry:public Imp{
private:
	void _setField(const String &n,const String &v);
	void _setField(const String &n,const ArrayObject &v);
	void _setField(const String &n,const ScalarObject &v);

	void _getField(const String &n,String &v);
	void _getField(const String &n,ArrayObject &v);
	void _getField(const String &n,ScalarObject &v);

public:
	NXentry():Imp(){}
	virtual ~NXentry(){}

	virtual void setTitle(const String &n){
		_setField("title",n);
	}

	virtual String getTitle() const{
		String s;
		_getField("title",s);
		return s;
	}

};

template<typename Imp> void NXentry<Imp>::_setField(const String &n,const String &v){
	EXCEPTION_SETUP("template<typename Imp> void _setField(const String &n,const String &v)");
	typename Imp::FImp f;

	try{
		if(Imp::exists(n)){
			Imp::remove(n);
		}

		f = Imp::createField(n,v);
		f.write(n);
		f.close();
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write field ["+n+"]!");
		EXCEPTION_THROW();
	}
}


template<typename Imp> void NXentry<Imp>::_setField(const String &n,const ArrayObject &v){
	EXCEPTION_SETUP("template<typename Imp> void _setField(const String &n,const ArrayObject &v)");
	typename Imp::FImp f;

	try{
		if(Imp::exists(n)){
			Imp::remove(n);
		}

		f = Imp::createField(n,v);
		f.write(n);
		f.close();
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write field ["+n+"]!");
		EXCEPTION_THROW();
	}

}

template<typename Imp> void NXentry<Imp>::_setField(const String &n,const ScalarObject &v){
	EXCEPTION_SETUP("template<typename Imp> void _setField(const String &n,const ScalarObject &v)");
	typename Imp::FImp f;

	try{
		if(Imp::exists(n)){
			Imp::remove(n);
		}

		f = Imp::createField(n,v);
		f.write(n);
		f.close();
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write field ["+n+"]!");
		EXCEPTION_THROW();
	}

}

template<typename Imp> void NXentry<Imp>::_getField(const String &n,String &v){
	EXCEPTION_SETUP("template<typename Imp> void NXentry<Imp>::_getField(const String &n,String &v)");

}

template<typename Imp> void NXentry<Imp>::_getField(const String &n,ArrayObject &v){
	EXCEPTION_SETUP("template<typename Imp> void NXentry<Imp>::_getField(const String &n,ArrayObject &v)");

}

template<typename Imp> void NXentry<Imp>::_getField(const String &n,ScalarObject &v){
	EXCEPTION_SETUP("template<typename Imp> void NXentry<Imp>::_getField(const String &n,ScalarObject &v)");

}



//end of namespace
}
}


#endif /* NXENTRY_HPP_ */

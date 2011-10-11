/*
 * NXentry.hpp
 *
 *  Created on: Sep 19, 2011
 *      Author: eugen
 */

#ifndef NXENTRY_HPP_
#define NXENTRY_HPP_

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/Exceptions.hpp>

#include "../NXField.hpp"
#include "BaseClassExceptions.hpp"
#include "BaseClassUtilities.hpp"

using namespace pni::utils;



namespace pni{
namespace nx{


template<typename Base> class NXentry:public Base{
public:
	NXentry():Base(){}
	virtual ~NXentry(){}

	NXentry(const NXentry<Base> &o):Base(o){}


	virtual inline void setTitle(const String &n);
	virtual inline String getTitle() const;

	virtual String getExperimentIdentifier() const;
	virtual void setExperimentIdentifier(const String &n);

	virtual void setCollectionIdentifier(const String &n);
	virtual String getCollectionIdentifier() const;

	virtual void setCollectionDescription(const String &n);
	virtual String getCollectionDescription() const;

	virtual void setDefinition(const String &d,const String &v,const String &url);
	virtual String getDefinition() const;
	virtual String getDefinitionVersion();
	virtual String getDefinitionURL();

	/*
	virtual void setDefinitionLocal(const String &d,const String &v,const String &url);
	virtual String getDefinitionLocal() const;
	virtual String getDefinitionLocalVersion() const ;
	virtual String getDefinitionLocalURL() const;

	virtual void setStartTime(const String &n);
	virtual String getStartTime() const;

	virtual void setEndTime(const String &n);
	virtual String getEndTime() const;

	template<typename T> void setDuration(const Scalar<T> &);
	template<typename T> Scalar<T> getDuration() const;
	*/
};


//------------------------------------------------------------------------------
template<typename Base> void NXentry<Base>::setTitle(const String &n){
	EXCEPTION_SETUP("template<typename Imp> void NXentry<Imp>::setTitle(const String &n)");
	try{
		setField(*this,"title",n);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write title field for NXentry ["+Base::getName()+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Base> String NXentry<Base>::getTitle() const{
	EXCEPTION_SETUP("template<typename Imp> String NXentry<Imp>::getTitle() const");
	String s;
	try{
		getField((NXentry<Base> &)(*this),"title",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read title from NXentry ["+Base::getName()+"]");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Base> String NXentry<Base>::getExperimentIdentifier() const {
	EXCEPTION_SETUP("template<typename Imp> String NXentry<Imp>::getExperimentIdentifier() const");
	String s;
	try{
		getField((NXentry<Base> &)(*this),"experiment_identfier",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read experiment identifier from NXentry ["+Base::getName()+"]!");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Base> void NXentry<Base>::setExperimentIdentifier(const String &n){
	EXCEPTION_SETUP("template<typename Imp> void NXentry<Imp>::setExperimentIdentifier(const String &n)");
	try{
		setField(*this,"experiment_identifier",n);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write experiment identifier for NXentry ["+Base::getName()+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Base> void NXentry<Base>::setCollectionIdentifier(const String &n){
	EXCEPTION_SETUP("template<typename Imp> void NXentry<Imp>::setCollectionIdentifier(const String &n)");
	try{
		setField(*this,"collection_identifier",n);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write collection identifier for NXentry ["+Base::getName()+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Base> String NXentry<Base>::getCollectionIdentifier() const{
	EXCEPTION_SETUP("template<typename Imp> String NXentry<Imp>::getCollectionIdentifier() const");
	String s;
	try{
		getField((NXentry<Base> &)(*this),"collection_identifier",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read collection identifier for NXentry ["+Base::getName()+"]!");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Base> void NXentry<Base>::setCollectionDescription(const String &n){
	EXCEPTION_SETUP("template<typename Imp> void NXentry<Imp>::setCollectionDescription(const String &n)");
	try{
		setField(*this,"collection_description",n);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write collection description for NXentry ["+Base::getName()+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Base> String NXentry<Base>::getCollectionDescription() const{
	EXCEPTION_SETUP("template<typename Imp> String NXentry<Imp>::getCollectionDescription() const");
	String s;
	try{
		getField((NXentry<Base> &)(*this),"collection_description",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read collection description for NXentry  ["+Base::getName()+"]!");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Base> void NXentry<Base>::setDefinition(const String &d,const String &v,const String &url){
	EXCEPTION_SETUP("template<typename Imp> void NXentry<Imp>::setDefinition(const String &d,const String &v,const String &url)");
	try{
		setField(*this,"definition",d);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write definition for NXentry ["+Base::getName()+"]!");
		EXCEPTION_THROW();
	}

	NXField<typename Base::FImp> f;
	f = Base::openField("definition");
	try{
		f.setAttribute("version",v);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write version attribute the definition of NXentry ["+Base::getName()+"]!");
		EXCEPTION_THROW();
	}
	try{
		f.setAttribute("URL",url);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write URL attribute of the definition of NXentry ["+Base::getName()+"]!");
		EXCEPTION_THROW();
	}

	f.close();
}

//------------------------------------------------------------------------------
template<typename Base> String NXentry<Base>::getDefinition() const {
	EXCEPTION_SETUP("template<typename Imp> String NXentry<Imp>::getDefinition() const ");
	String s;
	try{
		getField((NXentry<Base> &)(*this),"definition",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read definition of NXentry ["+Base::getName()+"]!");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Base> String NXentry<Base>::getDefinitionVersion(){
	EXCEPTION_SETUP("String NXentry<Imp>::getDefinitionVersion() const");
	NXField<typename Base::FImp> f;
	String s;
	try{
		f = Base::openField("definition");
		f.getAttribute("version",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot retrieve the version of the NXDL definition of NXentry ["+Base::getName()+"!");
		EXCEPTION_THROW();
	}

	return s;
}

//------------------------------------------------------------------------------
template<typename Base> String NXentry<Base>::getDefinitionURL(){
	EXCEPTION_SETUP("template<typename Imp> String NXentry<Imp>::getDefinitionURL() const");
	NXField<typename Base::FImp> f;
	String s;

	try{
		f = Base::openField("definition");
		f.getAttribute("URL",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot retrieve the URL of the NXDL definition of NXentry ["+Base::getName()+"]!");
		EXCEPTION_THROW();
	}

	return s;
}



//end of namespace
}
}


#endif /* NXENTRY_HPP_ */

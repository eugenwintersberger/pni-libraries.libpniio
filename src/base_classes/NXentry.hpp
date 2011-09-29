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
#include "BaseClassUtilities.hpp"

using namespace pni::utils;



namespace pni{
namespace nx{


template<typename Imp> class NXentry:public Imp{
public:
	NXentry():Imp(){}
	virtual ~NXentry(){}

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
	virtual String getDefinitionVersion() const;
	virtual String getDefinitionURL() const;

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

};

//------------------------------------------------------------------------------
template<typename Imp> void NXentry<Imp>::setTitle(const String &n){
	EXCEPTION_SETUP("template<typename Imp> void NXentry<Imp>::setTitle(const String &n)");
	try{
		setField(*this,"title",n);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write title field for NXentry ["+Imp::getName()+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Imp> String NXentry<Imp>::getTitle() const{
	EXCEPTION_SETUP("template<typename Imp> String NXentry<Imp>::getTitle() const");
	String s;
	try{
		getField(*this,"title",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read title from NXentry ["+Imp::getName()+"]");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Imp> String NXentry<Imp>::getExperimentIdentifier() const {
	EXCEPTION_SETUP("template<typename Imp> String NXentry<Imp>::getExperimentIdentifier() const");
	String s;
	try{
		getField(*this,"experiment_identfier",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read experiment identifier from NXentry ["+Imp::getName()+"]!");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Imp> void NXentry<Imp>::setExperimentIdentifier(const String &n){
	EXCEPTION_SETUP("template<typename Imp> void NXentry<Imp>::setExperimentIdentifier(const String &n)");
	try{
		setField(*this,"experiment_identifier",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write experiment identifier for NXentry ["+Imp::getName()+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Imp> void NXentry<Imp>::setCollectionIdentifier(const String &n){
	EXCEPTION_SETUP("template<typename Imp> void NXentry<Imp>::setCollectionIdentifier(const String &n)");
	try{
		setField(*this,"collection_identifier",n);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write collection identifier for NXentry ["+Imp::getName()+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Imp> String NXentry<Imp>::getCollectionIdentifier() const{
	EXCEPTION_SETUP("template<typename Imp> String NXentry<Imp>::getCollectionIdentifier() const");
	String s;
	try{
		getField(*this,"collection_identifier",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read collection identifier for NXentry ["+Imp::getName()+"]!");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Imp> void NXentry<Imp>::setCollectionDescription(const String &n){
	EXCEPTION_SETUP("template<typename Imp> void NXentry<Imp>::setCollectionDescription(const String &n)");
	try{
		setField(*this,"collection_description",n);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write collection description for NXentry ["+Imp::getName()+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Imp> String NXentry<Imp>::getCollectionDescription() const{
	EXCEPTION_SETUP("template<typename Imp> String NXentry<Imp>::getCollectionDescription() const");
	String s;
	try{
		getField(*this,"collection_description",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read collection description for NXentry  ["+Imp::getName()+"]!");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Imp> void NXentry<Imp>::setDefinition(const String &d,const String &v,const String &url){
	EXCEPTION_SETUP("template<typename Imp> void NXentry<Imp>::setDefinition(const String &d,const String &v,const String &url)");
	try{
		setField(*this,"definition",d);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write definition for NXentry ["+Imp::getName()+"]!");
		EXCEPTION_THROW();
	}

	typename imp::FImp f;
	f = openField("definition");
	try{
		f.setAttribute("version",v);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write version attribute the definition of NXentry ["+Imp::getName()+"]!");
		EXCEPTION_THROW();
	}
	try{
		f.setAttribute("URL",url);
	}catch(...){
		EXCEPTION_INIT(NXentryError;"Cannot write URL attribute of the definition of NXentry ["+Imp::getName()+"]!");
		EXCEPTION_THROW();
	}

	f.close();
}

//------------------------------------------------------------------------------
template<typename Imp> String NXentry<Imp>::getDefinition() const {
	EXCEPTION_SETUP("template<typename Imp> String NXentry<Imp>::getDefinition() const ");
	String s;
	try{
		getField(*this,"definition",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read definition of NXentry ["+Imp::getName()+"]!");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Imp> String NXentry<Imp>::getDefinitionVersion() const {
	EXCEPTION_SETUP("String NXentry<Imp>::getDefinitionVersion() const");
	typename Imp::FImp f;
	String s;
	try{
		f = Imp::openField("definition");
		s = f.getAttribute("version");
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot retrieve the version of the NXDL definition of NXentry ["+Imp::getName()+"!");
		EXCEPTION_TRHOW();
	}

	return s;
}

//------------------------------------------------------------------------------
template<typename Imp> String NXentry<Imp>::getDefinitionURL() const {
	EXCEPTION_SETUP("template<typename Imp> String NXentry<Imp>::getDefinitionURL() const");
	typename Imp::FImp f;
	String s;

	try{
		f = Imp::openField("definition");
		s = f.getAttribute("URL");
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot retrieve the URL of the NXDL definition of NXentry ["+Imp::getName()+"]!");
		EXCEPTION_THROW();
	}

	return s;
}



//end of namespace
}
}


#endif /* NXENTRY_HPP_ */

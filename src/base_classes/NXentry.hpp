/*
 * Declaration of Nexus base class NXentry template.
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Declaration of Nexus base class NXentry template.
 *
 * Created on: Sep 19, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXENTRY_HPP_
#define NXENTRY_HPP_

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/Exceptions.hpp>

#include "../NXField.hpp"
#include "BaseClassExceptions.hpp"
#include "BaseClassUtilities.hpp"

#include "NXnote.hpp"

using namespace pni::utils;



namespace pni{
namespace nx{


template<typename Base> class NXentry:public Base{

public:
	NXentry():Base(){}
	virtual ~NXentry(){}

	NXentry(const NXentry<Base> &o):Base(o){}
	NXentry(const Base &o):Base(o){}


	virtual typename Base::FieldType title() const;

	virtual typename Base::FieldType experiment_identifier() const;
	virtual typename Base::FieldType experiment_description() const;
	virtual typename Base::FieldType entry_identifier() const;
	virtual typename Base::FieldType collection_identifier() const;
	virtual typename Base::FieldType collection_description() const;

	virtual typename Base::FieldType definition(const String &version,const String &url) const;
	virtual typename Base::FieldType definition() const;


	virtual inline void definition_local(const String &d,const String &v,const String &url) const;
	virtual inline String definition_local() const;
	virtual inline String definition_local_version() const ;
	virtual inline String definition_local_url() const;

	virtual inline void start_time(const String &n) const;
	virtual inline String start_time() const;

	virtual inline void end_time(const String &n) const;
	virtual inline String end_time() const;

	template<typename T> void duration(const Scalar<T> &) const;
	template<typename T> Scalar<T> duration() const;

	template<typename T> void collection_time(const Scalar<T> &) const;
	template<typename T> Scalar<T> collection_time() const;

	virtual inline void run_cycle(const String &n) const;
	virtual inline String run_cycle() const;

	virtual inline void program_name(const String &n,const String &v,const String &conf) const;
	virtual inline String program_name() const;
	virtual inline String program_name_version() const;
	virtual inline String program_name_configuration() const;

	virtual inline void revision(const String &rev,const String &comment) const;
	virtual inline String revision() const;
	virtual inline String revision_comment() const;

	template<typename T> void pre_sample_flightpath(const Scalar<T> &s) const;
	template<typename T> Scalar<T> pre_sample_flightpath() const;

	//here we need a couple of creator functions for a bunch of Nexus classes
};


//------------------------------------------------------------------------------
template<typename Base>
typename Base::FieldType
NXentry<Base>::title() const{
	EXCEPTION_SETUP("template<typename Base> typename Base::FieldType "
					"NXentry<Base>::title() const");

	typename Base::FieldType field;

	if(Base::exists("title")){
		field = Base::openField("title");
	}else{
		field = Base::createStringField("title");
	}

	return field;

}


//------------------------------------------------------------------------------
template<typename Base>
typename Base::FieldType
NXentry<Base>::experiment_identifier() const {
	EXCEPTION_SETUP("template<typename Base> typename Base::FieldType "
					"NXentry<Base>::experiment_identifier() const");
	typename Base::FieldType field;

	if(Base::exists("experiment_identifier")){
		field = Base::openField("experiment_identifier");
	}else{
		field = Base::createStringField("experiment_identifier");
	}

	return field;
}

//------------------------------------------------------------------------------
template<typename Base>
typename Base::FieldType
NXentry<Base>::experiment_description() const {
	EXCEPTION_SETUP("template<typename Base> typename Base::FieldType "
					"NXentry<Base>::experiment_description() const");
	typename Base::FieldType field;

	if(Base::exists("experiment_description")){
		field = Base::openField("experiment_description");
	}else{
		field = Base::createStringField("experiment_description");
	}

	return field;
}



//------------------------------------------------------------------------------
template<typename Base>
typename Base::FieldType
NXentry<Base>::entry_identifier() const {
	EXCEPTION_SETUP("template<typename Base> typename Base::FieldType "
					"NXentry<Base>::entry_identifier() const");

	typename Base::FieldType field;

	if(Base::exists("entry_identifier")){
		field = Base::openField("entry_identifier");
	}else{
		field = Base::createStringField("entry_identifier");
	}

	return field;

}


//------------------------------------------------------------------------------
template<typename Base>
typename Base::FieldType
NXentry<Base>::collection_identifier() const{
	EXCEPTION_SETUP("template<typename Base> typename Base::FieldType "
					"NXentry<Base>::collection_identifier() const");

	typename Base::FieldType field;

	if(Base::exists("collection_identifier")){
		field = Base::openField("collection_identifier");
	}else{
		field = Base::createStringField("collection_identifier");
	}

	return field;

}

//------------------------------------------------------------------------------
template<typename Base> typename Base::FieldType NXentry<Base>::collection_description() const{
	EXCEPTION_SETUP("template<typename Imp> String NXentry<Imp>::getCollectionDescription() const");
	String s;
	try{
		getField((NXentry<Base> &)(*this),"collection_description",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read collection description for NXentry  ["+Base::getName()+"]!");
		EXCEPTION_THROW();
	}
	typename Base::FieldType field;
	return field;
}

//------------------------------------------------------------------------------
template<typename Base>
typename Base::FieldType
NXentry<Base>::definition(const String &version,const String &url) const{
	EXCEPTION_SETUP("template<typename Base> typename Base::FieldType"
					" NXentry<Base>::definition("
					"const String &v,const String &url) const");

	typename Base::FieldType field;
	if(Base::exists("definition")){
		field = Base::openField("definition");
	}else{
		field = Base::createStringField("definition");
		field.setAttribute("version",version);
		field.setAttribute("url",url);
	}

	return field;
}

//------------------------------------------------------------------------------
template<typename Base>
typename Base::FieldType
NXentry<Base>::definition() const{
	EXCEPTION_SETUP("template<typename Base> typename Base::FieldType"
					" NXentry<Base>::definition() const");

	typename Base::FieldType field;
	if(Base::exists("definition")){
		field = Base::openField("definition");
	}else{
		//raise an exception here
	}

	return field;
}


//------------------------------------------------------------------------------
template<typename Base> void NXentry<Base>::definition_local(const String &d,const String &v,const String &url) const{
	EXCEPTION_SETUP("template<typename Base> void NXentry<Base>::definition_local(const String &d,const String &v,const String &url) const");
	try{
		setField(*this,"definition_local",d);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write definition for NXentry ["+Base::getName()+"]!");
		EXCEPTION_THROW();
	}

	NXField<typename Base::FImp> f;
	f = Base::openField("definition_local");
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
template<typename Base> String NXentry<Base>::definition_local() const {
	EXCEPTION_SETUP("template<typename Base> String NXentry<Base>::definition_local() const");
	String s;
	try{
		getField((NXentry<Base> &)(*this),"definition_local",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read definition of NXentry ["+Base::getName()+"]!");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Base> String NXentry<Base>::definition_local_version() const{
	EXCEPTION_SETUP("template<typename Base> String NXentry<Base>::definition_local_version() const");
	NXField<typename Base::FImp> f;
	String s;
	try{
		f = Base::openField("definition_local");
		f.getAttribute("version",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot retrieve the version of the NXDL definition of NXentry ["+Base::getName()+"!");
		EXCEPTION_THROW();
	}

	return s;
}

//------------------------------------------------------------------------------
template<typename Base> String NXentry<Base>::definition_local_url() const{
	EXCEPTION_SETUP("template<typename Base> String NXentry<Base>::definition_local_url() const");
	NXField<typename Base::FImp> f;
	String s;

	try{
		f = Base::openField("definition_local");
		f.getAttribute("URL",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot retrieve the URL of the NXDL definition of NXentry ["+Base::getName()+"]!");
		EXCEPTION_THROW();
	}

	return s;
}

//------------------------------------------------------------------------------
template<typename Base> void NXentry<Base>::start_time(const String &n) const{
	EXCEPTION_SETUP("template<typename Base> void NXentry<Base>::start_time(const String &n) const");
	try{
		setField(*this,"start_time",n);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot set start_time field!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Base> String NXentry<Base>::start_time() const {
	EXCEPTION_SETUP("template<typename Base> String NXentry<Base>::start_time() const ");
	String s;
	try{
		getField(*this,"start_time",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read start_time field!");
		EXCEPTION_THROW();
	}

	return s;
}

//------------------------------------------------------------------------------
template<typename Base> void NXentry<Base>::end_time(const String &n) const{
	EXCEPTION_SETUP("template<typename Base> void NXentry<Base>::end_time(const String &n) const");

	try{
		setField(*this,"end_time",n);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot set end_time field!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
template<typename Base> String NXentry<Base>::end_time() const{
	EXCEPTION_SETUP("template<typename Base> String NXentry<Base>::end_time() const");
	String s;

	try{
		getField(*this,"end_time",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read end_time field!");
		EXCEPTION_THROW();
	}

	return s;
}
//------------------------------------------------------------------------------
template<typename Base>
template<typename T> void NXentry<Base>::duration(const Scalar<T> &s) const{
	EXCEPTION_SETUP("template<typename Base> template<typename T> void NXentry<Base>::duration(const Scalar<T> &) const");
	try{
		setField(*this,"duration",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot set field duration!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Base>
template<typename T> Scalar<T> NXentry<Base>::duration() const{
	EXCEPTION_SETUP("template<typename Base> template<typename T> Scalar<T> NXentry<Base>::duration() const");
	Scalar<T> s;
	try{
		getField(*this,"duration",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read field duration!");
		EXCEPTION_THROW();
	}

	return s;
}

//------------------------------------------------------------------------------
template<typename Base>
template<typename T> void NXentry<Base>::collection_time(const Scalar<T> &s) const{
	EXCEPTION_SETUP("template<typename Base> template<typename T> void NXentry<Base>::collection_time(const Scalar<T> &s) const");
	try{
		setField(*this,"collection_time",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot set field duration!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Base>
template<typename T> Scalar<T> NXentry<Base>::collection_time() const{
	EXCEPTION_SETUP("template<typename Base> template<typename T> Scalar<T> NXentry<Base>::collection_time() const");
	Scalar<T> s;
	try{
		getField(*this,"collection_time",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read field duration!");
		EXCEPTION_THROW();
	}

	return s;
}

//------------------------------------------------------------------------------
template<typename Base> void NXentry<Base>::run_cycle(const String &n) const{
	EXCEPTION_SETUP("template<typename Base> void NXentry<Base>::run_cycle(const String &n) const");
	try{
		setField(*this,"run_cycle",n);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write field [run_cylce]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Base> String NXentry<Base>::run_cycle() const{
	EXCEPTION_SETUP("template<typename Base> String NXentry<Base>::run_cycle() const");
	String s;

	try{
		getField(*this,"run_cycle",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read field [run_cycle]!");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Base>
void NXentry<Base>::program_name(const String &n,const String &v,const String &conf) const{
	EXCEPTION_SETUP("template<typename Base> void NXentry<Base>::program_name(const String &n,const String &v,const String &conf) const");

	try{
		setField(*this,"program_name",n);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot set field [program_name]!");
		EXCEPTION_THROW();
	}

	NXField<typename Base::FImp> field;
	try{
		field = Base::openField("program_name");
		field.setAttribute("version",v);
		field.setAttribute("configuration",conf);
		field.close();
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot set attributes to field [program_name]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Base> String NXentry<Base>::program_name() const{
	EXCEPTION_SETUP("template<typename Base> String NXentry<Base>::program_name() const");
	String s;

	try{
		getField(*this,"program_name",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read field [program_name]!");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Base> String NXentry<Base>::program_name_version() const{
	EXCEPTION_SETUP("template<typename Base> String NXentry<Base>::program_name_version() const");
	String s;

	NXField<typename Base::FImp> field;
	try{
		field = Base::openField("program_name");
		field.getAttribute("version",s);
		field.close();
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read attribute [version] from field [program_field]!");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Base> String NXentry<Base>::program_name_configuration() const{
	EXCEPTION_SETUP("template<typename Base> String NXentry<Base>::program_name_configuration() const");
	String s;

	NXField<typename Base::FImp> field;
	try{
		field = Base::openField("program_name");
		field.getAttribute("configuration",s);
		field.close();
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read attribute [configuration] from field [program_name]!");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Base> void NXentry<Base>::revision(const String &rev,const String &comment) const{
	EXCEPTION_SETUP("template<typename Base> void NXentry<Base>::revision(const String &rev,const String &comment) const");

	try{
		setField(*this,"revision",rev);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write field [revision]!");
		EXCEPTION_THROW();
	}

	NXField<typename Base::FImp> field;
	try{
		field = Base::openField("revision");
		field.setAttribute("comment",comment);
		field.close();
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write attribute [comment] of field [revision]!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
template<typename Base> String NXentry<Base>::revision() const {
	EXCEPTION_SETUP("template<typename Base> String NXentry<Base>::revision() const");
	String s;

	try{
		getField(*this,"revision",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read field [revision]!");
		EXCEPTION_THROW();
	}

	return s;
}

//------------------------------------------------------------------------------
template<typename Base> String NXentry<Base>::revision_comment() const{
	EXCEPTION_SETUP("template<typename Base> String NXentry<Base>::revision_comment() const");
	String s;
	NXField<typename Base::FImp> field;

	try{
		field = Base::openField("revision");
		field.getAttribute("comment",s);
		field.close();
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot read attribute [comment] from field [revision]!");
		EXCEPTION_THROW();
	}

	return s;
}

//------------------------------------------------------------------------------
template<typename Base>
template<typename T> void NXentry<Base>::pre_sample_flightpath(const Scalar<T> &s) const{
	EXCEPTION_SETUP("template<typename Base> template<typename T> void NXentry<Base>::pre_sample_flightpath(const Scalar<T> &s) const");

	//here a unit check is missing

	try{
		setField(*this,"pre_sample_flightpath",s);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Cannot write field [pre_sample_flightpath]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Base>
template<typename T> Scalar<T> NXentry<Base>::pre_sample_flightpath() const{
	EXCEPTION_SETUP("template<typename Base> template<typename T> Scalar<T> NXentry<Base>::pre_sample_flightpath() const");
	Scalar<T> data;

	try{
		getField(*this,"pre_sample_flightpath",data);
	}catch(...){
		EXCEPTION_INIT(NXentryError,"Canot read field [pre_sample_flightpath]!");
		EXCEPTION_THROW();
	}
	return data;
}

//end of namespace
}
}


#endif /* NXENTRY_HPP_ */

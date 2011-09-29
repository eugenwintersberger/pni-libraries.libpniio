/*
 * NXnote.hpp
 *
 *  Created on: Sep 29, 2011
 *      Author: eugen
 */

#include <pni/utils/PNITypes.hpp>

#include "BaseClassExceptions.hpp"
#include "BaseClassUtilities.hpp"

using namespace pni::utils;

#ifndef NXNOTE_HPP_
#define NXNOTE_HPP_

namespace pni{
namespace nx{

template<typename Imp> class NXnote:private Imp{
public:
	NXnote():Imp(){}
	virtual ~NXnote(){}

	virtual inline void setAuthor(const String &n);
	virtual inline String getAuthor() const;

	virtual inline void setDate(const String &n);
	virtual inline String getDate() const;

	virtual inline void setType(const String &n);
	virtual inline String getType(const String &n);

	virtual inline void setFileName(const String &n);
	virtual inline String getFileName() const;

	virtual inline void setDescription(const String &n);
	virtual inline String getDescription() const;

	virtual inline void setData();
	virtual inline void getData() const;

};

//------------------------------------------------------------------------------
template<typename Imp> void NXnote<Imp>::setAuthor(const String &n){
	EXCEPTION_SETUP("template<typename Imp> void NXnote<Imp>::setAuthor(const String &n)");
	try{
		setField(*this,"author",n);
	}catch(...){
		EXCEPTION_INIT(NXnoteError,"Cannot write author to note!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Imp> inline String NXnote<Imp>::getAuthor() const{
	EXCEPTION_SETUP("template<typename Imp> inline String NXnote<Imp>::getAuthor() const");
	String s;
	try{
		getField(*this,"author",s);
	}catch(...){
		EXCEPTION_INIT(NXnoteError,"Cannot read author from note!");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Imp> inline void NXnote<Imp>::setDate(const String &n){
	EXCEPTION_SETUP("template<typename Imp> inline void NXnote<Imp>::setDate(const String &n)");
	//here we should check the date format

	try{
		setField(*this,"date",n);
	}catch(...){
		EXCEPTION_INIT(NXnoteError,"Cannot write date to note!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Imp> inline String NXnote<Imp>::getDate() const{
	EXCEPTION_SETUP("template<typename Imp> inline String NXnote<Imp>::getDate() const");
	String s;

	try{
		getField(*this,"date",s);
	}catch(...){
		EXCEPTION_INIT(NXnoteError,"Canot read date from note!");
		EXCEPTION_THROW();
	}

	return s;
}

//------------------------------------------------------------------------------
template<typename Imp> inline void NXnote<Imp>::setType(const String &n){
	EXCEPTION_SETUP("template<typename Imp> inline void NXnote<Imp>::setType(const String &n)");
	//here we should check if n is a valid mime type

	try{
		setField(*this,"type",n);
	}catch(...){
		EXCEPTION_INIT(NXnoteError,"Cannot write MIME-type to note!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Imp> inline String NXnote<Imp>::getType(const String &n){
	EXCEPTION_SETUP("template<typename Imp> inline void NXnote<Imp>::getType(const String &n)");
	String s;

	try{
		getField(*this,"type",s);
	}catch(...){
		EXCEPTION_INIT(NXnoteError,"Cannot read MIME-type from note!");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Imp> inline void NXnote<Imp>::setFileName(const String &n){
	EXCEPTION_SETUP("template<typename Imp> inline void NXnote<Imp>::setFileName(const String &n)");

	try{
		setField(*this,"file_name",n);
	}catch(...){
		EXCEPTION_INIT(NXnoteError,"Cannot write file name to note!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Imp> inline String NXnote<Imp>::getFileName() const{
	EXCEPTION_SETUP("template<typename Imp> inline String NXnote<Imp>::getFileName() const");
	String s;

	try{
		getField(*this,"file_name",s);
	}catch(...){
		EXCEPTION_INIT(NXnoteError,"Cannot read file name from note!");
		EXCEPTION_THROW();
	}

	return s;
}

//------------------------------------------------------------------------------
template<typename Imp> inline void NXnote<Imp>::setDescription(const String &n){
	EXCEPTION_SETUP("template<typename Imp> inline void NXnote<Imp>::setDescription(const String &n)");
	try{
		setField(*this,"description",n);
	}catch(...){
		EXCEPTION_INIT(NXnoteError,"Cannot write description to note!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
template<typename Imp> inline String NXnote<Imp>::getDescription() const{
	EXCEPTION_SETUP("template<typename Imp> inline String NXnote<Imp>::getDescription() const");
	String s;

	try{
		getField(*this,"description",s);
	}catch(...){
		EXCEPTION_INIT(NXnoteError,"Cannot read description from note!");
		EXCEPTION_THROW();
	}
	return s;
}

//------------------------------------------------------------------------------
template<typename Imp> inline void NXnote<Imp>::setData(){

}

//------------------------------------------------------------------------------
template<typename Imp> inline void NXnote<Imp>::getData() const{

}

}
}


#endif /* NXNOTE_HPP_ */

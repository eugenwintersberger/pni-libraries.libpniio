/*
 * Declaration of Nexus base class NXnote template
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
 * Declaration of Nexus base class NXnote template
 *
 * Created on: Sep 29, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <pni/utils/PNITypes.hpp>

#include "BaseClassExceptions.hpp"
#include "BaseClassUtilities.hpp"

using namespace pni::utils;

#ifndef NXNOTE_HPP_
#define NXNOTE_HPP_

namespace pni{
namespace nx{

template<typename Base> class NXnote:private Base{
public:
	NXnote():Base(){}
	virtual ~NXnote(){}

	virtual inline void author(const String &n) const;
	virtual inline String author() const;

	virtual inline void date(const String &n) const;
	virtual inline String date() const;

	virtual inline void type(const String &n) const;
	virtual inline String type() const;

	virtual inline void file_name(const String &n) const;
	virtual inline String file_name() const;

	virtual inline void description(const String &n) const;
	virtual inline String description() const;

	virtual inline void data(const String &s) const;
	virtual inline void data(String &s) const;

};

//------------------------------------------------------------------------------
template<typename Base> void NXnote<Base>::author(const String &n) const{
	EXCEPTION_SETUP("template<typename Imp> void NXnote<Imp>::author(const String &n) const");
	try{
		setField(*this,"author",n);
	}catch(...){
		EXCEPTION_INIT(NXnoteError,"Cannot write author to note!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Base> inline String NXnote<Base>::author() const{
	EXCEPTION_SETUP("template<typename Imp> inline String NXnote<Imp>::author() const");
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
template<typename Base> inline void NXnote<Base>::date(const String &n) const{
	EXCEPTION_SETUP("template<typename Imp> inline void NXnote<Imp>::date(const String &n) const");
	//here we should check the date format

	try{
		setField(*this,"date",n);
	}catch(...){
		EXCEPTION_INIT(NXnoteError,"Cannot write date to note!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Base> inline String NXnote<Base>::date() const{
	EXCEPTION_SETUP("template<typename Imp> inline String NXnote<Imp>::date() const");
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
template<typename Base> inline void NXnote<Base>::type(const String &n) const{
	EXCEPTION_SETUP("template<typename Imp> inline void NXnote<Imp>::type(const String &n) const");
	//here we should check if n is a valid mime type

	try{
		setField(*this,"type",n);
	}catch(...){
		EXCEPTION_INIT(NXnoteError,"Cannot write MIME-type to note!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Base> inline String NXnote<Base>::type() const{
	EXCEPTION_SETUP("template<typename Imp> inline void NXnote<Imp>::type(const String &n) const");
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
template<typename Base> inline void NXnote<Base>::file_name(const String &n) const{
	EXCEPTION_SETUP("template<typename Imp> inline void NXnote<Imp>::file_name(const String &n) const");

	try{
		setField(*this,"file_name",n);
	}catch(...){
		EXCEPTION_INIT(NXnoteError,"Cannot write file name to note!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename Base> inline String NXnote<Base>::file_name() const{
	EXCEPTION_SETUP("template<typename Imp> inline String NXnote<Imp>::file_name() const");
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
template<typename Base> inline void NXnote<Base>::description(const String &n) const{
	EXCEPTION_SETUP("template<typename Imp> inline void NXnote<Imp>::description(const String &n) const");
	try{
		setField(*this,"description",n);
	}catch(...){
		EXCEPTION_INIT(NXnoteError,"Cannot write description to note!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
template<typename Base> inline String NXnote<Base>::description() const{
	EXCEPTION_SETUP("template<typename Imp> inline String NXnote<Imp>::description() const");
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
template<typename Base> inline void NXnote<Base>::data(const String &s) const{
	EXCEPTION_SETUP("template<typename Base> inline void NXnote<Base>::data(const String &s) const");

}

//------------------------------------------------------------------------------
template<typename Base> inline void NXnote<Base>::data(String &s) const{
	EXCEPTION_SETUP("template<typename Base> inline void NXnote<Base>::data(String &s) const");
}

}
}


#endif /* NXNOTE_HPP_ */

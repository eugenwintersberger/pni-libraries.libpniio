/*
 * Declaration of Nexus base class NXroot template
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
 * Declaration of Nexus base class NXroot template
 *
 * Created on: Sep 13, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXROOT_HPP_
#define NXROOT_HPP_

#include "../NXFile.hpp"
#include "../NXGroup.hpp"
#include "../NXExceptions.hpp"
#include "BaseClassExceptions.hpp"
#include "NXStandardGroup.hpp"
#include "NXentry.hpp"
#include <ctime>

namespace pni{
namespace nx{


template<typename Base> class NXroot:private Base{
private:
	NXroot(const NXroot<Base> &):Base(){};
	NXroot<Base> &operator=(const NXroot<Base> &o){ return *this;}
public:
	NXroot():Base(){}
	virtual ~NXroot(){close();}

	virtual void setFileName(const String &n){
		Base::setFileName(n);
	}

	virtual String getFileName() const {
		return Base::getFileName();
	}

	virtual void setOverwrite(const bool &v){
		Base::setOverwrite(v);
	}

	virtual void setReadOnly(const bool &v){
		Base::setReadOnly(v);
	}

	virtual void create(){
		EXCEPTION_SETUP("template<typename Imp> NXroot<Imp>::create()");

		try{
			Base::create();

			//have to set here some default attributes
			Base::setAttribute("NX_class","NXroot");
			Base::setAttribute("NeXus_version","4.2.3"); //this needs to be fixed
			Base::setAttribute("HDF5_version","1.8.7");  //this needs to be fixed
			Base::setAttribute("creator","DESY");        //this needs configuration

			//have to set the time
			std::time_t time;
			std::time(&time);
			String tstr = String(std::ctime(&time));

			Base::setAttribute("file_time",tstr);
			Base::setAttribute("file_update_time",tstr);

		}catch(...){
			EXCEPTION_INIT(NXrootError,"Creation of root object ["+getFileName()+"] failed!");
			EXCEPTION_THROW();
		}

	}
	virtual void open(){
		EXCEPTION_SETUP("template<typename Imp> NXroot<Imp>::open()");

		try{
			Base::open();

			if(!Base::isReadOnly()){
				//if the file is not read only we have to adopt an attribute
				std::time_t time;
				std::time(&time);
				String tstr = std::ctime(&time);
				Base::setAttribute("file_update_time",tstr);
			}

		}catch(...){
			EXCEPTION_INIT(NXrootError,"Opening of root object ["+getFileName()+"] failed!");
			EXCEPTION_THROW();
		}
	}

	virtual void close(){
		Base::close();
	}

	virtual String getFileTime(){
		String s;
		Base::getAttribute("file_time",s);
		return s;
	}

	virtual String getFileUpdateTime(){
		String s;
		Base::getAttribute("file_update_time",s);
		return s;
	}


	NXentry<NXStandardGroup<NXGroup<typename Base::GImp> > > createEntry(const String &n) const{
		EXCEPTION_SETUP("NXentry<NXGroup<typename Base::GImp> > createEntry(const String &n)");
		NXentry<NXStandardGroup<NXGroup<typename Base::GImp> > > e;

		try{
			e = static_cast<NXentry<NXStandardGroup<NXGroup<typename Base::GImp> > > >(Base::createGroup(n));
			e.setAttribute("NX_class","NXentry");
		}catch(...){
			EXCEPTION_INIT(NXrootError,"Cannot create entry ["+n+"]!");
			EXCEPTION_THROW();
		}

		return e;
	}

	NXentry<NXStandardGroup<NXGroup<typename Base::GImp> > > openEntry(const String &n) const{
		EXCEPTION_SETUP("NXentry<NXGroup<typename Base::GImp> > openEntry(const String &n)");
		NXentry<NXStandardGroup<NXGroup<typename Base::GImp> > > e;

		try{
			e = static_cast<NXentry<NXStandardGroup<NXGroup<typename Base::GImp> > > >(Base::openGroup(n));
		}catch(...){
			EXCEPTION_INIT(NXentryError,"Cannot open entry ["+n+"]!");
			EXCEPTION_THROW();
		}

		return e;
	}


};

//end of namespace
}
}



#endif /* NXROOT_HPP_ */

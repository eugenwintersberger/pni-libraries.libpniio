/*
 * NXroot.hpp
 *
 *  Created on: Sep 23, 2011
 *      Author: eugen
 */

#ifndef NXROOT_HPP_
#define NXROOT_HPP_

#include "../NXFile.hpp"
#include "../NXExceptions.hpp"
#include "BaseClassExceptions.hpp"
#include "NXentry.hpp"
#include <ctime>

namespace pni{
namespace nx{


template<typename Imp> class NXroot:private Imp{
private:
	NXroot(const NXroot<Imp> &):Imp(){};
	NXroot<Imp> &operator=(const NXroot<Imp> &o){ return *this;}
public:
	NXroot():Imp(){}
	virtual ~NXroot(){close();}

	virtual void setFileName(const String &n){
		Imp::setFileName(n);
	}

	virtual String getFileName() const {
		return Imp::getFileName();
	}

	virtual void setOverwrite(const bool &v){
		Imp::setOverwrite(v);
	}

	virtual void setReadOnly(const bool &v){
		Imp::setReadOnly(v);
	}

	virtual void create(){
		EXCEPTION_SETUP("template<typename Imp> NXroot<Imp>::create()");

		try{
			Imp::create();

			//have to set here some default attributes
			Imp::setAttribute("NX_class","NXroot");
			Imp::setAttribute("NeXus_version","4.2.3");
			Imp::setAttribute("HDF5_version","1.8.7");
			Imp::setAttribute("creator","DESY");

			//have to set the time
			std::time_t time;
			std::time(&time);
			String tstr = String(std::ctime(&time));

			Imp::setAttribute("file_time",tstr);
			Imp::setAttribute("file_update_time",tstr);

		}catch(...){
			EXCEPTION_INIT(NXrootError,"Creation of root object ["+getFileName()+"] failed!");
			EXCEPTION_THROW();
		}

	}
	virtual void open(){
		EXCEPTION_SETUP("template<typename Imp> NXroot<Imp>::open()");

		try{
			Imp::open();

			if(!Imp::isReadOnly()){
				//if the file is not read only we have to adopt an attribute
				std::time_t time;
				std::time(&time);
				String tstr = std::ctime(&time);
				Imp::setAttribute("file_update_time",tstr);
			}

		}catch(...){
			EXCEPTION_INIT(NXrootError,"Opening of root object ["+getFileName()+"] failed!");
			EXCEPTION_THROW();
		}
	}

	virtual void close(){
		Imp::close();
	}

	virtual String getFileTime(){
		String s;
		Imp::getAttribute("file_time",s);
		return s;
	}

	virtual String getFileUpdateTime(){
		String s;
		Imp::getAttribute("file_update_time",s);
		return s;
	}


	NXentry<typename Imp::GImp> createEntry(const String &n){
		NXentry<typename Imp::GImp> e;

		e = Imp::createGroup(n);
		e.setAttribute("NX_class","NXentry");

		return e;
	}

	NXentry<typename Imp::GImp> openEntry(const String &n){
		NXentry<typename Imp::GImp> e;

		e = Imp::openGroup(n);

		return e;
	}


};

//end of namespace
}
}



#endif /* NXROOT_HPP_ */

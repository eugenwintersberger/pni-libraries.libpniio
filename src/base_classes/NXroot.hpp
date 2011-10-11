/*
 * NXroot.hpp
 *
 *  Created on: Sep 23, 2011
 *      Author: eugen
 */

#ifndef NXROOT_HPP_
#define NXROOT_HPP_

#include "../NXFile.hpp"
#include "../NXGroup.hpp"
#include "../NXExceptions.hpp"
#include "BaseClassExceptions.hpp"
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


	NXentry<NXGroup<typename Base::GImp> > createEntry(const String &n){
		NXentry<NXGroup<typename Base::GImp> > e;

		(NXGroup<typename Base::GImp>)e = Base::createGroup(n);
		e.setAttribute("NX_class","NXentry");

		return e;
	}

	NXentry<NXGroup<typename Base::GImp> > openEntry(const String &n){
		NXentry<NXGroup<typename Base::GImp> > e;

		(NXGroup<typename Base::GImp>)e = Base::openGroup(n);

		return e;
	}


};

//end of namespace
}
}



#endif /* NXROOT_HPP_ */

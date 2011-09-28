/*
 * NXGroupH5Implementation.cpp
 *
 *  Created on: Jul 1, 2011
 *      Author: eugen
 */

extern "C"{
#include <hdf5.h>
}

#include <pni/utils/Exceptions.hpp>

#include "H5Exceptions.hpp"

#include "NXGroupH5Implementation.hpp"
#include "H5TypeFactory.hpp"

#include "../NX.hpp"

namespace pni{
namespace nx{
namespace h5{


//------------------------------------------------------------------------------
NXGroupH5Implementation::NXGroupH5Implementation()
                        :NXObjectH5Implementation(){
	EXCEPTION_SETUP("NXGroupH5Implementation::NXGroupH5Implementation()"
			        ":NXObjectH5Implementation()");
}

//------------------------------------------------------------------------------
NXGroupH5Implementation::~NXGroupH5Implementation() {
	//close a Group if it is no longer needed
	//clearly the parent ID must not be closed since it might be hold
	//by a different object
	close();
}

//------------------------------------------------------------------------------
void NXGroupH5Implementation::create(const String &n,const NXObjectH5Implementation &o){
	EXCEPTION_SETUP("void NXGroupH5Implementation::create(const String &n,const NXObjectH5Implementation &o)");

	hid_t pid = o.getId();  //obtain the parent ID
	hid_t id = 0;           //id of the newly created group

	//create the property list for the group
	hid_t plist = H5Pcreate(H5P_LINK_CREATE);
	if(plist<0){
		EXCEPTION_INIT(H5PropertyListError,"Cannot create group creation property list!");
		EXCEPTION_THROW();
	}
	//create intermediate groups if neccessary
	H5Pset_create_intermediate_group(plist,1);

	//create the group object in the file
	id = H5Gcreate2(pid,n.c_str(),plist, H5P_DEFAULT, H5P_DEFAULT);
	if(id<0){
		EXCEPTION_INIT(H5GroupError,"Cannot create group "+String(n)+"!");
		EXCEPTION_THROW();
	}

	//assemble the implementation object
	setId(id);

	//close the property list
	H5Pclose(plist);

}

//------------------------------------------------------------------------------
NXGroupH5Implementation &
NXGroupH5Implementation::operator=(const NXGroupH5Implementation &o){
	EXCEPTION_SETUP("NXGroupH5Implementation::operator=(const "
					"NXGroupH5Implementation &o)");
	if (this != &o){
		//here we have somehow the same problem as with the copy constructor
		(NXObjectH5Implementation &)(*this) = (NXObjectH5Implementation &)o;
	}

	return *this;
}

//------------------------------------------------------------------------------
void NXGroupH5Implementation::createGroup(const char *n,
		NXGroupH5Implementation &imp) {
	EXCEPTION_SETUP("void NXGroupH5Implementation::createGroup(const char *n,"
					"NXGroupH5Implementation &imp)");

	try{
		imp.create(String(n),*this);
	}catch(...){
		EXCEPTION_INIT(H5GroupError,"Error creating group!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
void NXGroupH5Implementation::openGroup(const char *n,
		                                NXGroupH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::openGroup(const char *n,"
			        "NXGroupH5Implementation &imp)");

	hid_t id = 0;
	id = H5Gopen2(getId(),n,H5P_DEFAULT);
	if(id<0){
		EXCEPTION_INIT(H5GroupError,"Cannot open group ["+String(n)+"]!");
		EXCEPTION_THROW();
	}

	imp.setId(id);
}

//------------------------------------------------------------------------------
void NXGroupH5Implementation::openField(const char *n,
		                                NXFieldH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::openField(const char *n,"
			        "NXFieldH5Implementation &imp)");

	try{
		imp.open(n,*this);
	}catch(...){
		EXCEPTION_INIT(H5DataSetError,"Cannot open dataset "+String(n)+"!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
//create a field for array data
void NXGroupH5Implementation::createField(const char *n, PNITypeID tid,
		                                  const ArrayShape &s,
			                              NXFieldH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::createField(const char *n, "
			        "PNITypeID tid,UInt32 rank, const UInt32 *dims,"
			        "NXFieldH5Implementation &imp)");

	imp.setDataSpace(s);
	imp.setDataType(tid);
	try{
		imp.create(String(n),*this);
	}catch(...){
		EXCEPTION_INIT(H5DataSetError,"Error creating array data-set ["+String(n)+"]");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
void NXGroupH5Implementation::createField(const char *n, PNITypeID tid,
		                                  NXFieldH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::createField(const char *n, "
			        "PNITypeID tid,NXFieldH5Implementation &imp)");

	imp.setDataSpace();
	imp.setDataType(tid);
	try{
		imp.create(String(n),*this);
	}catch(...){
		EXCEPTION_INIT(H5DataSetError,"Error creating scalar data-set ["+String(n)+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
void NXGroupH5Implementation::createField(const char *n, UInt64 size,
		                                  NXFieldH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::createStringField("
			        "const char *n, UInt64 size,NXFieldH5Implementation &imp)");

	imp.setDataSpace();
	imp.setDataType(size);
	try{
		imp.create(String(n),*this);
	}catch(...){
		EXCEPTION_INIT(H5DataSetError,"Error creating string data-set ["+String(n)+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
void NXGroupH5Implementation::remove(const String &n){
	EXCEPTION_SETUP("void NXGroupH5Implementation::remove(const String &n)");
	herr_t retval;

	retval = H5Ldelete(getId(),n.c_str(),H5P_DEFAULT);
	if(retval < 0){
		EXCEPTION_INIT(H5GroupError,"Cannot delete object ["+n+"] from group ["+getName()+"]!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
bool NXGroupH5Implementation::exists(const String &n) const {
	EXCEPTION_SETUP("bool NXGroupH5Implementation::exists(const String &n) const");

	htri_t retval;
	std::vector<String> plist;
	std::vector<String>::iterator iter;
	size_t spos1,spos2;
	String path;
	bool is_abs = false;

	//remove a trailing slash
	if(n[n.size()-1]=='/'){
		path = n.substr(0,n.size()-1);
	}else{
		path = n;
	}

	if(n[0] == '/') is_abs = true;

	//have to split the string
	spos1 = path.find_first_of("/");
	if(spos1 != n.npos){
		if(spos1 != 0) plist.push_back(path.substr(0,spos1));

		do{
			spos2 = path.find_first_of("/",spos1+1);
			plist.push_back(path.substr(spos1+1,(spos2-spos1)-1));
			spos1 = spos2;
		}while(spos2 != path.npos);
	}else{
		plist.push_back(path);
	}

	//clear the path
	path.clear();
	if(is_abs) path += "/";

	for(iter = plist.begin(); iter != plist.end(); ++iter){
		path += *iter;

		//do check
		std::cout<<path<<std::endl;
		retval = H5Lexists(getId(),path.c_str(),H5P_DEFAULT);
		if(retval<0) {
			EXCEPTION_INIT(H5GroupError,"Cannot check existance of objec ["+n+"]!");
			EXCEPTION_THROW();
		}

		if(!retval) return false;

		//append a trailing /
		path += "/";
	}

	return true;
}



//end of namespace
}
}
}

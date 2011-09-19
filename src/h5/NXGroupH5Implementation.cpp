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


NXGroupH5Implementation::NXGroupH5Implementation()
                        :NXObjectH5Implementation(){
	EXCEPTION_SETUP("NXGroupH5Implementation::NXGroupH5Implementation()"
			        ":NXObjectH5Implementation()");
}

NXGroupH5Implementation::~NXGroupH5Implementation() {
	//close a Group if it is no longer needed
	//clearly the parent ID must not be closed since it might be hold
	//by a different object
	close();
}

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
	id = H5Gcreate2(getId(),n,plist, H5P_DEFAULT, H5P_DEFAULT);
	if(id<0){
		EXCEPTION_INIT(H5GroupError,"Cannot create group "+String(n)+"!");
		EXCEPTION_THROW();
	}

	//assemble the implementation object
	setId(id);

	//close the property list
	H5Pclose(plist);

}

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


void NXGroupH5Implementation::openGroup(const char *n,
		                                NXGroupH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::openGroup(const char *n,"
			        "NXGroupH5Implementation &imp)");

	hid_t id = 0;
	id = H5Gopen2(getId(),n,H5P_DEFAULT);
	if(id<0){
		EXCEPTION_INIT(H5GroupError,"Cannot open group ["+n+"]!");
		EXCEPTION_THROW();
	}

	imp.setId(id);
}

void NXGroupH5Implementation::openField(const char *n,
		                                NXFieldH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::openField(const char *n,"
			        "NXFieldH5Implementation &imp)");

	imp._id = H5Dopen(_id,n);
	if(imp._id<0){
		EXCEPTION_INIT(H5DataSetError,"Error opening field ["+String(n)+"]!");
		EXCEPTION_THROW();
	}
	//fetch all other informatoin
	imp._type_id = H5Dget_type(imp._id);
	imp._space_id = H5Dget_space(imp._id);
	imp._creation_plist = H5Dget_create_plist(imp._id);
}

//create a field for array data
void NXGroupH5Implementation::createField(const char *n, PNITypeID tid,
		                                  UInt32 rank, const UInt32 *dims,
			                              NXFieldH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::createField(const char *n, "
			        "PNITypeID tid,UInt32 rank, const UInt32 *dims,"
			        "NXFieldH5Implementation &imp)");

	imp.setDataSpace(rank,dims);
	imp.setDataType(tid);
	try{
		imp.create(String(n),*this);
	}catch(...){
		EXCEPTION_INIT(H5DataSetError,"Error creating array data-set ["+String(n)+"]");
		EXCEPTION_THROW();
	}
}



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


void NXGroupH5Implementation::createLink(const String &s,const String &d){
	String source_file;
	String source_path;

	//we first need to check for external or internal links - only the
	//source must contain an external path file:/path/to/object
	size_t spos = s.find_first_of(":");
	if(spos == String::npos){
		//the source path is not an external location
		source_file.clear();
		source_path = s;
	}else{
		source_file = String(s,0,spos);
		source_path = String(s,spos+1,(s.size()-spos-1));
	}

	if(source_file.empty()){
		//create an internal link
		H5Lcreate_soft((const char *)source_path.c_str(),_id,(const char *)d.c_str(),_gcreate_plist,H5P_DEFAULT);
	}else{
		//create an external link

	}
}

//end of namespace
}
}
}

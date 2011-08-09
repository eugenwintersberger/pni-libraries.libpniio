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

	_gcreate_plist = H5Pcreate(H5P_LINK_CREATE);
	if(_gcreate_plist<0){
		EXCEPTION_INIT(H5PropertyListError,"Cannot create group creation property list!");
		EXCEPTION_THROW();
	}
	//create intermediate groups if neccessary
	H5Pset_create_intermediate_group(_gcreate_plist,1);
}

NXGroupH5Implementation::~NXGroupH5Implementation() {
	//close a Group if it is no longer needed
	//clearly the parent ID must not be closed since it might be hold
	//by a different object
	if(H5Iis_valid(_id)) H5Gclose(_id);
	if(H5Iis_valid(_gcreate_plist)) H5Pclose(_gcreate_plist);
}

NXGroupH5Implementation &
NXGroupH5Implementation::operator=(const NXGroupH5Implementation &o){
	EXCEPTION_SETUP("NXGroupH5Implementation::operator=(const "
					"NXGroupH5Implementation &o)");
	if (this != &o){
		//here we have somehow the same problem as with the copy constructor

		if(H5Iis_valid(o._id)){
			setParent(o.getParent());
			try{
				open(o.getName());
			}catch(H5GroupError &e){
				EXCEPTION_INIT(H5GroupError,"Error opening group ["+o.getName()
						+"] during assignment!");
				EXCEPTION_THROW();
			}
			_gcreate_plist = H5Gget_create_plist(_id);
			//_name = o._name;
		}else{
			_id = 0;
			_pid = 0;
		}
	}

	return *this;
}

void NXGroupH5Implementation::createGroup(const char *n,
		NXGroupH5Implementation &imp) {
	EXCEPTION_SETUP("void NXGroupH5Implementation::createGroup(const char *n,"
					"NXGroupH5Implementation &imp)");
	//we have to create a new r
	imp.setParent(_id);
	//imp._name = String(n);

	try{
		imp.create(String(n));
	}catch(H5GroupError &e){
		EXCEPTION_INIT(H5GroupError,"Cannot create group ["+String(n)+"]!");
		EXCEPTION_THROW();
	}
}

void NXGroupH5Implementation::create(const String &n){
	EXCEPTION_SETUP("void NXGroupH5Implementation::create(const String &n)");

	_id = H5Gcreate2(_pid, n.c_str(), _gcreate_plist, H5P_DEFAULT, H5P_DEFAULT);
	if(_id<0){
		EXCEPTION_INIT(H5GroupError,"Cannot create group "+n+"!");
		EXCEPTION_THROW();
	}
}

void NXGroupH5Implementation::openGroup(const char *n,
		                                NXGroupH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::openGroup(const char *n,"
			        "NXGroupH5Implementation &imp)");
	imp.setParent(_id);
	//imp._name = String(n);
	try{
		imp.open(String(n));
	}catch(H5GroupError &e){
		EXCEPTION_INIT(H5GroupError,"Cannot open group ["+String(n)+"]!");
		EXCEPTION_THROW();
	}

}

void NXGroupH5Implementation::open(const String &n){
	EXCEPTION_SETUP("void NXGroupH5Implementation::open(const String &n)");

	_id = H5Gopen2(_pid,(char *)n.c_str(),H5P_DEFAULT);
	if(_id<0){
		EXCEPTION_INIT(H5GroupError,"Cannot open group ["+n+"]!");
		EXCEPTION_THROW();
	}
}

void NXGroupH5Implementation::createField(const char *n, PNITypeID tid,
		                                  const ArrayShape &s,
										  NXFieldH5Implementation &imp){

	createField(n,tid,s.getRank(),s.getDimensions(),imp);
}

void NXGroupH5Implementation::createField(const char *n, PNITypeID tid,
		                                  const ArrayShape::sptr s,
		                                  NXFieldH5Implementation &imp){

	createField(n,tid,s->getRank(),s->getDimensions(),imp);
}

void NXGroupH5Implementation::openField(const char *n,
		                                NXFieldH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::openField(const char *n,"
			        "NXFieldH5Implementation &imp)");

	imp.setParent(_id);
	try{
		imp.open(String(n));
	}catch(...){
		EXCEPTION_INIT(H5DataSetError,"Error opening field ["+String(n)+"]!");
		EXCEPTION_THROW();
	}
}

//create a field for array data
void NXGroupH5Implementation::createField(const char *n, PNITypeID tid,
		                                  UInt32 rank, const UInt32 *dims,
			                              NXFieldH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::createField(const char *n, "
			        "PNITypeID tid,UInt32 rank, const UInt32 *dims,"
			        "NXFieldH5Implementation &imp)");

	NXLZFFilter f;

	try{
		imp.setParent(_id);
		imp.setDataSpace(rank,dims);
		imp.setDataType(tid);
		imp.setChunkedLayout();
		imp.setChunkSize(rank,dims);
		imp.setShuffle();
		imp.setFilter(f);
		imp.create(String(n));
	}catch(...){
		EXCEPTION_INIT(H5DataSetError,"Error creating array data-set ["+String(n)+"]");
		EXCEPTION_THROW();
	}
}

void NXGroupH5Implementation::createField(const char *n, PNITypeID tid,
		                                  NXFieldH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::createField(const char *n, "
			        "PNITypeID tid,NXFieldH5Implementation &imp)");

	try{
		imp.setParent(_id);
		imp.setDataSpace();
		imp.setDataType(tid);
		imp.create(String(n));
	}catch(...){
		EXCEPTION_INIT(H5DataSetError,"Error creating scalar data-set ["+String(n)+"]!");
		EXCEPTION_THROW();
	}
}

void NXGroupH5Implementation::createStringField(const char *n, UInt64 size,
		                                        NXFieldH5Implementation &imp){
	EXCEPTION_SETUP("void NXGroupH5Implementation::createStringField("
			        "const char *n, UInt64 size,NXFieldH5Implementation &imp)");

	try{
		imp.setParent(_id);
		imp.setDataSpace();
		imp.setDataType(size);
		imp.create(String(n));
	}catch(...){
		EXCEPTION_INIT(H5DataSetError,"Error creating string data-set ["+String(n)+"]!");
		EXCEPTION_THROW();
	}
}


void NXGroupH5Implementation::close(){
	if(H5Iis_valid(_id)) H5Gclose(_id);
}

//end of namespace
}
}
}

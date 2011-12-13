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


//=============Implementation of constructors and destructor====================
//Implementation of the default constructor
NXGroupH5Implementation::NXGroupH5Implementation()
                        :NXObjectH5Implementation(){
	EXCEPTION_SETUP("NXGroupH5Implementation::NXGroupH5Implementation()"
			        ":NXObjectH5Implementation()");
}

//------------------------------------------------------------------------------
//Implementation of the copy constructor
NXGroupH5Implementation::NXGroupH5Implementation(const NXGroupH5Implementation &o)
                        :NXObjectH5Implementation(o){

}

//------------------------------------------------------------------------------
//Implementation of the move constructor
NXGroupH5Implementation::NXGroupH5Implementation(NXGroupH5Implementation &&o){
	*this = std::move(o);
}

//------------------------------------------------------------------------------
//implementation of copy conversion constructor
NXGroupH5Implementation::NXGroupH5Implementation(const NXObjectH5Implementation &o)
:NXObjectH5Implementation(o){

}

//------------------------------------------------------------------------------
//implementation of move conversion operator
NXGroupH5Implementation::NXGroupH5Implementation(NXObjectH5Implementation &&o)
:NXObjectH5Implementation(std::move(o)){

}

//------------------------------------------------------------------------------
NXGroupH5Implementation::~NXGroupH5Implementation() {
	//close a Group if it is no longer needed
	//clearly the parent ID must not be closed since it might be hold
	//by a different object
	close();
}



//=================Implementation of assignment operations======================
//Implementation of the copy assignment operator
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
//Implementation of the move assignment operator
NXGroupH5Implementation &NXGroupH5Implementation::operator=(NXGroupH5Implementation &&o){
	EXCEPTION_SETUP("NXGroupH5Implementation &NXGroupH5Implementation::operator=(NXGroupH5Implementation &&o)");
	if(this != &o){
		(NXObjectH5Implementation &)(*this) = std::move((NXObjectH5Implementation &)o);
	}
	return *this;
}

//------------------------------------------------------------------------------
//Implementation of the copy conversion assignment operator
NXGroupH5Implementation &NXGroupH5Implementation::operator=(const NXObjectH5Implementation &o){
	if(this != &o){
		(NXObjectH5Implementation &)(*this) = o;
	}
	return *this;
}

//------------------------------------------------------------------------------
//implementation of the move conversion assignment operator
NXGroupH5Implementation &NXGroupH5Implementation::operator=(NXObjectH5Implementation &&o){
	if(this != &o){
		(NXObjectH5Implementation &)(*this) = std::move(o);
	}
	return *this;
}


//=====================Implementation of object creation methods================
//------------------------------------------------------------------------------
NXGroupH5Implementation NXGroupH5Implementation::createGroup(const String &n) const{
	EXCEPTION_SETUP("void NXGroupH5Implementation::createGroup(const char *n,"
					"NXGroupH5Implementation &imp)");

	NXGroupH5Implementation group;

	hid_t pid = getId();  //obtain the parent ID
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
	group.setId(id);

	//close the property list
	H5Pclose(plist);

	return group;
}

//------------------------------------------------------------------------------
//create a field for array data
NXNumericFieldH5Implementation NXGroupH5Implementation::createNumericField(const String &n, TypeID tid,const Shape &s) const{
	EXCEPTION_SETUP("NXFieldH5Implementation NXGroupH5Implementation::createField(const String &n, PNITypeID tid,const ArrayShape &s)");

	NXNumericFieldH5Implementation field;
	hid_t pid = getId();
	hid_t id;

	//create the data type
	hid_t type_id = H5TFactory.createTypeFromID(tid);
	if(type_id < 0){
		EXCEPTION_INIT(H5DataTypeError,"Type creation failed!");
		EXCEPTION_THROW();
	}

	//create the data space
	hsize_t *dims=nullptr,*mdims=nullptr,*cdims=nullptr;
	dims = new hsize_t[s.rank()+1];
	if(!dims){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for data set dimensions!");
		EXCEPTION_THROW();
	}
	mdims = new hsize_t[s.rank()+1];
	if(!mdims){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for data set max. dimensions!");
		if(dims) delete [] dims;
		EXCEPTION_THROW();
	}
	cdims = new hsize_t[s.rank()+1];
	if(!cdims){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for data set chunk dimensions!");
		if(dims) delete [] dims;
		if(mdims) delete [] mdims;
		EXCEPTION_THROW();
	}

	//can immediately setup the first dimension
	dims[0] = 0;
	cdims[0] = 1;
	mdims[0] = H5S_UNLIMITED;
	//now add all others
	for(UInt32 i=0;i<s.rank();i++){
		dims[i+1] = s.dim(i);
		cdims[i+1] = s.dim(i);
		mdims[i+1] = s.dim(i);
	}

	hid_t space_id = H5Screate_simple(s.rank()+1,dims,mdims);
	if(space_id<0){
		EXCEPTION_INIT(H5DataSpaceError,"Cannot create data space!");
		EXCEPTION_THROW();
	}

	//create property list and set it up
	hid_t creation_plist = H5Pcreate(H5P_DATASET_CREATE);
	hid_t lcreate_plist = H5Pcreate(H5P_LINK_CREATE);
	H5Pset_create_intermediate_group(lcreate_plist,1);
	H5Pset_layout(creation_plist,H5D_CHUNKED);
	H5Pset_chunk(creation_plist,s.rank()+1,cdims);

	//create the dataset
	id = H5Dcreate2(pid,n.c_str(),type_id,space_id,lcreate_plist,creation_plist,H5P_DEFAULT);
	if(id<0){
		EXCEPTION_INIT(H5DataSetError,"Cannot create dataset!");
		EXCEPTION_THROW();
	}

	//if everything was sucessful we can close all intermediate objects
	H5Tclose(type_id);
	H5Pclose(creation_plist);
	H5Pclose(lcreate_plist);
	H5Sclose(space_id);

	//set the id of the new object
	field.setId(id);

	//free memory
	if(dims) delete [] dims;
	if(mdims) delete [] mdims;
	if(cdims) delete [] cdims;

	return field;
}

//-----------------------------------------------------------------------------
NXNumericFieldH5Implementation NXGroupH5Implementation::createNumericField(const String &n, TypeID tid,
		                                  const Shape &s,const H5Filter &f) const{
	EXCEPTION_SETUP("void NXGroupH5Implementation::createField(const char *n, "
			        "PNITypeID tid,UInt32 rank, const UInt32 *dims,"
			        "NXFieldH5Implementation &imp)");

	NXNumericFieldH5Implementation field;
	hid_t pid = getId();
	hid_t id = 0;
	//create the data type
	hid_t type_id = H5TFactory.createTypeFromID(tid);
	if(type_id < 0){
		EXCEPTION_INIT(H5DataTypeError,"Type creation failed!");
		EXCEPTION_THROW();
	}

	//create the data space
	hsize_t *dims=NULL,*mdims=NULL,*cdims=NULL;
	dims = new hsize_t[s.rank()];
	if(dims == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for data set dimensions!");
		EXCEPTION_THROW();
	}
	mdims = new hsize_t[s.rank()];
	if(mdims == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for data set max. dimensions!");
		if(dims != NULL) delete [] dims;
		EXCEPTION_THROW();
	}
	cdims = new hsize_t[s.rank()];
	if(cdims == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for data set chunk dimensions!");
		if(dims != NULL) delete [] dims;
		if(mdims != NULL) delete [] mdims;
		EXCEPTION_THROW();
	}

	for(size_t i=0;i<s.rank();i++){
		dims[i] = s.dim(i);
		cdims[i] = s.dim(i);
		mdims[i] = s.dim(i);
	}
	//modify some of the dimension arrays
	cdims[0] = 1;
	mdims[0] = H5S_UNLIMITED;

	hid_t space_id = H5Screate_simple(s.rank(),dims,mdims);
	if(space_id<0){
		EXCEPTION_INIT(H5DataSpaceError,"Cannot create data space!");
		EXCEPTION_THROW();
	}

	//create property list and set it up
	hid_t creation_plist = H5Pcreate(H5P_DATASET_CREATE);
	hid_t lcreate_plist = H5Pcreate(H5P_LINK_CREATE);
	H5Pset_create_intermediate_group(lcreate_plist,1);
	H5Pset_shuffle(creation_plist);
	H5Pset_layout(creation_plist,H5D_CHUNKED);
	H5Pset_chunk(creation_plist,s.rank(),cdims);

	//here we need to add filter code
	f.setup(creation_plist);

	//create the dataset
	id = H5Dcreate2(pid,n.c_str(),type_id,space_id,lcreate_plist,creation_plist,H5P_DEFAULT);
	if(id<0){
		//raise an exception here
	}

	//if everything was sucessful we can close all intermediate objects
	H5Tclose(type_id);
	H5Pclose(creation_plist);
	H5Pclose(lcreate_plist);
	H5Sclose(space_id);

	//set the id of the new object
	field.setId(id);

	//free memory
	if(dims != NULL) delete [] dims;
	if(mdims != NULL) delete [] mdims;
	if(cdims != NULL) delete [] cdims;


	return field;
}

//------------------------------------------------------------------------------
NXNumericFieldH5Implementation NXGroupH5Implementation::createNumericField(const String &n, TypeID tid) const{
	EXCEPTION_SETUP("NXFieldH5Implementation NXGroupH5Implementation::createField(const String &n, PNITypeID tid)");

	NXNumericFieldH5Implementation field;
	hid_t id = 0;
	hid_t pid = getId();
	hsize_t dims[1];
	hsize_t mdims[1];

	//create the data type
	hid_t type_id = H5TFactory.createTypeFromID(tid);
	if(type_id < 0){
		EXCEPTION_INIT(H5DataTypeError,"Type creation failed!");
		EXCEPTION_THROW();
	}

	//create the data space
	dims[0] = 0;
	mdims[0] = H5S_UNLIMITED;
	hid_t space_id =H5Screate_simple(1,dims,mdims);
	if(space_id<0){
		EXCEPTION_INIT(H5DataSpaceError,"Cannot create scalar data space!");
		EXCEPTION_THROW();
	}

	//create the link creation property list
	hid_t creation_plist = H5Pcreate(H5P_DATASET_CREATE);
	hid_t lcreate_plist = H5Pcreate(H5P_LINK_CREATE);
	H5Pset_create_intermediate_group(lcreate_plist,1);
	H5Pset_layout(creation_plist,H5D_CHUNKED);
	H5Pset_chunk(creation_plist,1,dims);

	//create the data set
	id = H5Dcreate2(pid,n.c_str(),type_id,space_id,lcreate_plist,creation_plist,H5P_DEFAULT);
	if(id<0){
		EXCEPTION_INIT(H5DataSetError,"Creation of data set ["+n+"] below group ["+getName()+"] failed!");
		EXCEPTION_THROW();
	}

	//set the id of the data space object
	field.setId(id);

	return field;
}

//------------------------------------------------------------------------------
NXStringFieldH5Implementation NXGroupH5Implementation::createStringField(const String &n) const{
	EXCEPTION_SETUP("void NXGroupH5Implementation::createStringField("
			        "const char *n, UInt64 size,NXFieldH5Implementation &imp)");

	NXStringFieldH5Implementation field;
	hid_t pid = getId();
	hid_t id = 0;

	//create the data type
	hid_t type_id = H5TFactory.createTypeFromID(TypeID::STRING);
	H5Tset_size(type_id,H5T_VARIABLE);

	//H5Tset_size(type_id,size);
	if(type_id < 0){
		EXCEPTION_INIT(H5DataTypeError,"Type creation failed!");
		EXCEPTION_THROW();
	}

	//create the data space
	hsize_t cdims[1] =  {0};
	hsize_t mdims[1] = {H5S_UNLIMITED};

	//hid_t space_id =H5Screate(H5S_SCALAR);
	hid_t space_id = H5Screate_simple(1,cdims,mdims);
	if(space_id<0){
		EXCEPTION_INIT(H5DataSpaceError,"Cannot create scalar data space!");
		EXCEPTION_THROW();
	}

	//create the link creation property list
	hid_t lcreate_plist = H5Pcreate(H5P_LINK_CREATE);
	H5Pset_create_intermediate_group(lcreate_plist,1);
	hid_t dcreate_plist = H5Pcreate(H5P_DATASET_CREATE);
	H5Pset_layout(dcreate_plist,H5D_CHUNKED);
	cdims[0] = 1;
	H5Pset_chunk(dcreate_plist,1,cdims);

	//create the data set
	id = H5Dcreate2(pid,n.c_str(),type_id,space_id,lcreate_plist,dcreate_plist,H5P_DEFAULT);
	if(id<0){
		EXCEPTION_INIT(H5DataSetError,"Creation of data set ["+n+"] below group ["+getName()+"] failed!");
		EXCEPTION_THROW();
	}

	//close all intermediate objects
	H5Tclose(type_id);
	H5Sclose(space_id);
	H5Pclose(lcreate_plist);

	field.setId(id);

	return field;
}

//------------------------------------------------------------------------------
NXBinaryFieldH5Implementation
NXGroupH5Implementation::createBinaryField(const String &n) const{
	EXCEPTION_SETUP("NXBinaryFieldH5Implementation NXGroupH5Implementation::"
					"createBinaryField(const String &n)");

	NXBinaryFieldH5Implementation field;
	hid_t pid = getId();
	hid_t id = 0;

	//create the data type
	hid_t type_id = H5TFactory.createTypeFromID(TypeID::BINARY);
	H5Tset_size(type_id,H5T_VARIABLE);

	//H5Tset_size(type_id,size);
	if(type_id < 0){
		EXCEPTION_INIT(H5DataTypeError,"Type creation failed!");
		EXCEPTION_THROW();
	}

	//create the data space
	hsize_t cdims[1] =  {0};
	hsize_t mdims[1] = {H5S_UNLIMITED};

	//hid_t space_id =H5Screate(H5S_SCALAR);
	hid_t space_id = H5Screate_simple(1,cdims,mdims);
	if(space_id<0){
		EXCEPTION_INIT(H5DataSpaceError,"Cannot create scalar data space!");
		EXCEPTION_THROW();
	}

	//create the link creation property list
	hid_t lcreate_plist = H5Pcreate(H5P_LINK_CREATE);
	H5Pset_create_intermediate_group(lcreate_plist,1);
	hid_t dcreate_plist = H5Pcreate(H5P_DATASET_CREATE);
	H5Pset_layout(dcreate_plist,H5D_CHUNKED);
	cdims[0] = 1;
	H5Pset_chunk(dcreate_plist,1,cdims);

	//create the data set
	id = H5Dcreate2(pid,n.c_str(),type_id,space_id,lcreate_plist,dcreate_plist,H5P_DEFAULT);
	if(id<0){
		EXCEPTION_INIT(H5DataSetError,"Creation of data set ["+n+"] below group ["+getName()+"] failed!");
		EXCEPTION_THROW();
	}

	//close all intermediate objects
	H5Tclose(type_id);
	H5Sclose(space_id);
	H5Pclose(lcreate_plist);

	field.setId(id);
	return field;
}

//------------------------------------------------------------------------------
void NXGroupH5Implementation::remove(const String &n) const{
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
		//std::cout<<path<<std::endl;
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

//------------------------------------------------------------------------------
NXObjectH5Implementation NXGroupH5Implementation::open(const String &n) const{
	EXCEPTION_SETUP("NXObjectH5Implementation &&NXGroupH5Implementation::open(const String &n) const");
	hid_t oid;

	oid = H5Oopen(getId(),n.c_str(),H5P_DEFAULT);
	if(oid<0){
		EXCEPTION_INIT(H5ObjectError,"Error opening object ["+n+"] from group ["+getName()+"]!");
		EXCEPTION_THROW();
	}

	NXObjectH5Implementation o(oid);
	return o;

}



//end of namespace
}
}
}

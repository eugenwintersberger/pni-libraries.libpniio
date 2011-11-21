/*
 * NXGroupH5Implementation.hpp
 *
 *  Created on: Jul 1, 2011
 *      Author: eugen
 */

#ifndef NXGROUPH5IMPLEMENTATION_HPP_
#define NXGROUPH5IMPLEMENTATION_HPP_

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/ArrayShape.hpp>
#include <pni/utils/Exceptions.hpp>

#include "NXObjectH5Implementation.hpp"
#include "NXFieldH5Implementation.hpp"
#include "H5Exceptions.hpp"
#include "../NXFilter.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{
namespace h5{


class NXGroupH5Implementation:public NXObjectH5Implementation {
private:
	//! copy constructor
	NXGroupH5Implementation(const NXGroupH5Implementation &o){}
public:
	typedef boost::shared_ptr<NXGroupH5Implementation> sptr;
	//! default constructor
	NXGroupH5Implementation();

	//! default destructor
	virtual ~NXGroupH5Implementation();

	//! assignment operator
	NXGroupH5Implementation &operator=(const NXGroupH5Implementation &o);

	//! create a new group below this group
	virtual NXGroupH5Implementation createGroup(const String &n) const;
	//! open a new group belonging to this group
	virtual NXGroupH5Implementation openGroup(const String &n) const;
	//! create a field

	//! create a field
	NXFieldH5Implementation createNumericField(const String &n, PNITypeID tid,const ArrayShape &s) const;

	template<typename Filter>
	NXFieldH5Implementation createNumericField(const String &n, PNITypeID tid,const ArrayShape &s,pni::nx::NXFilter<Filter> &f) const;

	//! method to create a field for a single scalar value
	NXFieldH5Implementation createNumericField(const String &n,PNITypeID) const;
	//! create a field to store string data
	NXFieldH5Implementation createStringField(const String &n,const UInt64 &size) const;
	//! create a field to store binary data
	NXFieldH5Implementation createBinaryField(const String &n,const UInt64 &nbytes);
	//! open an existing field
	virtual NXFieldH5Implementation openField(const String &n) const;

	//! remove an object from the HDF5 tree
	virtual void remove(const String &n) const;
	//! check for the existence of an object
	virtual bool exists(const String &n) const;

};

template<typename Filter>
NXFieldH5Implementation NXGroupH5Implementation::createNumericField(const String &n, PNITypeID tid,
		                                  const ArrayShape &s,pni::nx::NXFilter<Filter> &f) const{
	EXCEPTION_SETUP("void NXGroupH5Implementation::createField(const char *n, "
			        "PNITypeID tid,UInt32 rank, const UInt32 *dims,"
			        "NXFieldH5Implementation &imp)");

	NXFieldH5Implementation field;
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
	dims = new hsize_t[s.getRank()];
	if(dims == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for data set dimensions!");
		EXCEPTION_THROW();
	}
	mdims = new hsize_t[s.getRank()];
	if(mdims == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for data set max. dimensions!");
		if(dims != NULL) delete [] dims;
		EXCEPTION_THROW();
	}
	cdims = new hsize_t[s.getRank()];
	if(cdims == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for data set chunk dimensions!");
		if(dims != NULL) delete [] dims;
		if(mdims != NULL) delete [] mdims;
		EXCEPTION_THROW();
	}

	for(UInt32 i=0;i<s.getRank();i++){
		dims[i] = s.getDimension(i);
		cdims[i] = s.getDimension(i);
		mdims[i] = s.getDimension(i);
	}
	//modify some of the dimension arrays
	cdims[0] = 1;
	mdims[0] = H5S_UNLIMITED;

	hid_t space_id = H5Screate_simple(s.getRank(),dims,mdims);
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
	H5Pset_chunk(creation_plist,s.getRank(),cdims);

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


//end of namespace
}
}
}


#endif /* NXGROUPH5IMPLEMENTATION_HPP_ */

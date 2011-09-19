/*
 * H5Utilities.cpp
 *
 *  Created on: Aug 3, 2011
 *      Author: eugen
 */


#include "H5Utilities.hpp"
#include "H5Exceptions.hpp"
#include "H5TypeFactory.hpp"

namespace pni {
namespace nx {
namespace h5 {


void H5Utilities::ArrayShape2DataSpace(const ArrayShape &s,hid_t &dspace){
	EXCEPTION_SETUP("void H5Utilities::ArrayShape2DataSpace(const ArrayShape &s,hid_t &dspace)");
	hsize_t *dims = NULL;

	//get the rank of the array
	UInt32 rank = s.getRank();
	if(rank == 0){
		//do some error handling here
	}

	//set the dimension array
	dims = new hsize_t[rank];
	for(UInt32 i=0;i<rank;i++) dims[i] = s.getDimension(i);

	dspace = H5Screate_simple(rank,dims,NULL);
	if(dspace<0){
		EXCEPTION_INIT(H5DataSpaceError,"Cannot create HDF5 dataspace!");
		EXCEPTION_THROW();
	}

	if(dims != NULL) delete [] dims;

}

void H5Utilities::DataSpace2ArrayShape(const hid_t &dspace,ArrayShape &s){
	EXCEPTION_SETUP("void H5Utilities::DataSpace2ArrayShape(const hid_t &dspace,ArrayShape &s)");
	UInt32 rank;
	hsize_t *dims;

	rank = H5Sget_simple_extent_ndims(dspace);
	if(rank < 0){
		EXCEPTION_INIT(H5DataSpaceError,"Cannot obtain data-space rank!");
		EXCEPTION_THROW();
	}

	dims = new hsize_t[rank];
	rank = H5Sget_simple_extent_dims(dspace,dims,NULL);
	if(rank < 0){
		EXCEPTION_INIT(H5DataSpaceError,"Cannot obtain data-space dimensions!");
		EXCEPTION_THROW();
	}

	s.setRank(rank);
	for(UInt32 i=0;i<rank;i++) s.setDimension(i,(UInt32)dims[i]);

	//free memory
	if(dims != NULL) delete [] dims;
}

PNITypeID H5Utilities::H5Type2PNITypeCode(hid_t tid){
	if(H5Tequal(H5TFactory.getTypeFromID(INT8),tid)) return INT8;
	if(H5Tequal(H5TFactory.getTypeFromID(UINT8),tid)) return UINT8;
	if(H5Tequal(H5TFactory.getTypeFromID(INT16),tid)) return INT16;
	if(H5Tequal(H5TFactory.getTypeFromID(UINT16),tid)) return UINT16;
	if(H5Tequal(H5TFactory.getTypeFromID(INT32),tid)) return INT32;
	if(H5Tequal(H5TFactory.getTypeFromID(UINT32),tid)) return UINT32;
	if(H5Tequal(H5TFactory.getTypeFromID(INT64),tid)) return INT64;
	if(H5Tequal(H5TFactory.getTypeFromID(UINT64),tid)) return UINT64;
	if(H5Tequal(H5TFactory.getTypeFromID(FLOAT32),tid)) return FLOAT32;
	if(H5Tequal(H5TFactory.getTypeFromID(FLOAT64),tid)) return FLOAT64;
	if(H5Tequal(H5TFactory.getTypeFromID(FLOAT128),tid)) return FLOAT128;
	if(H5Tequal(H5TFactory.getTypeFromID(COMPLEX32),tid)) return COMPLEX32;
	if(H5Tequal(H5TFactory.getTypeFromID(COMPLEX64),tid)) return COMPLEX64;
	if(H5Tequal(H5TFactory.getTypeFromID(COMPLEX128),tid)) return COMPLEX128;

	return NONE;
}

//end of namespace
}
}
}

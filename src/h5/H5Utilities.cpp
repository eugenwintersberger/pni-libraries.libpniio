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
	hsize_t *dims = nullptr;

	//get the rank of the array
	UInt32 rank = s.getRank();
	if(rank == 0){
		//in the case of a rank=0 array shape we create a data space
		//for a single number
		hsize_t dims[] = {1};
		dspace = H5Screate_simple(1,dims,dims);
	}else{

		//set the dimension array
		dims = new hsize_t[rank];
		if(!dims){
			EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for data space dimensions!");
			EXCEPTION_THROW();
		}
		for(UInt32 i=0;i<rank;i++) dims[i] = s.getDimension(i);

		dspace = H5Screate_simple(rank,dims,NULL);
		if(dspace<0){
			EXCEPTION_INIT(H5DataSpaceError,"Cannot create HDF5 dataspace!");
			EXCEPTION_THROW();
		}

		if(dims != NULL) delete [] dims;
	}

}

void H5Utilities::DataSpace2ArrayShape(const hid_t &dspace,ArrayShape &s){
	EXCEPTION_SETUP("void H5Utilities::DataSpace2ArrayShape(const hid_t &dspace,ArrayShape &s)");
	UInt32 rank;
	hsize_t *dims = NULL;

	//need to check if the data space is simple (if not do nothing)
	if(!H5Sis_simple(dspace)){
		s.setRank(0);
	}else{

		rank = H5Sget_simple_extent_ndims(dspace);
		if(rank < 0){
			EXCEPTION_INIT(H5DataSpaceError,"Cannot obtain data-space rank!");
			EXCEPTION_THROW();
		}

		dims = new hsize_t[rank];
		if(dims == NULL){
			EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for data-space dimension buffer!");
			EXCEPTION_THROW();
		}
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
}

PNITypeID H5Utilities::H5Type2PNITypeCode(hid_t tid){
	if(H5Tequal(H5TFactory.getTypeFromID(PNITypeID::INT8),tid)) return PNITypeID::INT8;
	if(H5Tequal(H5TFactory.getTypeFromID(PNITypeID::UINT8),tid)) return PNITypeID::UINT8;
	if(H5Tequal(H5TFactory.getTypeFromID(PNITypeID::INT16),tid)) return PNITypeID::INT16;
	if(H5Tequal(H5TFactory.getTypeFromID(PNITypeID::UINT16),tid)) return PNITypeID::UINT16;
	if(H5Tequal(H5TFactory.getTypeFromID(PNITypeID::INT32),tid)) return PNITypeID::INT32;
	if(H5Tequal(H5TFactory.getTypeFromID(PNITypeID::UINT32),tid)) return PNITypeID::UINT32;
	if(H5Tequal(H5TFactory.getTypeFromID(PNITypeID::INT64),tid)) return PNITypeID::INT64;
	if(H5Tequal(H5TFactory.getTypeFromID(PNITypeID::UINT64),tid)) return PNITypeID::UINT64;
	if(H5Tequal(H5TFactory.getTypeFromID(PNITypeID::FLOAT32),tid)) return PNITypeID::FLOAT32;
	if(H5Tequal(H5TFactory.getTypeFromID(PNITypeID::FLOAT64),tid)) return PNITypeID::FLOAT64;
	if(H5Tequal(H5TFactory.getTypeFromID(PNITypeID::FLOAT128),tid)) return PNITypeID::FLOAT128;
	if(H5Tequal(H5TFactory.getTypeFromID(PNITypeID::COMPLEX32),tid)) return PNITypeID::COMPLEX32;
	if(H5Tequal(H5TFactory.getTypeFromID(PNITypeID::COMPLEX64),tid)) return PNITypeID::COMPLEX64;
	if(H5Tequal(H5TFactory.getTypeFromID(PNITypeID::COMPLEX128),tid)) return PNITypeID::COMPLEX128;

	if(H5Tis_variable_str(tid)){
		return PNITypeID::STRING;
	}

	return PNITypeID::NONE;
}

//end of namespace
}
}
}

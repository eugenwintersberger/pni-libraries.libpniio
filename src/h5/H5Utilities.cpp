/*
 * H5Utilities.cpp
 *
 *  Created on: Aug 3, 2011
 *      Author: eugen
 */

#include "H5Utilities.hpp"
#include "H5Exceptions.hpp"

namespace pni {
namespace nx {
namespace h5 {


void H5Utilities::ArrayShape2DataSpace(const ArrayShape &s,hid_t &dspace){
	H5METHOD_EXCEPTION_SETUP("void H5Utilities::ArrayShape2DataSpace(const ArrayShape &s,hid_t &dspace)");
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
		H5METHOD_EXCEPTION_INIT(H5DataSpaceException,"Cannot create HDF5 dataspace!");
		H5METHOD_EXCEPTION_THROW();
	}

	if(dims != NULL) delete [] dims;

}

void H5Utilities::DataSpace2ArrayShape(const hid_t &dspace,ArrayShape &s){
	H5METHOD_EXCEPTION_SETUP("void H5Utilities::DataSpace2ArrayShape(const hid_t &dspace,ArrayShape &s)");
	UInt32 rank;
	hsize_t *dims;
	UInt32 *sdims;

	rank = H5Sget_simple_extent_ndims(dspace);
	if(rank < 0){
		H5METHOD_EXCEPTION_INIT(H5DataSpaceException,"Cannot obtain data-space rank!");
		H5METHOD_EXCEPTION_THROW();
	}

	dims = new hsize_t[rank];
	sdims = new UInt32[rank];
	rank = H5Sget_simple_extent_dims(dspace,dims,NULL);
	if(rank < 0){
		H5METHOD_EXCEPTION_INIT(H5DataSpaceException,"Cannot obtain data-space dimensions!");
		H5METHOD_EXCEPTION_THROW();
	}

	for(UInt32 i=0;i<rank;i++) sdims[i] = dims[i];

	s = ArrayShape(rank,sdims);

	//free memory
	if(dims != NULL) delete [] dims;
	if(sdims != NULL) delete [] sdims;
}

//end of namespace
}
}
}

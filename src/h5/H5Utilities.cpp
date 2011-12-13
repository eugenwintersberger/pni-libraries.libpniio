/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * H5Utilities.cpp
 *
 *  Created on: Aug 3, 2011
 *      Author: Eugen Wintersberger
 */


#include "H5Utilities.hpp"
#include "H5Exceptions.hpp"
#include "H5TypeFactory.hpp"

namespace pni {
namespace nx {
namespace h5 {

//------------------------------------------------------------------------------
void H5Utilities::Shape2DataSpace(const Shape &s,hid_t &dspace){
	EXCEPTION_SETUP("void H5Utilities::ArrayShape2DataSpace("
				    "const ArrayShape &s,hid_t &dspace)");
	hsize_t *dims = nullptr;

	//get the rank of the array
	UInt32 rank = s.rank();
	if(rank == 0){
		//in the case of a rank=0 array shape we create a data space
		//for a single number
		hsize_t dims[] = {1};
		dspace = H5Screate_simple(1,dims,dims);
	}else{

		//set the dimension array
		dims = new hsize_t[rank];
		if(!dims){
			EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for "
						   "data space dimensions!");
			EXCEPTION_THROW();
		}
		for(UInt32 i=0;i<rank;i++) dims[i] = s.dim(i);

		dspace = H5Screate_simple(rank,dims,NULL);
		if(dspace<0){
			EXCEPTION_INIT(H5DataSpaceError,"Cannot create HDF5 dataspace!");
			EXCEPTION_THROW();
		}

		if(dims != NULL) delete [] dims;
	}

}

//------------------------------------------------------------------------------
void H5Utilities::DataSpace2Shape(const hid_t &dspace,Shape &s){
	EXCEPTION_SETUP("void H5Utilities::DataSpace2ArrayShape"
					"(const hid_t &dspace,ArrayShape &s)");
	UInt32 rank;
	hsize_t *dims = nullptr;

	//need to check if the data space is simple (if not do nothing)
	if(!H5Sis_simple(dspace)){
		s.rank(0);
	}else{

		//obtain the rank of the data space
		rank = H5Sget_simple_extent_ndims(dspace);
		if(rank < 0){
			EXCEPTION_INIT(H5DataSpaceError,"Cannot obtain data-space rank!");
			EXCEPTION_THROW();
		}

		//obtain the number of elements along each dimension of the data-space
		dims = new hsize_t[rank];
		if(!dims){
			EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for "
						   "data-space dimension buffer!");
			EXCEPTION_THROW();
		}
		rank = H5Sget_simple_extent_dims(dspace,dims,NULL);
		if(rank < 0){
			EXCEPTION_INIT(H5DataSpaceError,
						  "Cannot obtain data-space dimensions!");
			EXCEPTION_THROW();
		}

		//setup the shape object
		s.rank(rank);
		for(size_t i=0;i<rank;i++) s.dim(i,(UInt32)dims[i]);

		//free memory
		if(dims) delete [] dims;
	}
}

//------------------------------------------------------------------------------
TypeID H5Utilities::H5Type2PNITypeCode(hid_t tid){
	if(H5Tequal(H5TFactory.getTypeFromID(TypeID::INT8),tid)){
		return TypeID::INT8;
	}
	if(H5Tequal(H5TFactory.getTypeFromID(TypeID::UINT8),tid)){
		return TypeID::UINT8;
	}
	if(H5Tequal(H5TFactory.getTypeFromID(TypeID::INT16),tid)){
		return TypeID::INT16;
	}
	if(H5Tequal(H5TFactory.getTypeFromID(TypeID::UINT16),tid)){
		return TypeID::UINT16;
	}
	if(H5Tequal(H5TFactory.getTypeFromID(TypeID::INT32),tid)){
		return TypeID::INT32;
	}
	if(H5Tequal(H5TFactory.getTypeFromID(TypeID::UINT32),tid)){
		return TypeID::UINT32;
	}
	if(H5Tequal(H5TFactory.getTypeFromID(TypeID::INT64),tid)){
		return TypeID::INT64;
	}
	if(H5Tequal(H5TFactory.getTypeFromID(TypeID::UINT64),tid)){
		return TypeID::UINT64;
	}
	if(H5Tequal(H5TFactory.getTypeFromID(TypeID::FLOAT32),tid)){
		return TypeID::FLOAT32;
	}
	if(H5Tequal(H5TFactory.getTypeFromID(TypeID::FLOAT64),tid)){
		return TypeID::FLOAT64;
	}
	if(H5Tequal(H5TFactory.getTypeFromID(TypeID::FLOAT128),tid)){
		return TypeID::FLOAT128;
	}
	if(H5Tequal(H5TFactory.getTypeFromID(TypeID::COMPLEX32),tid)){
		return TypeID::COMPLEX32;
	}
	if(H5Tequal(H5TFactory.getTypeFromID(TypeID::COMPLEX64),tid)){
		return TypeID::COMPLEX64;
	}
	if(H5Tequal(H5TFactory.getTypeFromID(TypeID::COMPLEX128),tid)){
		return TypeID::COMPLEX128;
	}

	if(H5Tis_variable_str(tid)){
		return TypeID::STRING;
	}

	if(H5Tequal(H5TFactory.getTypeFromID(TypeID::BINARY),tid)){
		return TypeID::BINARY;
	}

	//if no type fits return NONE
	return TypeID::NONE;
}

//end of namespace
}
}
}

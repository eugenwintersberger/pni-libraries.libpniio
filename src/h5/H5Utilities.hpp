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
 * H5Utilities.hpp
 *
 *  Created on: Aug 3, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef H5UTILITIES_HPP_
#define H5UTILITIES_HPP_

#include <pni/utils/Shape.hpp>
#include <pni/utils/Types.hpp>
#include <pni/utils/Exceptions.hpp>
#include <pni/utils/Selection.hpp>

extern "C"{
#include <hdf5.h>
}

using namespace pni::utils;

namespace pni {
namespace nx {
namespace h5 {

//! \ingroup HDF5-Implementation

//! \brief HDF5 utility class

//! Provides static methods to convert between HDF5 objects and PNI objects.
//! SHOULD BE IMPLEMNETED AS SINGLETON!
class H5Utilities {
private:
	//class can neither be copied nor assigned
	H5Utilities(const H5Utilities &o){}
	H5Utilities &operator=(const H5Utilities &o){return *this;}
public:
	//! default constructor
	H5Utilities(){}
	//! destructor
	virtual ~H5Utilities(){}

	//! data space from array shape

	//! Create an HDF5 data space from an ArrayShape object.
	//! \throws MemoryAllocationError if allocation of temporary buffers fails
	//! \throws H5DataSpaceError if data space creation fails
	//! \param s ArrayShape object
	//! \param dspace data space id
	static void Shape2DataSpace(const Shape &s,hid_t &dspace);
	//! ArrayShape from data space

	//! Creates an ArraySpace object from an existing HDF5 data space.
	//! If the data-space is not simple a shape object with rank=0 is
	//! created.
	//! \throws H5DataSpaceError in cases where data-space inquiry fails
	//! \throws MemoryAllocationError if temporary buffer allocation fails
	//! \param dspace data space id
	//! \param s ArrayShape object
	static void DataSpace2Shape(const hid_t &dspace,Shape &s);
	//! Selection from dataspace

	//! Creates a selection that is appropriate for a given data space.
	//! This means that the buffers of the selection are allocated properly.
	static void DataSpace2Selection(const hid_t &dspace,Selection &s);

	static void Selection2DataSpace(const Selection &s,hid_t &dspace);

	//! convert HDF5 data type

	//! Gets the PNI type code from an HDF5 data type. If there is no
	//! corresponding PNI type available for a particular HDF5 type
	//! PNITypeID::NONE is returned.
	//! \param tid HDF5 type object
	//! \return PNI type ID
	static TypeID H5Type2PNITypeCode(const hid_t tid);
};

static H5Utilities H5Utils;

//end of namespace
}
}
}

#endif /* H5UTILITIES_HPP_ */

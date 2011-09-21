/*
 * H5Utilities.hpp
 *
 *  Created on: Aug 3, 2011
 *      Author: eugen
 */

#ifndef H5UTILITIES_HPP_
#define H5UTILITIES_HPP_

#include <pni/utils/ArrayShape.hpp>
#include <pni/utils/PNITypes.hpp>
#include <pni/utils/Exceptions.hpp>
#include <pni/utils/Selection.hpp>

extern "C"{
#include <hdf5.h>
}

using namespace pni::utils;

namespace pni {
namespace nx {
namespace h5 {

class H5Utilities {
private:
	H5Utilities(const H5Utilities &o){}
	H5Utilities &operator=(const H5Utilities &o){return *this;}
public:
	H5Utilities(){}
	virtual ~H5Utilities(){}

	//! data space from array shape

	//! Create an HDF5 data space from an ArrayShape object.
	//! \param s ArrayShape object
	//! \param dspace data space id
	static void ArrayShape2DataSpace(const ArrayShape &s,hid_t &dspace);
	//! ArrayShape from data space

	//! Creates an ArraySpace object from an existing HDF5 data space.
	//! \param dspace data space id
	//! \param s ArrayShape object
	static void DataSpace2ArrayShape(const hid_t &dspace,ArrayShape &s);
	//! Selection from dataspace

	//! Creates a selection that is appropriate for a given data space.
	//! This means that the buffers of the selection are allocated properly.
	static void DataSpace2Selection(const hid_t &dspace,Selection &s);

	static void Selection2DataSpace(const Selection &s,hid_t &dspace);
	static PNITypeID H5Type2PNITypeCode(const hid_t tid);
};

static H5Utilities H5Utils;

//end of namespace
}
}
}

#endif /* H5UTILITIES_HPP_ */

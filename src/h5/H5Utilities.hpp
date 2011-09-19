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

	static void ArrayShape2DataSpace(const ArrayShape &s,hid_t &dspace);
	static void DataSpace2ArrayShape(const hid_t &dspace,ArrayShape &s);
	static PNITypeID H5Type2PNITypeCode(const hid_t tid);
};

static H5Utilities H5Utils;

//end of namespace
}
}
}

#endif /* H5UTILITIES_HPP_ */

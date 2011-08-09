/*
 * H5Filter.hpp
 *
 *  Created on: Aug 9, 2011
 *      Author: eugen
 */

#ifndef H5FILTER_HPP_
#define H5FILTER_HPP_

extern "C"{
#include <hdf5.h>
}

#include <pni/utils/PNITypes.hpp>

using namespace pni::utils;

namespace pni {
namespace nx {
namespace h5 {

class H5Filter {
public:
	H5Filter();
	H5Filter(const H5Filter &o);
	virtual ~H5Filter();

	H5Filter &operator=(const H5Filter &o);

	void setup(hid_t _id);

};


//end of namespace
}
}
}

#endif /* H5FILTER_HPP_ */

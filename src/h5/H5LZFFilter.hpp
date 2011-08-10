/*
 * H5LZFFilter.hpp
 *
 *  Created on: Aug 10, 2011
 *      Author: eugen
 */

#ifndef H5LZFFILTER_HPP_
#define H5LZFFILTER_HPP_

extern "C"{
#include <hdf5.h>
}

#include <pni/utils/PNITypes.hpp>

#include "H5Filter.hpp"

using namespace pni::utils;

namespace pni {
namespace nx {
namespace h5 {

class H5LZFFilter:public H5Filter {
public:
	H5LZFFilter();
	H5LZFFilter(const H5LZFFilter &o);
	virtual ~H5LZFFilter();

	H5LZFFilter &operator=(const H5LZFFilter &o);

	virtual void setup(hid_t id);
};


//end of namespace
}
}
}

#endif /* H5LZFFILTER_HPP_ */

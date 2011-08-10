/*
 * H5LZFFilter.cpp
 *
 *  Created on: Aug 10, 2011
 *      Author: eugen
 */

#include "H5LZFFilter.hpp"
extern "C"{
#include "filters/lzf_filter.h"
}

namespace pni {
namespace nx {
namespace h5 {

H5LZFFilter::H5LZFFilter():H5Filter() {

}

H5LZFFilter::H5LZFFilter(const H5LZFFilter &o){

}

H5LZFFilter::~H5LZFFilter() {
}


H5LZFFilter &H5LZFFilter::operator=(const H5LZFFilter &o){
	if(this != &o){

	}

	return *this;
}

void H5LZFFilter::setup(hid_t id){
	H5Pset_filter(id, H5PY_FILTER_LZF, H5Z_FLAG_OPTIONAL, 0, NULL);
}

//end of namespace
}
}
}

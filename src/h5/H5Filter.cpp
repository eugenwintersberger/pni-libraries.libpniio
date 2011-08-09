/*
 * H5Filter.cpp
 *
 *  Created on: Aug 9, 2011
 *      Author: eugen
 */

#include <pni/utils/Exceptions.hpp>

#include "filters/lzf_filter.h"
#include "H5Filter.hpp"

namespace pni {
namespace nx {
namespace h5 {

H5Filter::H5Filter() {

}

H5Filter::H5Filter(const H5Filter &o){
	EXCEPTION_SETUP("H5Filter::H5Filter(const H5Filter &o)");

}

H5Filter::~H5Filter() {

}

H5Filter &H5Filter::operator=(const H5Filter &f){
	EXCEPTION_SETUP("H5Filter &H5Filter::operator=(const H5Filter &f)");
	if( this != &f ){

	}

	return *this;
}

void H5Filter::setup(hid_t id){
	H5Pset_filter(id, H5PY_FILTER_LZF, H5Z_FLAG_OPTIONAL, 0, NULL);
}


//end of namespace
}
}
}

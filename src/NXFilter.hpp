/*
 * NXFilter.hpp
 *
 *  Created on: Aug 8, 2011
 *      Author: eugen
 */

#ifndef NXFILTER_HPP_
#define NXFILTER_HPP_

#include <pni/utils/PNITypes.hpp>

#include "NXObject.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{


class NXFilter{
public:
	NXFilter();
	NXFilter(const NXFilter &f);
	virtual ~NXFilter();

	NXFilter &operator=(const NXFilter &f);
};

NXFilter::NXFilter(){

}

NXFilter::NXFilter(const NXFilter &o){
}

NXFilter::~NXFilter(){

}

NXFilter &NXFilter::operator=(const NXFilter &f){

	return *this;
}



//end of namespace
}
}


#endif /* NXFILTER_HPP_ */

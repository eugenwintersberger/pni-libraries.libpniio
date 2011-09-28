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


template<typename Filter>
class NXFilter:public Filter{
public:
	NXFilter();
	NXFilter(const NXFilter<Filter> &f);
	virtual ~NXFilter();

	NXFilter<Filter> &operator=(const NXFilter<Filter> &f);

	const ArrayShape &getChunkShape() const;
	void setChunkShape(const ArrayShape &s);
};

template<typename Filter> NXFilter<Filter>::NXFilter():Filter(){
}

template<typename Filter> NXFilter<Filter>::NXFilter(const NXFilter<Filter> &o){
	Filter::Filter(o);
}

template<typename Filter> NXFilter<Filter>::~NXFilter(){

}

template<typename Filter>
NXFilter<Filter> &NXFilter<Filter>::operator=(const NXFilter<Filter> &f){
	if ( this != &f){

	}

	return *this;
}




//end of namespace
}
}


#endif /* NXFILTER_HPP_ */

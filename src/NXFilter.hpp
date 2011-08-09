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


template<typename Imp>
class NXFilter:public Imp{
public:
	NXFilter();
	NXFilter(const NXFilter &f);
	virtual ~NXFilter();

	NXFilter &operator=(const NXFilter &f);
};

template<typename Imp> NXFilter<Imp>::NXFilter():Imp(){
}

template<typename Imp> NXFilter<Imp>::NXFilter(const NXFilter &o){
}

template<typename Imp> NXFilter<Imp>::~NXFilter(){

}

template<typename Imp>
NXFilter<Imp> &NXFilter<Imp>::operator=(const NXFilter<Imp> &f){
	if ( this != &f){

	}

	return *this;
}



//end of namespace
}
}


#endif /* NXFILTER_HPP_ */

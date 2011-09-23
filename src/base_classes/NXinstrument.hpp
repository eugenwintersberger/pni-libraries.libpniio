/*
 * NXinstrument.hpp
 *
 *  Created on: Sep 23, 2011
 *      Author: eugen
 */

#ifndef NXINSTRUMENT_HPP_
#define NXINSTRUMENT_HPP_

#include "NXGroup.hpp"


namespace pni{
namespace nx{

template<typename Imp>
class NXinstrument:public NXGroup<Imp>{
public:
	NXinstrument():NXGroup<Imp>(){}
	NXinstrument(const NXInstrument &o):NXGroup<Imp>(o){}
	virtual ~NXinstrument(){}

	NXinstrument &operator=(const NXinstrument &o){
		if(this != &o){
			(NXGroup<Imp> &)(*this) = (NXGroup<Imp> &)o;
		}

		return *this;
	}


};

//end of namespace
}
}



#endif /* NXINSTRUMENT_HPP_ */

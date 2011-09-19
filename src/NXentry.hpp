/*
 * NXentry.hpp
 *
 *  Created on: Sep 19, 2011
 *      Author: eugen
 */

#ifndef NXENTRY_HPP_
#define NXENTRY_HPP_

#include "NXGroup.hpp"

namespace pni{
namespace nx{


template<typename Imp>
class NXentry:public NXGroup<Imp>{
public:
	NXentry();
	virtual ~NXentry();


};


//end of namespace
}
}


#endif /* NXENTRY_HPP_ */

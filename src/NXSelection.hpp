/*
 * NXSelection.hpp
 *
 *  Created on: Sep 21, 2011
 *      Author: eugen
 */

#ifndef NXSELECTION_HPP_
#define NXSELECTION_HPP_

#include<pni/utils/PNITypes.hpp>
#include<pni/utils/ArrayObject.hpp>

using namespace pni::utils;

namespace pni{
namespace nx{

//! \brief selection decorator for array fields
template<typename Imp> class NXSelection:public Imp{
public:
	NXSelection():Imp(){}
	virtual ~NXSelection(){}

};


}
}


#endif /* NXSELECTION_HPP_ */

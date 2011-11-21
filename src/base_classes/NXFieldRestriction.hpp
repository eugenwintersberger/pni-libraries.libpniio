/*
 * NXFieldRestriction.hpp
 *
 *  Created on: Oct 18, 2011
 *      Author: eugen
 */

#ifndef NXFIELDRESTRICTION_HPP_
#define NXFIELDRESTRICTION_HPP_

#include <pni/utils/PNITypes.hpp>

using namespace pni::utils;

namespace pni {
namespace nx {

class NXFieldRestriction {
private:
	PNITypeID _tid;
	PNITypeClass _tclass;
	bool _is_array;
	bool _is_scalar;
	//need here a field to check the unit class

public:
	NXFieldRestriction();
	NXFieldRestriction(const PNITypeID &tid,const PNITypeClass &tclass,const bool &isarray,const bool &isscalar);
	virtual ~NXFieldRestriction();

	bool check_type(const PNITypeID &tid);
	bool check_type_class(const PNITypeClass &tclass);
	bool is_array() const {
		return _is_array;
	}

	bool is_scalar() const{
		return _is_scalar;
	}
};

} /* namespace nx */
} /* namespace pni */
#endif /* NXFIELDRESTRICTION_HPP_ */

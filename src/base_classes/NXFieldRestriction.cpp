/*
 * NXFieldRestriction.cpp
 *
 *  Created on: Oct 18, 2011
 *      Author: eugen
 */

#include "NXFieldRestriction.hpp"

namespace pni {
namespace nx {

NXFieldRestriction::NXFieldRestriction() {
	_tclass = PNITypeClass::NONE;
	_tid = PNITypeID::NONE;

}

NXFieldRestriction::NXFieldRestriction(const PNITypeID &tid,const PNITypeClass &tclass,const bool &isarray,const bool &isscalar){
	_tclass = tclass;
	_tid = tid;
	_is_array = isarray;
	_is_scalar = isscalar;
}

NXFieldRestriction::~NXFieldRestriction() {
	// TODO Auto-generated destructor stub
}

bool NXFieldRestriction::check_type(const PNITypeID &tid){
	if(_tid != PNITypeID::NONE){
		if(_tid != tid) return false;
	}
	return true;
}
bool NXFieldRestriction::check_type_class(const PNITypeClass &tclass){
	if(_tclass != PNITypeClass::NONE){
		if(_tclass != tclass) return false;
	}
	return true;
}

} /* namespace nx */
} /* namespace pni */

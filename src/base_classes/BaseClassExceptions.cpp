/*
 * BaseClassExceptions.cpp
 *
 *  Created on: Sep 23, 2011
 *      Author: eugen
 */

#include "BaseClassExceptions.hpp"

namespace pni {
namespace nx {

std::ostream &operator<<(std::ostream &o,const NXrootError &e){
	return e.print(o);
}

std::ostream &operator<<(std::ostream &o,const NXentryError &e){
	return e.print(o);
}

std::ostream &operator<<(std::ostream &o,const NXinstrumentError &e){
	return e.print(o);
}

std::ostream &operator<<(std::ostream &o,const NXdetectorError &e){
	return e.print(o);
}

} /* namespace nx */
} /* namespace pni */

/*
 * NXDateTime.cpp
 *
 *  Created on: Nov 17, 2011
 *      Author: eugen
 */

#include "NXDateTime.hpp"

namespace pni {
namespace nx {

String NXDateTime::getDateTimeStr(){
	char dtstr[DATETIME_MAX_LENGTH];

	time_t time = std::time(NULL);
	struct tm *loctime = NULL;
	loctime = std::localtime(&time);
	std::strftime(dtstr,DATETIME_MAX_LENGTH,DATETIME_FORMAT,loctime);
	String out(dtstr);
	return out;
}

} /* namespace nx */
} /* namespace pni */

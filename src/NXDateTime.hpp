/*
 * NXDateTime.hpp
 *
 *  Created on: Nov 17, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef NXDATETIME_HPP_
#define NXDATETIME_HPP_

#include<ctime>
#include <pni/utils/PNITypes.hpp>

using namespace pni::utils;

namespace pni {
namespace nx {

#define DATETIME_FORMAT "%Y-%m-%dT%H:%M:%S%z"
#define DATETIME_MAX_LENGTH 1024

class NXDateTime {
public:

	static String getDateTimeStr();
};

} /* namespace nx */
} /* namespace pni */
#endif /* NXDATETIME_HPP_ */

/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * NXDateTime.hpp
 *
 *  Created on: Nov 17, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef NXDATETIME_HPP_
#define NXDATETIME_HPP_

#include<ctime>
#include <pni/utils/Types.hpp>

using namespace pni::utils;

namespace pni {
namespace nx {

#define DATETIME_FORMAT "%Y-%m-%dT%H:%M:%S%z"
#define DATETIME_MAX_LENGTH 1024

//! Nexus compliant date-time string

//! NXDateTime provides static methods to create date-time strings
//! which are compliant to the Nexus standard.
class NXDateTime {
public:

	//! date-time now

	//! Returns a string with a Nexus compliant date-time string
	//! for now.
	static String getDateTimeStr();
};

} /* namespace nx */
} /* namespace pni */
#endif /* NXDATETIME_HPP_ */

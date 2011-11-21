/*
 * Declaration of Nexus specific exceptions
 *
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
 *
 * Declaration of Nexus specific exceptions
 *
 * Created on: Aug 5, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXEXCEPTIONS_HPP_
#define NXEXCEPTIONS_HPP_

#include <iostream>
#include <pni/utils/Exceptions.hpp>

using namespace pni::utils;

namespace pni{
namespace nx{

class NXFieldError:public Exception{
public:
	NXFieldError();
	NXFieldError(const String &i,const String &d);
	virtual ~NXFieldError();

	friend std::ostream &operator<<(std::ostream &o,const NXFieldError &e);
};

class NXAttributeError:public Exception{
public:
	NXAttributeError();
	NXAttributeError(const String &i,const String &d);
	virtual ~NXAttributeError();

	friend std::ostream &operator<<(std::ostream &o,const NXAttributeError &e);
};

class NXGroupError:public Exception{
public:
	NXGroupError();
	NXGroupError(const String &i,const String &d);
	virtual ~NXGroupError();

	friend std::ostream &operator<<(std::ostream &o,const NXGroupError &e);
};

//end of namespace
}
}


#endif /* NXEXCEPTIONS_HPP_ */

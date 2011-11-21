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
 * Created on: Sep 23, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef BASECLASSEXCEPTIONS_HPP_
#define BASECLASSEXCEPTIONS_HPP_

#include <pni/utils/Exceptions.hpp>

using namespace pni::utils;

namespace pni {
namespace nx {

class NXrootError:public Exception{
public:
	NXrootError():Exception("NXrootError"){}
	NXrootError(const String &i,const String &d):Exception("NXrootError",i,d){}
	virtual ~NXrootError(){}

	friend std::ostream &operator<<(std::ostream &o,const NXrootError &e);
};

class NXentryError:public Exception{
public:
	NXentryError():Exception("NXentryError"){}
	NXentryError(const String &i,const String &d):Exception("NXentryError",i,d){}
	virtual ~NXentryError(){}

	friend std::ostream &operator<<(std::ostream &o,const NXentryError &e);
};

class NXinstrumentError:public Exception{
public:
	NXinstrumentError():Exception("NXinstrumentError"){}
	NXinstrumentError(const String &i,const String &d):Exception("NXinstrumentError",i,d){}
	virtual ~NXinstrumentError(){}

	friend std::ostream &operator<<(std::ostream &o,const NXinstrumentError &e);
};

class NXdetectorError:public Exception{
public:
	NXdetectorError():Exception("NXdetectorError"){}
	NXdetectorError(const String &i,const String &d):Exception("NXdetectorError",i,d){}
	virtual ~NXdetectorError(){}

	friend std::ostream &operator<<(std::ostream &o,const NXdetectorError &e);
};

class NXnoteError:public Exception{
public:
	NXnoteError():Exception("NXnoteError"){}
	NXnoteError(const String &i,const String &d):Exception("NXnoteError",i,d){}
	virtual ~NXnoteError() {}

	friend std::ostream &operator<<(std::ostream &o,const NXnoteError &e);
};


} /* namespace nx */
} /* namespace pni */
#endif /* BASECLASSEXCEPTIONS_HPP_ */

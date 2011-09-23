/*
 * BaseClassExceptions.hpp
 *
 *  Created on: Sep 23, 2011
 *      Author: eugen
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
	virtual ~NXentryError();

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


} /* namespace nx */
} /* namespace pni */
#endif /* BASECLASSEXCEPTIONS_HPP_ */

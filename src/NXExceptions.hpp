/*
 * NXExceptions.hpp
 *
 *  Created on: Aug 5, 2011
 *      Author: eugen
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

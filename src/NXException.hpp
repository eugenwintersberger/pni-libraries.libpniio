/*
 * NXException.hpp
 *
 *  Created on: Aug 3, 2011
 *      Author: eugen
 */

#ifndef NXEXCEPTION_HPP_
#define NXEXCEPTION_HPP_

#include <iostream>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <pni/utils/PNITypes.hpp>
using namespace pni::utils;

namespace pni {
namespace nx {

//general purpose exception class
class NXException {
public:
	typedef boost::shared_ptr<NXException> sptr;

	NXException();
	NXException(const String &n);
	NXException(const String &n,const String &i);
	NXException(const String &n,const String &i,const String &d);
	NXException(const NXException &e);
	virtual ~NXException();

	NXException &operator=(const NXException &e);

	virtual void setName(const String &n);
	virtual String getName() const;

	virtual void setIssuer(const String &i);
	virtual String getIssuer() const;

	virtual void setDescription(const String &d);
	virtual String getDescription() const;

	virtual void setPreviousException(NXException::sptr prev);

private:
	String _name;
	String _issuer;
	String _description;

	NXException::sptr _prev_exception;

};

//end of namespace
}
}

#endif /* NXEXCEPTION_HPP_ */

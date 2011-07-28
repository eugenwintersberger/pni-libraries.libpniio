/*
 * H5Exceptions.hpp
 *
 *  Created on: Jul 6, 2011
 *      Author: eugen
 */

#ifndef H5EXCEPTIONS_HPP_
#define H5EXCEPTIONS_HPP_

#include <pni/utils/PNITypes.hpp>
extern "C"{
#include <hdf5.h>
}

#include "H5ErrorStack.hpp"

namespace pni{
namespace nx{
namespace h5{

using namespace pni::utils;

#define H5METHOD_EXCEPTION_SETUP(issuer) \
	static String ExIssuer = (issuer);\
	String ExDescription

#define H5METHOD_EXCEPTION_THROW(extype,exdesc)\
	extype e;\
	ExDescription = (exdesc);\
	e.setName(ExIssuer);\
	e.setDescription(ExDescription);\
	std::cerr<<e<<std::endl;\
	std::cerr<<"in line: "<<__LINE__<<" of file "<<__FILE__<<std::endl;\
	throw e;

class H5Exception{
protected:
	String _name;
	String _issuer;
	String _description;

	H5ErrorStack _h5estack;
public:
	H5Exception();
	H5Exception(const String &n);
	H5Exception(const String &n,const String &i,const String &d);
	virtual ~H5Exception();

	virtual void setName(const String &n);
	virtual String getName() const;

	virtual void setIssuer(const String &i);
	virtual String getIssuer() const;

	virtual void setDescription(const String &d);
	virtual String getDescription() const;

	friend std::ostream &operator<<(std::ostream &o,const H5Exception &e);

};

class H5DataTypeException:public H5Exception{
public:
	H5DataTypeException();
	H5DataTypeException(const String &i,const String &d);
	virtual ~H5DataTypeException();

	friend std::ostream &operator<<(std::ostream &o,const H5DataTypeException &e);
};

class H5DataSetException:public H5Exception{
public:
	H5DataSetException();
	H5DataSetException(const String &i,const String &d);
	virtual ~H5DataSetException();

	friend std::ostream &operator<<(std::ostream &o,const H5DataSetException &e);
};

class H5DataSpaceException:public H5Exception{
public:
	H5DataSpaceException();
	H5DataSpaceException(const String &i,const String &d);
	virtual ~H5DataSpaceException();

	friend std::ostream &operator<<(std::ostream &o,const H5DataSpaceException &e);
};

class H5AttributeException:public H5Exception{
public:
	H5AttributeException();
	H5AttributeException(const String &i,const String &d);
	virtual ~H5AttributeException();

	friend std::ostream &operator<<(std::ostream &o,const H5AttributeException &e);
};

class H5FileException:public H5Exception{
public:
	H5FileException();
	H5FileException(const String &i,const String &d);
	virtual ~H5FileException();

	friend std::ostream &operator<<(std::ostream &o,const H5FileException &e);
};

//end of namespace
}
}
}


#endif /* H5EXCEPTIONS_HPP_ */
